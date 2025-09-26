#pragma once
#include <lcms2.h>

cmsHTRANSFORM createAdobeToSRGBTransform(const char *adobeIccPath);
cmsHTRANSFORM createAdobeToSRGBTransform(cmsHPROFILE hAdobe);
