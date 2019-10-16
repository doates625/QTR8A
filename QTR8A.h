/**
 * @file QTR8A.h
 * @brief Class for interfacing with Pololu QTR-8A analog line sensor
 * @author Dan Oates (WPI Class of 2020)
 * 
 * The QTR-8A is a linear array of 8 analog phototransistors designed for
 * robotic line-following applications. This class contains methods for raw
 * input reading, average calculation, line-detection via thresholding, and
 * line position calculation through center-of-mass. This class has support
 * for both the Arduino and Mbed platforms (see Platform).
 * 
 * Dependencies:
 * - AnalogIn: https://github.com/doates625/AnalogIn.git
 * - Platform: https://github.com/doates625/Platform.git
 * - CppUtil: https://github.com/doates625/CppUtil.git
 * 
 * References:
 * - QTR-8A: https://www.pololu.com/product/960
 */
#pragma once
#include <AnalogIn.h>

class QTR8A
{
public:
	QTR8A(AnalogIn* inputs, float line_thresh = 0.5f);
	void update();
	float get_single(uint8_t index);
	float get_mean();
	bool on_line();
	float line_pos();
private:
	static const float positions[8];
	AnalogIn* inputs;
	float readings[8];
	float line_thresh;
};