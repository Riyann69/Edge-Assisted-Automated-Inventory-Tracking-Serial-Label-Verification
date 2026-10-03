# Edge-Assisted Inventory Tracking & Serial Label Verification

Everything lives in **`label_verification_pipeline.ipynb`**. Open it in Jupyter or VS Code and use *Run All*.

```
label_verifier/
├── label_verification_pipeline.ipynb   <- the whole project
├── data/
│   ├── inventory.csv                   <- stock list (replace with yours, then db.reseed())
│   ├── inventory.db                    <- SQLite: items + scans log (created by the notebook)
│   ├── synthetic/images + annotations.csv   <- generated TEST set (496 frames)
│   ├── yolo/                                 <- separate YOLO training set (400 train / 100 val)
│   └── real/images + annotations.csv        <- PUT YOUR PHONE / WEBCAM PHOTOS HERE
├── outputs/
│   ├── figures/   <- every graph & stage image used in the report
│   ├── stages/    <- each pipeline intermediate image as a PNG
│   ├── results/   <- per-image CSVs (synthetic, detection, ablation, easyocr, real)
│   └── yolo/label_detector/weights/best.pt   <- trained YOLO11n label detector
└── hardware/
    ├── indicator/indicator.ino         <- Arduino: G=PASS green LED D8, R=MISMATCH red LED D9, E=ERROR buzzer D10
    └── pico_main.py                    <- same thing in MicroPython for a Raspberry Pi Pico
```

## Requirements
Python 3.10+, [Tesseract 5](https://github.com/UB-Mannheim/tesseract/wiki) installed, then:

```bash
pip install opencv-python pytesseract python-Levenshtein pillow matplotlib pandas qrcode pyzbar pyserial flask easyocr polars
pip install ultralytics --no-deps   # YOLO; --no-deps keeps your existing OpenCV build
```

## Using real data instead of the synthetic set
* **Photos from your phone:** copy them to `data/real/images/` and add one line per photo to
  `data/real/annotations.csv`, e.g. `images/IMG_2041.jpg,SN-284517-XJ,30` (filename, true serial, optional angle).
  Re-run Section 11 to get the same CER metrics and plots on real photos.
* **Phone camera live:** IP Webcam / DroidCam app, then set `SOURCE = "http://<phone-ip>:8080/video"`.
* **Phone browser upload:** set `START_PHONE_SERVER = True` and open `http://<laptop-ip>:5000` on the phone.
  Type the true serial and the photo is saved straight into the real dataset.
* **USB webcam rig:** set `SOURCE = 0` and call `live_scan(0)` for auto-trigger scanning.

The notebook follows the Review 2 deck: input → processing (YOLO → ROI → preprocessing → OCR) → verification
(PASS / MISMATCH / ERROR) → output (LED/buzzer), then the slide-12 test plan.

Switches at the top of the notebook (`REGENERATE_DATASET`, `RERUN_EVALUATION`, `RUN_ABLATION`, `RUN_EASYOCR`, `TRAIN_YOLO`)
control the slow steps. Results are cached, so re-running is quick.
