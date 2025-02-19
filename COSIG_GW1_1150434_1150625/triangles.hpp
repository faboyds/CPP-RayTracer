//
//  triangles.hpp
//  COSIG_GW1_1150434_1150625
//
//  Created by Fábio Lourenço on 20/02/2019.
//  Copyright © 2019 Fábio Lourenço. All rights reserved.
//

#ifndef triangles_hpp
#define triangles_hpp

#include <stdio.h>
#include <iostream>
#include <vector>

#include "triangle.hpp"
#include "sceneObject.hpp"

class Triangles : public SceneObject{
    
public:

    std::vector<Triangle> triangles;

    Triangles(
              Transformation &transformation,
              std::vector<Triangle> triangles
           );

    virtual double hit_object(ray &ray, vec3 &normal, Material &material);
    virtual double hit_object(ray &ray);
    
    friend std::ostream& operator<<(std::ostream&, const Triangles&);
};



#endif /* triangles_hpp */
