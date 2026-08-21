# Custom Audio Effects Processor & Remote Controller

A custom-designed embedded system capable of applying 16 different DSP audio effects to an analog input signal (guitar processing). This project features a dual-PCB architecture communicating via a LoRa wireless link, built around a PIC microcontroller.

Developed in 2025 as part of the 3rd-year Embedded Systems curriculum at JUNIA ISEN Lille (6-member team).

## Key Features & Architecture

### Analog & Audio Processing Chain
* **Input Stage:** Preamplifier circuit designed for high-impedance instrument signals.
* **DSP & Codec:** Audio signal processing powered by the **V1000 DSP** chip paired with a **V4220 audio CODEC** for high-fidelity A/D and D/A conversion.
* **Output Stage:** Digitally controlled amplifier for precise output gain adjustments.

### Embedded System & Peripherals
* **Main MCU:** PIC microcontroller managing overall system control, DSP routing, and peripheral communications via **I2C, SPI, and UART**.
* **User Interface:** Real-time effect and parameters status displayed on dual 7-segment displays and streamed over a PC serial console via UART.
* **Wireless Remote Control (LoRa):** Secondary custom PCB acting as an industrial-grade radio remote controller to mirror and manipulate audio parameters from a distance.

## Repository Structure

Code/           # PIC microcontroller firmware & LoRa communication code
Hardware/       # Schematics, PCB layouts, and Gerber files
3D_Models/      # CAD files for enclosures and hardware mechanical design
Docs/           # Technical documentation and block diagrams
