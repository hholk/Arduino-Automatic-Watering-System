from pathlib import Path


def test_lotti_page_present():
    repo_root = Path(__file__).resolve().parents[1]
    lotti = repo_root / "public" / "lotti.html"
    assert lotti.is_file()
    assert (repo_root / "public" / ".nojekyll").is_file()
    text = lotti.read_text(encoding="utf-8")
    assert "canvas class=\"fx\"" not in text
    assert "burst(" not in text
