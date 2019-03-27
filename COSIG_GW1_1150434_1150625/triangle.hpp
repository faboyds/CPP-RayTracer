//
//  triangle.hpp
//  COSIG_GW1_1150434_1150625
//
//  Created by Fábio Lourenço on 21/02/2019.
//  Copyright © 2019 Fábio Lourenço. All rights reserved.
//

#ifndef triangle_hpp
#define triangle_hpp

#include <stdio.h>
#include <iostream>
#include <vector>

#include "material.hpp"
#include "vertex.hpp"
#include "sceneObject.hpp"

class Triangle {
    
public:
    
    Material material;
    std::vector<Vertex> vertices;
    vec3 normalVector;
    
    Triangle(
              Material material,
              std::vector<Vertex> vertices
              );

    void buildNormalVector();

    friend std::ostream& operator<<(std::ostream&, const Triangle&);
};



#endif /* triangle_hpp */
