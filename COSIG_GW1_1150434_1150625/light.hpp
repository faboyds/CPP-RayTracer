//
//  light.hpp
//  COSIG_GW1_1150434_1150625
//
//  Created by Fábio Lourenço on 20/02/2019.
//  Copyright © 2019 Fábio Lourenço. All rights reserved.
//

#ifndef light_hpp
#define light_hpp

#include <stdio.h>
#include <iostream>

#include "transformation.hpp"

class Light {
    
public:
    Transformation &transformation;

    double red = 0;
    double green = 0;
    double blue = 0;
    
    Light();
    
    Light(
          Transformation &transformation,
          double red,
          double green,
          double blue);
    
    friend std::ostream& operator<<(std::ostream&, const Light&);
};

#endif /* light_hpp */
