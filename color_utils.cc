#include "color_utils.hh"
#include <iostream>

// Create a LittleCMS transform: Adobe RGB -> sRGB (8-bit output)
// Input: float RGB values in [0..1]
// Output: 8-bit RGB values in [0..255]
cmsHTRANSFORM createAdobeToSRGBTransform(const char *adobeIccPath)
{
    // Open Adobe RGB ICC profile
    cmsHPROFILE hIn = cmsOpenProfileFromFile(adobeIccPath, "r");
    if (!hIn)
    {
        std::cerr << "Cannot open Adobe ICC: " << adobeIccPath << "\n";
        return nullptr;
    }

    // Create default sRGB profile
    cmsHPROFILE hOut = cmsCreate_sRGBProfile();
    if (!hOut)
    {
        std::cerr << "Cannot create sRGB profile\n";
        cmsCloseProfile(hIn);
        return nullptr;
    }

    // Create transform: AdobeRGB (float) -> sRGB (8-bit)
    cmsHTRANSFORM xform = cmsCreateTransform(
        hIn, TYPE_RGB_FLT, // input: float RGB
        hOut, TYPE_RGB_8,  // output: 8-bit RGB
        INTENT_PERCEPTUAL, // rendering intent: perceptual
        0);

    cmsCloseProfile(hIn);
    cmsCloseProfile(hOut);
    return xform;
}

cmsHTRANSFORM createAdobeToSRGBTransform(cmsHPROFILE hAdobe)
{
    std::string srgbPath = std::string(LCMS_PROFILE_DIR) + "/AdobeRGB1998.icc";
    cmsHPROFILE hSRGB = cmsOpenProfileFromFile(srgbPath.c_str(), "r");
    if (!hSRGB)
        return nullptr;

    cmsHTRANSFORM transform = cmsCreateTransform(
        hAdobe, TYPE_RGB_FLT,
        hSRGB, TYPE_RGB_8,
        INTENT_PERCEPTUAL, 0);

    cmsCloseProfile(hSRGB);
    return transform;
}