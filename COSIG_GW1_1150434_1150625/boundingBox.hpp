//
// Created by Fábio Lourenço on 2019-04-09.
//

#ifndef COSIG_GW1_1150434_1150625_BOUNDINGBOX_H
#define COSIG_GW1_1150434_1150625_BOUNDINGBOX_H

#include <stdio.h>
#include <iostream>

#include "vec3.hpp"
#include "ray.hpp"

class BoundingBox{

public:

    vec3 pMin;
    vec3 pMax;

    BoundingBox(
            vec3 pMin,
            vec3 pMax
    );

    virtual bool hit_object(ray &ray);
};


#endif //COSIG_GW1_1150434_1150625_BOUNDINGBOX_HPP
