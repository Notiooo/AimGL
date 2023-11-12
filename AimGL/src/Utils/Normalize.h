#pragma once

/**
 * \brief Normalizes the values in a given range to the 0 - 1 space.
 * \param value Value to be normalized.
 * \param min The minimum value that can be taken
 * \param max The maximum value that can be taken
 * \return Normalized value from 0 to 1
 */
float normalize(float value, float min, float max)
{
    return ((value - min) / (max - min));
}