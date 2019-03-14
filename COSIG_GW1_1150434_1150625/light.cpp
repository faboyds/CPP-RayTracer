//
//  light.cpp
//  COSIG_GW1_1150434_1150625
//
//  Created by Fábio Lourenço on 20/02/2019.
//  Copyright © 2019 Fábio Lourenço. All rights reserved.
//

#include "light.hpp"

Light::Light(Transformation &transformation, double red, double green, double blue): transformation(transformation), red(red), green(green), blue(blue)
{
}

std::ostream& operator<<(std::ostream &strm, const Light &l) {
    return strm << "Light( transformation: " << l.transformation << ", red: " << l.red << ", green: " << l.green << ", blue: " << l.blue << " )";
}
