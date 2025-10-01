# Soft Robotics PCB

Motor control, optical feedback, ADCs, sensors, servos, and a camera on a single board.  
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
### Schematic 
<img width="1276" height="874" alt="image" src="https://github.com/user-attachments/assets/9f45ea96-3302-4600-9bac-3ce35ebfb80c" />

### PCB Layout
<img width="971" height="929" alt="image" src="https://github.com/user-attachments/assets/069e9272-6496-45fa-8958-314af8e39d6f" />

### Front View
<img width="787" height="800" alt="image" src="https://github.com/user-attachments/assets/745cd26e-8e00-4f58-bc77-62a3f7b1588d" />

### Back View
<img width="792" height="846" alt="image" src="https://github.com/user-attachments/assets/a6f7de36-a9c3-403d-9135-eba6580efe70" />

### Setup Guidelines
1. Open ArduinoIDE
2. Set Baud Rate: 115200
3. Set COM to whatever appears on device manager
4. Set board to ESP32S3-Dev Board.
5. The serial monitor must read at 115200 Baud.
### Boot Guide
1. Enter Bootloader
2. Ensure IO46 is pulled down.
3. Pull boot low (Switch ON), Pull Enable Up and Down to reset the ESP32 (Switch On -> Switch Off). During this time firmware can be uploaded.
4. Boot from uploaded code
4. Pull boot high (Switch OFF), Pull Enable Up and Down to reset the ESP32 (Switch On -> Switch Off).


## Pinout
- CAMERA: PINS 4 to 14, 21.
- CAM_SDA: IO20
- CAM_SCL: IO3
- S_PWM: IO1, ADC1_CH0
- SDA: IO42
- SCL: IO41
- XSHUT: IO40
- nFault_A: I039
- nFault_B: IO4
- I_SENSE_A: IO14, ADC_CH3
- I_SENSE_B: IO2, ADC1_CH0
- IN1_A: IO38
- IN2_A: IO48
- IN1_B: IO47
- IN2_B: IO21
- LDR1: IO19
- LDR2: IO5
  
## Calculations

### Trip Current (typ.)
I_TRIP = V_REF / (R_IPROPI × A_IPROPI)  
       = 3.3 / (2350 × 455 × 10^-6)  
       ≈ 3.09 A

### IPROPI Current at Trip
I_IPROPI = I_TRIP × A_IPROPI  
         = V_REF / R_IPROPI  
         = 3.3 / 2350  
         ≈ 1.40 mA

### IPROPI Voltage at Trip
V_IPROPI = I_IPROPI × R_IPROPI  
         = 3.3 V
