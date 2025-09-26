
#include "convertColor.hh"
#include "color_utils.hh"
#include <cmath>
#include <iostream>
#include <numbers>

// Clamp helper: ensures a float is within [0..1]
static inline float clampBoundary(float x)
{
    return std::max(0.0f, std::min(1.0f, x));
}

int main()
{
    unsigned choice;

    do
    {
        std::cout << "\n Choose tendency of spiral: \n"
                  << "\t 1 - Counter‑clockwise\n"
                  << "\t 2 - Clockwise\n";
        std::cout << "\n  your choice: ";
        std::cin >> choice;
    } while (choice != 1 && choice != 2);

    // Profile path (adjust accordingly)
    /* const char *adobeICC = "AdobeRGB1998.icc"; */

    // Path to AdobeRGB1998 ICC profile (adjust if needed)
    std::string adobePath = std::string(LCMS_PROFILE_DIR) + "/AdobeRGB1998.icc";
    cmsHPROFILE hAdobe = cmsOpenProfileFromFile(adobePath.c_str(), "r");
    if (!hAdobe)
    {
        std::cerr << "Cannot open profile: " << adobePath << std::endl;
        return 1;
    }

    // Create transform Adobe -> sRGB
    /* cmsHTRANSFORM adobeToSRGB = createAdobeToSRGBTransform(adobeICC); */
    cmsHTRANSFORM adobeToSRGB = createAdobeToSRGBTransform(hAdobe);
    if (!adobeToSRGB)
        return 1;

    // Create SFML window
    sf::RenderWindow window(sf::VideoMode({1000u, 1000u}), "Spiral with LittleCMS");
    window.setFramerateLimit(60); // cap FPS to avoid going too fast
    // window.setVerticalSyncEnabled(true); // alternatively, use vsync
    // window.clear(sf::Color::Black);

    const int boundary = 600; // number of points in the spiral
    // center of the spiral
    const float cx = window.getSize().x / 2.0f;
    const float cy = window.getSize().y / 2.0f;

    int drawnCount = 0;              // how many points already drawn
    const int pointsPerFrame = 1;    // reveal speed: 1 point per step
    const float stepSeconds = 0.06f; // time between steps (increase to slow further)

    sf::Clock clock;
    float accumulator = 0.0f;

    // for (int a = 0; a <= boundary; ++a)
    // {
    //     // 1) Generate HSV (rainbow) colors
    //     float hue = std::fmod(a / 300.0f, 1.0f);
    //     sf::Vector3f rgbHSV = HSVtoRGB(hue, 1.0f, 1.0f);

    //     // 2) Assuming the color is in Adobe RGB (0..1)
    //     float inAdobe[3] = {
    //         clampBoundary(rgbHSV.x),
    //         clampBoundary(rgbHSV.y),
    //         clampBoundary(rgbHSV.z)};

    //     // 3) Use LittleCMS to convert to sRGB 8-bit
    //     unsigned char outSRGB[3];
    //     cmsDoTransform(adobeToSRGB, inAdobe, outSRGB, 1);
    //     sf::Color color(outSRGB[0], outSRGB[1], outSRGB[2]);

    //     // 4) Calculate spiral coordinates
    //     float b = a * 0.5f; // radius grows with each step
    //     /* float c = a * static_cast<float>(M_PI) / 30.0f; */
    //     float c = a * std::numbers::pi_v<float> / 30.0f; // angle
    //     float x = cx + b * std::cos(c);
    //     float y;

    //     if (choice == 1)
    //         y = cy + b * std::sin(c); // counter‑clockwise
    //     else
    //         y = cy - b * std::sin(c); // clockwise

    //     // 5) Draw a dot at the computed position
    //     float radius = static_cast<float>(a % 10 + 5);
    //     sf::CircleShape dot(radius);
    //     dot.setFillColor(color);

    //     // SFML positions shapes by their top-left corner
    //     dot.setPosition({x - radius, y - radius});
    //     window.draw(dot);
    //     window.display();                // present the current state
    //     sf::sleep(sf::milliseconds(40)); // small delay per dot

    //     // keep the window responsive
    //     while (auto event = window.pollEvent())
    //     {
    //         if (event->is<sf::Event::Closed>())
    //             window.close();
    //     }
    // }

    while (window.isOpen())
    {
        // Handle events
        while (auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        // Time step
        accumulator += clock.restart().asSeconds();
        while (accumulator >= stepSeconds && drawnCount <= boundary)
        {
            drawnCount += pointsPerFrame; // reveal more points
            accumulator -= stepSeconds;   // consume time slice
        }

        // Draw everything up to drawnCount
        window.clear(sf::Color::Black);

        // Draw all points up to drawnCount
        for (int a = 0; a < drawnCount && a <= boundary; ++a)
        {
            // 1) Generate HSV rainbow color
            float hue = std::fmod(a / 300.0f, 1.0f);
            sf::Vector3f rgbHSV = HSVtoRGB(hue, 1.0f, 1.0f);

            // 2) Assume this color is in Adobe RGB
            float inAdobe[3] = {
                clampBoundary(rgbHSV.x),
                clampBoundary(rgbHSV.y),
                clampBoundary(rgbHSV.z)};
            unsigned char outSRGB[3];
            cmsDoTransform(adobeToSRGB, inAdobe, outSRGB, 1);
            sf::Color color(outSRGB[0], outSRGB[1], outSRGB[2]);

            // 3) Compute spiral coordinates
            float b = a * 0.5f;
            float c = a * std::numbers::pi_v<float> / 30.0f;
            float x = cx + b * std::cos(c);

            float y = (choice == 1)
                          ? y = cy + b * std::sin(c)  // counter‑clockwise
                          : y = cy - b * std::sin(c); // clockwise

            // 4) Draw dot
            // float radius = static_cast<float>(a % 10 + 5);
            float radius = 4.f;

            sf::CircleShape dot(radius);
            dot.setFillColor(color);
            dot.setPosition({x - radius, y - radius});
            window.draw(dot);
        }

        // Show frame
        window.display();

        // Increase how many points to draw next frame
        // if (drawnCount <= boundary)
        //     drawnCount += pointsPerFrame;
    }

    // window.display();

    // Event loop: keep window open until user closes it
    /*
    while (window.isOpen())
    {
        while (auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
    }
    */

    // Advance how many points to show next frame
    /*
    if (drawnCount <= boundary)
        drawnCount += pointsPerFrame;
    */

    // Free the transform
    cmsDeleteTransform(adobeToSRGB);
    return 0;
}
