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

	// Line state enum
	typedef enum
	{
		on_white,	// On completely white surface
		on_line,	// On black line on white surface
		on_black,	// On completely black surface
		on_unknown,	// Before a reading is done
	}
	linestate_t;

	// Construction and initialization
	QTR8A(
		AnalogIn* inputs,
		float white_thresh = 0.1f,
		float black_thresh = 0.9f);
	void set_white_thresh(float white_thresh);
	void set_black_thresh(float black_thresh);
	
	// Get readings
	void update();
	float get_single(uint8_t index);
	float get_mean();
	linestate_t get_state();
	float line_pos();
	
private:
	static const float positions[8];
	AnalogIn* inputs;
	float white_thresh;
	float black_thresh;
	float readings[8];
	float mean;
	linestate_t state;
};