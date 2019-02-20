//
//  sceneObject.hpp
//  COSIG_GW1_1150434_1150625
//
//  Created by Fábio Lourenço on 20/02/2019.
//  Copyright © 2019 Fábio Lourenço. All rights reserved.
//

#ifndef sceneObject_hpp
#define sceneObject_hpp

#include <stdio.h>
#include <iostream>

#include "transformation.hpp"
#include "material.hpp"

class SceneObject {
    
public:
    Transformation transformation;
    Material material;
    
    SceneObject();
    
    SceneObject(
        Transformation transformation,
        Material material
        );
    
    friend std::ostream& operator<<(std::ostream&, const SceneObject&);
};

#endif /* sceneObject_hpp */
