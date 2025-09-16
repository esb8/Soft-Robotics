# Soft Robotics PCB

Electromagnet control, optical feedback, ADCs, and vision on a single board.  
This project features a soft-robotics controller built around an ESP32 with an onboard camera, driver stages for multiple electromagnets, photoresistor sensing, SPI breakouts, and a UART header for easy flashing.


## Features
- **ESP32** (WROOM or WROVER) with **camera module** (OV2640 or similar)
- **4–8 electromagnet channels** with protected low-side MOSFET drivers (PWM capable)
- **Photoresistor (LDR) inputs** with RC dividers → ADC
- **SPI header** (3.3V) for add-ons (external ADCs, sensors, or LED drivers)
- **Dedicated UART header** for flashing (RTS/DTR optional) + **USB-C** or JST-PH power
- **Reverse-polarity & transient protection**, per-channel flyback/snubbers
- **Buck Regulation for 2S LiPos**
- **Mounting + cable-reliefs** sized for soft-robotics rigs
- **Full Codebase** containing all peripheral test code


## Media
### Front View
<img width="787" height="800" alt="image" src="https://github.com/user-attachments/assets/745cd26e-8e00-4f58-bc77-62a3f7b1588d" />

### Back View
<img width="792" height="846" alt="image" src="https://github.com/user-attachments/assets/a6f7de36-a9c3-403d-9135-eba6580efe70" />


