import csv
import time
from datetime import datetime
from pathlib import Path

from arduino.app_utils import App, Bridge

DATA_DIR = Path(__file__).resolve().parent / "data"
DATA_DIR.mkdir(exist_ok=True)


def _build_log_path(now: datetime) -> Path:
    base_name = now.strftime("data_%Y%m%d_%H")
    candidate = DATA_DIR / f"{base_name}.csv"
    counter = 1
    while candidate.exists():
        candidate = DATA_DIR / f"{base_name}_{counter}.csv"
        counter += 1
    return candidate


LOG_PATH = _build_log_path(datetime.now())

if not LOG_PATH.exists():
    with LOG_PATH.open("w", newline="") as log_file:
        writer = csv.writer(log_file)
        writer.writerow(
            [
                "timestamp_ms",
                "latitude",
                "longitude",
                "heading",
                "rudder_angle",
                "awa",
                "filtered_awa",
                "unmanned_status",
            ]
        )

print(f"Logging data to {LOG_PATH}")


def log_data(
    timestamp_ms,
    latitude,
    longitude,
    heading,
    rudder_angle,
    awa,
    filtered_awa,
    unmanned_status,
):
    with LOG_PATH.open("a", newline="") as log_file:
        writer = csv.writer(log_file)
        writer.writerow(
            [
                timestamp_ms,
                latitude,
                longitude,
                heading,
                rudder_angle,
                awa,
                filtered_awa,
                unmanned_status,
            ]
        )


Bridge.provide("log_data", log_data)


def loop():
    """This function is called repeatedly by the App framework."""
    time.sleep(1)

App.run(user_loop=loop)
