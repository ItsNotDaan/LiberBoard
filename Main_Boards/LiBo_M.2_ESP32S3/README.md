## ESP32-S3, M.2 based System on Module (SOM)

This is my first KiCad project, developed over the last 2 months alongside my EPS project and work. 

## Versions:
### V1
The first version that was created. Soldered by hand. Did not boot properly. 

### V2
The second version got a redesign of the main ESP32 S3 connections. This time hopefully with the correct connections. 
Some bootpins were removed to change to a more usable setup. The board has also been ordered with assembly to make sure the soldering is correct. 

### Main Components

- **CPU:** ESP32-S3R8
- **Flash:** W25Q16JVUXIQ (16MBIT)
- **Crystals:** 40MHz and 32.768KHz (HSE/LSE)
- **Power/Flashing/Debugging:** USB-C
- **Buck Converter:** TLV62568DBV
- **Buttons:** Two buttons for RESET and BOOT
- **Antenna:** Antenna with PI filter
- **PCB:** 4-layer PCB (Top, GND, VCC, Bottom), internal planes are hidden

All these components are included on a M.2-B-Key footprint. 

## JLCPCB Ordering Details

- **Base Material:** FR-4
- **Layers:** 4
- **Dimension:** 70.97 mm × 70 mm
- **PCB Thickness:** 0.8 mm
- **Specify Stackup:** yes — JLC04081H-7628
- **Impedance Control:** No requirement
- **Material Type:** FR4 TG135
- **Via Covering:** Plugged
- **Surface Finish:** ENIG — Gold Thickness: 1U"
- **Outer Copper Weight:** 1 oz
- **Inner Copper Weight:** 0.5 oz
- **Gold Fingers:** Yes
- **Beveling:** 45°
- **Mark on PCB:** 2D barcode (Serial Number)
- **Min via hole size/diameter:** 0.3 mm / (0.4 / 0.45 mm)
- **Appearance Quality:** IPC Class 2 Standard
- **Silkscreen Technology:** Ink-jet/Screen Printing Silkscreen
- **Package Box:** With JLCPCB logo
- **Board Outline Tolerance:** ±0.2 mm (Regular)

### Notes
- **Layer Sequence:** Top / GND / VCC / Bottom (from design)
- **NOTE:** If a detail is not shown it means the standard is used. 
 
### Inspiration

The idea originated from a desire to create a more complex and smaller PCB that incorporates an expensive CPU. This CPU should be versatile enough to be used on different projects. After watching a video from Phil's Lab, I learned that M.2 was a great alternative to the mostly used header pin setup. 

### Future Plans

The ESP32-S3 is not high-end or anything special, but I plan to quickly redesign this board using the newly announced ESP32-P4. It is a really interesting and high-speed CPU based on the RISC-V architecture and I'm excited to start creating some (DSP) code with it. 

I have ordered the components and the PCB to start experimenting with it.

https://www.linkedin.com/in/daan-heetkamp/
