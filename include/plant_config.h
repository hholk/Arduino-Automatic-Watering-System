#ifndef PLANT_CONFIG_H
#define PLANT_CONFIG_H

#include <ArduinoJson.h>
#include <FS.h>

struct PlantConfig {
  String name;
  int moistureThreshold;
  unsigned long waterDurationMs;
  unsigned long measureIntervalMs;
  float weatherAdjust;
  PlantConfig()
      : name(""), moistureThreshold(600), waterDurationMs(3000),
        measureIntervalMs(60000), weatherAdjust(1.0f) {}
};

bool loadPlantConfig(const char *path, PlantConfig &config);

#endif
