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
#include "ray.hpp"
#include "boundingBox.hpp"

class SceneObject {
    
public:
    Transformation &transformation;
    Material material;
    BoundingBox boundingBox = BoundingBox(vec3(-9999,-9999,-9999), vec3(9999,9999,9999));

    SceneObject();
	virtual ~SceneObject() { }
    
    SceneObject(
                Transformation &transformation
                );
    
    SceneObject(
                Transformation &transformation,
                Material material
                );

    virtual double hit_object(ray &, vec3 &) { return -1; };
    virtual double hit_object(ray &, vec3 &, Material &) { return -1; };
    virtual double hit_object(ray &) { return -1; };
    
    friend std::ostream& operator<<(std::ostream&, const SceneObject&);
};

#endif /* sceneObject_hpp */
