#include "plant_config.h"

bool loadPlantConfig(const char *path, PlantConfig &config) {
  File file = SPIFFS.open(path, "r");
  if (!file) {
    Serial.println("Failed to open config");
    return false;
  }
  StaticJsonDocument<256> doc;
  DeserializationError err = deserializeJson(doc, file);
  file.close();
  if (err) {
    Serial.println("Failed to parse config");
    return false;
  }
  config.name = doc["name"] | config.name;
  config.moistureThreshold = doc["moistureThreshold"] | config.moistureThreshold;
  config.waterDurationMs = doc["waterDurationMs"] | config.waterDurationMs;
  config.measureIntervalMs = doc["measureIntervalMs"] | config.measureIntervalMs;
  config.weatherAdjust = doc["weatherAdjust"] | config.weatherAdjust;
  return true;
}
