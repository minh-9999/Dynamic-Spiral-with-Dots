#pragma once

#include "convertColor.hh"

// Convert HSV color to RGB (values in range 0..1)
// Formula: compute chroma (c), intermediate value (x), then add offset (m)
sf::Vector3f HSVtoRGB(float h, float s, float v)
{
    float c = v * s;                                                 // chroma: intensity of the color
    float x = c * (1 - std::fabs(std::fmod(h * 6.0f, 2.0f) - 1.0f)); // intermediate value
    float m = v - c;                                                 // offset to match brightness
    float r, g, b;

    // Determine which sector of the color wheel the hue falls into
    if (h < 1.0f / 6)
    {
        r = c;
        g = x;
        b = 0;
    }
    else if (h < 2.0f / 6)
    {
        r = x;
        g = c;
        b = 0;
    }
    else if (h < 3.0f / 6)
    {
        r = 0;
        g = c;
        b = x;
    }
    else if (h < 4.0f / 6)
    {
        r = 0;
        g = x;
        b = c;
    }
    else if (h < 5.0f / 6)
    {
        r = x;
        g = 0;
        b = c;
    }
    else
    {
        r = c;
        g = 0;
        b = x;
    }

    // Add offset m to shift values into [0..1]
    return {r + m, g + m, b + m};
}