#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <SPIFFS.h>
#include <lvgl.h>
#include <TFT_eSPI.h>
#include "plant_config.h"

// Pin definitions
static const int kMoistureSensorPin = 4;
static const int kPumpPin = 5;
static const int kWaterLevelPin = 6; // reservoir sensor

// Wi-Fi & MQTT configuration
const char *kSsid = "YOUR_WIFI";
const char *kPassword = "YOUR_PASS";
const char *kMqttServer = "homeassistant.local";

WiFiClient espClient;
PubSubClient mqttClient(espClient);

TFT_eSPI tft = TFT_eSPI();
static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf1[172 * 10];

PlantConfig activeConfig;
unsigned long lastMeasure = 0;

float weatherFactor = 1.0f; // updated via MQTT or Home Assistant

void mqttCallback(char *topic, byte *payload, unsigned int length) {
  // Handle incoming messages, e.g., weather factor
}

void setupMqtt() {
  mqttClient.setServer(kMqttServer, 1883);
  mqttClient.setCallback(mqttCallback);
}

void reconnectMqtt() {
  while (!mqttClient.connected()) {
    if (mqttClient.connect("esp32-watering")) {
      mqttClient.subscribe("watering/weatherFactor");
    } else {
      delay(5000);
    }
  }
}

void publishStatus(int moisture, bool watering, bool reservoirLow) {
  StaticJsonDocument<128> doc;
  doc["moisture"] = moisture;
  doc["watering"] = watering;
  doc["reservoirLow"] = reservoirLow;
  char buffer[128];
  size_t n = serializeJson(doc, buffer);
  mqttClient.publish("home/watering/status", buffer, n);
}

void guiCreate(); // forward declaration

void setup() {
  Serial.begin(115200);
  pinMode(kPumpPin, OUTPUT);
  pinMode(kWaterLevelPin, INPUT);
  digitalWrite(kPumpPin, LOW);

  if (!SPIFFS.begin(true)) {
    Serial.println("SPIFFS init failed");
  }

  WiFi.begin(kSsid, kPassword);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  setupMqtt();

  lv_init();
  tft.begin();
  tft.setRotation(0);
  lv_disp_draw_buf_init(&draw_buf, buf1, NULL, 172 * 10);

  static lv_disp_drv_t disp_drv;
  lv_disp_drv_init(&disp_drv);
  disp_drv.hor_res = 172;
  disp_drv.ver_res = 320;
  disp_drv.flush_cb = [](lv_disp_drv_t *d, const lv_area_t *a, lv_color_t const *c) {
    uint32_t w = (a->x2 - a->x1 + 1);
    uint32_t h = (a->y2 - a->y1 + 1);
    tft.startWrite();
    tft.setAddrWindow(a->x1, a->y1, w, h);
    tft.pushColors(&c->full, w * h, true);
    tft.endWrite();
    lv_disp_flush_ready(d);
  };
  disp_drv.draw_buf = &draw_buf;
  lv_disp_t *disp = lv_disp_drv_register(&disp_drv);
  (void)disp;

  guiCreate();
}

void startWatering() {
  digitalWrite(kPumpPin, HIGH);
  delay(activeConfig.waterDurationMs);
  digitalWrite(kPumpPin, LOW);
}

void guiPlantSelect(lv_event_t *e) {
  const char *path = (const char *)lv_event_get_user_data(e);
  if (loadPlantConfig(path, activeConfig)) {
    lv_obj_clean(lv_scr_act());
    lv_obj_t *label = lv_label_create(lv_scr_act());
    lv_label_set_text_fmt(label, "%s aktiv", activeConfig.name.c_str());
    lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
  }
}

void guiCreate() {
  lv_obj_t *oliveBtn = lv_btn_create(lv_scr_act());
  lv_obj_set_pos(oliveBtn, 10, 40);
  lv_obj_set_size(oliveBtn, 150, 60);
  lv_obj_add_event_cb(oliveBtn, guiPlantSelect, LV_EVENT_CLICKED,
                      (void *)"/plants/olivenbaum.json");
  lv_obj_t *oliveLabel = lv_label_create(oliveBtn);
  lv_label_set_text(oliveLabel, "Olivenbaum");
  lv_obj_center(oliveLabel);

  lv_obj_t *avocadoBtn = lv_btn_create(lv_scr_act());
  lv_obj_set_pos(avocadoBtn, 10, 120);
  lv_obj_set_size(avocadoBtn, 150, 60);
  lv_obj_add_event_cb(avocadoBtn, guiPlantSelect, LV_EVENT_CLICKED,
                      (void *)"/plants/avocadobaum.json");
  lv_obj_t *avocadoLabel = lv_label_create(avocadoBtn);
  lv_label_set_text(avocadoLabel, "Avocadobaum");
  lv_obj_center(avocadoLabel);
}

void loop() {
  lv_timer_handler();
  delay(5);
  if (!mqttClient.connected()) reconnectMqtt();
  mqttClient.loop();

  if (activeConfig.name != "" && millis() - lastMeasure >
                                     activeConfig.measureIntervalMs) {
    int moisture = analogRead(kMoistureSensorPin);
    bool reservoirLow = digitalRead(kWaterLevelPin) == LOW;
    float threshold = activeConfig.moistureThreshold * weatherFactor;
    bool watering = false;
    if (moisture < threshold && !reservoirLow) {
      watering = true;
      startWatering();
    }
    publishStatus(moisture, watering, reservoirLow);
    lastMeasure = millis();
  }
}
