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

#include "transformation.hpp"
#include "material.hpp"
#include "sceneObject.hpp"
#include "ray.hpp"

class Box : public SceneObject{
    
public:
        
    Box(
        Transformation transformation,
        Material material
        );

	//TODO change accordingly when the object is hit (parameters)
	virtual bool hit_object(const ray&);
    
    friend std::ostream& operator<<(std::ostream&, const Box&);
};

#endif /* box_hpp */
