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
 * @param line_thresh Line detection threshold in range [0,1]
 * 
 * Analog readings increase from white to black. The on_line() method compares
 * the mean reading to the given threshold for line detection.
 */
QTR8A::QTR8A(AnalogIn* inputs, float line_thresh)
{
	this->inputs = inputs;
	this->line_thresh = line_thresh;
	for (uint8_t i = 0; i < 8; i++)
	{
		this->readings[i] = 0.0f;
	}
}

/**
 * @brief Reads all 8 analog inputs and stores them internally
 * 
 * Call this method on each loop iteration before calls to:
 * - get_single()
 * - get_mean()
 * - on_line()
 * - line_pos()
 */
void QTR8A::update()
{
	for (uint8_t i = 0; i < 8; i++)
	{
		readings[i] = inputs[i].read();
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
	return Util::mean(readings, 8);
}

/**
 * @brief Returns true if sensor detects a black line
 */
bool QTR8A::on_line()
{
	return get_mean() > line_thresh;
}

/**
 * @brief Returns line position relative to sensor [m]
 * 
 * The value 0 corresponds to the line being exactly the middle of the sensor
 * (between inputs 3 and 4). Negative values correspond to the line approaching
 * input 0, and positive values approaching input 7.
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