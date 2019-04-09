//
//  sphere.hpp
//  COSIG_GW1_1150434_1150625
//
//  Created by Fábio Lourenço on 20/02/2019.
//  Copyright © 2019 Fábio Lourenço. All rights reserved.
//

#ifndef sphere_hpp
#define sphere_hpp

#include <stdio.h>
#include <iostream>

#include "material.hpp"
#include "sceneObject.hpp"
#include "boundingBox.hpp"

class Sphere : public SceneObject{
    
public:

    BoundingBox boundingBox = BoundingBox(vec3(-9999,-9999,-9999), vec3(9999,9999,9999));
    
    Sphere(
        Transformation &transformation,
        Material material
        );

    virtual double hit_object(ray &ray, vec3 &normal);
    virtual double hit_object(ray &ray);
    
    friend std::ostream& operator<<(std::ostream&, const Sphere&);
};


#endif /* sphere_hpp */
