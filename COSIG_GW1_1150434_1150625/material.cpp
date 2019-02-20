//
//  material.cpp
//  COSIG_GW1_1150434_1150625
//
//  Created by Fábio Lourenço on 20/02/2019.
//  Copyright © 2019 Fábio Lourenço. All rights reserved.
//

#include "material.hpp"

Material::Material(double red, double green, double blue,
                   double ambient, double diffuse, double reflection, double refractionCoefficient, double refractionIndex):
                        red(red), green(green), blue(blue),
                        ambient(ambient), diffuse(diffuse), reflection(reflection),
                        refractionCoefficient(refractionCoefficient), refractionIndex(refractionIndex)
{
}

std::ostream& operator<<(std::ostream &strm, const Material &m) {
    return strm << "Material( red: " << m.red << ", green: " << m.green << ", blue: " << m.blue << ", ambient: " << m.ambient << ", diffuse: " << m.diffuse << ", reflection: " << m.reflection << ", refraction coefficient: " << m.refractionCoefficient << ", refraction index: " << m.refractionIndex << " )";
}
