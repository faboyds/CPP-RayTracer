//
//  box.hpp
//  COSIG_GW1_1150434_1150625
//
//  Created by Fábio Lourenço on 20/02/2019.
//  Copyright © 2019 Fábio Lourenço. All rights reserved.
//

#ifndef box_hpp
#define box_hpp

#include <stdio.h>
#include <iostream>

#include "material.hpp"
#include "sceneObject.hpp"

class Box : public SceneObject{
    
public:
        
    Box(
        Transformation &transformation,
        Material material
        );

    virtual double hit_object(ray &ray, vec3 &normal);
    virtual double hit_object(ray &ray);
    
    friend std::ostream& operator<<(std::ostream&, const Box&);
};

#endif /* box_hpp */
