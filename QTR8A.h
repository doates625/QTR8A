/**
 * @file QTR8A.h
 * @brief Class for interfacing with Pololu QTR-8A analog line sensor
 * @author Dan Oates (WPI Class of 2020)
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