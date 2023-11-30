#pragma once

/**
 * \brief Performs linear interpolation between two values.
 * \tparam T The type of the values to interpolate.
 * \param start The starting value of the interpolation.
 * \param end The ending value of the interpolation.
 * \param delta The interpolation factor (most often multiplied by deltatime,
 * so the time that has passed since the game was last updated.)
 * \return The interpolated value of type T.
 */
template<typename T>
auto lerp(const T& start, const T& end, float delta)
{
    return start + delta * (end - start);
}