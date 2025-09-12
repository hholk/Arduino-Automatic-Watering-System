from pathlib import Path


def test_lotti_page_present():
    repo_root = Path(__file__).resolve().parents[1]
    assert (repo_root / "public" / "lotti.html").is_file()
    assert (repo_root / "public" / ".nojekyll").is_file()
