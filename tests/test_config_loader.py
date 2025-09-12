from pathlib import Path
import sys

REPO_ROOT = Path(__file__).resolve().parents[1]
sys.path.append(str(REPO_ROOT))

from scripts.config_loader import load_config  # noqa: E402


def test_olivenbaum_config_loads():
    cfg = load_config(REPO_ROOT / "plants" / "olivenbaum.json")
    assert cfg.name == "Olivenbaum"
    assert cfg.moistureThreshold == 520


def test_defaults_applied(tmp_path):
    p = tmp_path / "plant.json"
    p.write_text('{"name": "Test"}')
    cfg = load_config(p)
    assert cfg.waterDurationMs == 3000
    assert cfg.measureIntervalMs == 60000
