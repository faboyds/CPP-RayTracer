//
//  material.hpp
//  COSIG_GW1_1150434_1150625
//
//  Created by Fábio Lourenço on 20/02/2019.
//  Copyright © 2019 Fábio Lourenço. All rights reserved.
//

#ifndef material_hpp
#define material_hpp

#include <stdio.h>
#include <iostream>

class Material {
    
public:
    double red;
    double green;
    double blue;
    
    double ambient;
    double diffuse;
    double reflection;
    double refractionCoefficient;
    double refractionIndex;
    
    Material(double red,
             double green,
             double blue,
             double ambient,
             double diffuse,
             double reflection,
             double refractionCoefficient,
             double refractionIndex);
    
    friend std::ostream& operator<<(std::ostream&, const Material&);
};

#endif /* material_hpp */
