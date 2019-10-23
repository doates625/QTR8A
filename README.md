# QTR8A
Class for interfacing with Pololu QTR-8A analog line sensor  
Written by Dan Oates (WPI Class of 2020)

### Description
The QTR-8A is a linear array of 8 analog phototransistors designed for robotic line-following applications. This class contains methods for raw input reading, average calculating, line-following state detection via thresholding, and line position calculation through a center-of-mass calculation. This class has support for both the Arduino and Mbed platforms.

### Dependencies
- [CppUtil](https://github.com/doates625/CppUtil.git)
- [Platform](https://github.com/doates625/Platform.git)
- [AnalogIn](https://github.com/doates625/AnalogIn.git)

### References
- [Pololu QTR-8A](https://www.pololu.com/product/960)