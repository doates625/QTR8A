/**
 * @file QTR8A.h
 * @author Dan Oates (WPI Class of 2020)
 */
#include "QTR8A.h"
#include <CppUtil.h>

/**
 * Static Constants
 */
const float QTR8A::positions[8] =
{
	-0.0333375f,	// Sensor 0
	-0.0238125f,	// Sensor 1
	-0.0142875f,	// Sensor 2
	-0.0047625f,	// Sensor 3
	+0.0047625f,	// Sensor 4
	+0.0142875f,	// Sensor 5
	+0.0238125f,	// Sensor 6
	+0.0333375f,	// Sensor 7
};

/**
 * @brief Constructs QTR-8A interface
 * @param inputs Array of ordered analog inputs
 * @param white_thresh Maximum mean reading to be considered on white
 * @param black_thresh Minimum mean reading to be considered on black
 * 
 * Any mean reading between the white and black thresholds is assumed to be a
 * black line on a white surface.
 */
QTR8A::QTR8A(AnalogIn* inputs, float white_thresh, float black_thresh)
{
	this->inputs = inputs;
	this->white_thresh = white_thresh;
	this->black_thresh = black_thresh;
	for (uint8_t i = 0; i < 8; i++)
	{
		this->readings[i] = 0.0f;
	}
	this->mean = 0.0f;
	this->state = on_unknown;
}

/**
 * @brief Sets white surface threshold for state detection
 * @param white_thresh Maximum mean reading to be considered on white
 */
void QTR8A::set_white_thresh(float white_thresh)
{
	this->white_thresh = white_thresh;
}

/**
 * @brief Sets black surface threshold for state detection
 * @param black_thresh Minimum mean reading to be considered on black
 */
void QTR8A::set_black_thresh(float black_thresh)
{
	this->black_thresh = black_thresh;
}

/**
 * @brief Reads all 8 analog inputs and stores them internally
 * 
 * Call this method on each loop iteration before calls to:
 * - get_single()
 * - get_mean()
 * - get_state()
 * - line_pos()
 */
void QTR8A::update()
{
	// Get individual and average readings
	for (uint8_t i = 0; i < 8; i++)
	{
		readings[i] = inputs[i].read();
	}
	mean = CppUtil::mean(readings, 8);

	// Determine state with thresholds
	if (mean < white_thresh)
	{
		state = on_white;
	}
	else if (mean > black_thresh)
	{
		state = on_black;
	}
	else
	{
		state = on_line;
	}
}

/**
 * @brief Returns normalized ADC reading from given sensor
 * @param index Sensor index in range [0,7]
 */
float QTR8A::get_single(uint8_t index)
{
	return readings[index];
}

/**
 * @brief Returns mean of all 8 sensor readings
 */
float QTR8A::get_mean()
{
	return mean;
}

/**
 * @brief Returns state from last update
 * 
 * State options:
 * - on_white = On completely white surface
 * - on_line = On black line on white surface
 * - on_black = On completely black surface
 * - on_unknown = Before update() is called
 */
QTR8A::linestate_t QTR8A::get_state()
{
	return state;
}

/**
 * @brief Returns line position relative to sensor [m]
 * 
 * The value 0 corresponds to the line being exactly the middle of the sensor
 * (between inputs 3 and 4). Negative values correspond to the line approaching
 * input 0, and positive values approaching input 7. Note that the user should
 * calibrate the white and black thresholds and assure that the state is on_line
 * by calling get_state() before using this method.
 */
float QTR8A::line_pos()
{
	float num = 0.0f;
	float den = 0.0f;
	for (uint8_t i = 0; i < 8; i++)
	{
		num += readings[i] * positions[i];
		den += readings[i];
	}
	return num / den;
}