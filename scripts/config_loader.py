from dataclasses import dataclass
import json
from pathlib import Path

@dataclass
class PlantConfig:
    name: str = ""
    moistureThreshold: int = 600
    waterDurationMs: int = 3000
    measureIntervalMs: int = 60000
    weatherAdjust: float = 1.0


def load_config(path: Path) -> PlantConfig:
    data = json.loads(path.read_text())
    cfg = PlantConfig()
    for field in cfg.__dataclass_fields__:
        if field in data:
            setattr(cfg, field, data[field])
    return cfg
