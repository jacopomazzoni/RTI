# RTI Dome Controller Firmware

![GitHub last commit](https://img.shields.io/github/last-commit/jacopomazzoni/RTI)

## Overview

This Arduino project provides firmware for an RTI (Reflection Transformation Images) Dome Controller that utilizes addressable RGBW LED strips and controls a timer for a camera.

## Features

- **Addressable RGBW LED Support:** Illuminate your dome using addressable RGBW LED strips.
- **Camera Timer Control:** Precisely control the timing of your camera and see an estimate of the capture time.
- **Simple Codebase:** Easily customize the behavior of the dome controller to suit your specific requirements.
- **User-Friendly Interface:** The firmware is designed with a user-friendly interface to simplify setup and operation.

## Hardware Requirements

- Arduino Board (e.g., Arduino Uno)
- Addressable RGBW LED Strips
- Camera with Remote shutter Capability
- [5v Relay switch]
- 16x4 LCD display with ic2 controller
- 2 rotary encoders
- 1 latching switch
- 1 semispherical plastic bowl

## Installation

1. Clone the repository:

    ```bash
    git clone https://github.com/jacopomazzoni/RTI.git
    ```

2. Upload the firmware to your Arduino board using the Arduino IDE or your preferred method.

3. build the device (schematics coming soon)
## Contributing

We welcome contributions from the community! Feel free to open issues, submit pull requests, or provide feedback.

## License

This project is licensed under the [Creative Commons](LICENSE.md) - see the [LICENSE.md](LICENSE.md) file for details.

## Acknowledgments

- [a copy of FastLED.h is included, I do not own FastLED.h please support their awesome project]
- [other bits and bobs from other libraries, attribution is maintained in the header files of each library]

---

**Happy RTI Capturing!** 📷✨