//
// Created by ASUS on 12/17/2023.
//

#ifndef SPL_01_COORDINATECALC_H
#define SPL_01_COORDINATECALC_H

#include <iostream>
#include <cmath>

class CoordinateCalc {

public:
    CoordinateCalc() {}

    void equatorialToEcliptic(double ra, double dec, double &lambda, double &beta) {
        double epsilon = 23.439;

        ra *= M_PI / 180.0; // Convert degrees to radians
        dec *= M_PI / 180.0;

        lambda = atan2(sin(ra) * cos(epsilon) + tan(dec) * sin(epsilon), cos(ra));
        beta = asin(sin(dec) * cos(epsilon) - cos(dec) * sin(epsilon) * sin(ra));

        lambda *= 180.0 / M_PI;
        beta *= 180.0 / M_PI;
    }

    void eclipticToEquatorial(double lambda, double beta, double &ra, double &dec) {
        double epsilon = 23.439;

        lambda *= M_PI / 180.0;
        beta *= M_PI / 180.0;

        ra = atan2(sin(lambda) * cos(epsilon) - tan(beta) * sin(epsilon), cos(lambda));
        dec = asin(sin(epsilon) * sin(lambda) + cos(epsilon) * cos(lambda) * sin(beta));

        ra *= 180.0 / M_PI;
        dec *= 180.0 / M_PI;
    }

    void calculateParallax(double ra, double dec, double distance, double &parallaxRA, double &parallaxDec) {
        ra *= M_PI / 180.0;
        dec *= M_PI / 180.0;

        parallaxRA = atan2(-cos(ra) * sin(dec) * distance, cos(dec) * distance + sin(ra) * sin(dec));

        parallaxDec = asin(-sin(ra) * cos(dec) * distance);

        parallaxRA *= 180.0 / M_PI;
        parallaxDec *= 180.0 / M_PI;
    }

};


#endif //SPL_01_COORDINATECALC_H
