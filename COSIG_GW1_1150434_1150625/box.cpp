//
//  box.cpp
//  COSIG_GW1_1150434_1150625
//
//  Created by Fábio Lourenço on 20/02/2019.
//  Copyright © 2019 Fábio Lourenço. All rights reserved.
//

#include "box.hpp"

Box::Box(Transformation &transformation, Material material): SceneObject(transformation, material)
{
}

inline double Box::hit_object(ray &r, vec3 &normal) {

    double maxCoord = 0.5;

    // If Dx=0, then ray is parallel
    if (r.direction().x() == 0) return -1;

    // X axis ----------------------------------------------------------------------------------------------------------
    double tx1 = (-maxCoord - r.origin().x()) / r.direction().x();
    double tx2 = (maxCoord - r.origin().x()) / r.direction().x();

    if (tx1 > tx2) {
        double temp = tx1;
        tx1 = tx2;
        tx2 = temp;
    }

    // Y axis ----------------------------------------------------------------------------------------------------------
    double ty1 = (-maxCoord - r.origin().y()) / r.direction().y();
    double ty2 = (maxCoord - r.origin().y()) / r.direction().y();

    if (ty1 > ty2) {
        double temp = ty1;
        ty1 = ty2;
        ty2 = temp;
    }

    // misses the box
    if (tx1 > ty2 || ty1 > tx2) {
        return -1;
    }

    double tnear;
    double tfar;

    tnear = (tx1 > ty1) ? tx1 : ty1;
    tfar = (tx2 < ty2) ? tx2 : ty2;

    // Z axis ----------------------------------------------------------------------------------------------------------
    double tz1 = (-maxCoord - r.origin().z()) / r.direction().z();
    double tz2 = (maxCoord - r.origin().z()) / r.direction().z();

    if (tz1 > tz2) {
        double temp = tz1;
        tz1 = tz2;
        tz2 = temp;
    }

    if (tnear > tz2 || tz1 > tfar) return -1;
    if (tz1 > tnear) tnear = tz1;
    if (tz2 < tfar) tfar = tz2;

    if (tfar < 0) return -1;

    vec3 point = r.point_at_parameter(tnear);

    double ep = 0.00001;

    if (fabs(point.x() + maxCoord) < ep) {
        normal = vec3(-1, 0, 0);
    } else if (fabs(point.x() - maxCoord) < ep) {
        normal = vec3(1, 0, 0);
    } else if (fabs(point.y() + maxCoord) < ep) {
        normal = vec3(0, -1, 0);
    } else if (fabs(point.y() - maxCoord) < ep) {
        normal = vec3(0, -1, 0);
    } else if (fabs(point.z() + maxCoord) < ep) {
        normal = vec3(0, 0, -1);
    } else if (fabs(point.z() - maxCoord) < ep) {
        normal = vec3(0, 0, 1);
    }

    return tnear;
}

inline double Box::hit_object(ray &r) {
    vec3 norm;
    return hit_object(r, norm);
}

std::ostream& operator<<(std::ostream &strm, const Box &b) {
    return strm << "Box( transformation: " << b.transformation << ", material: " << b.material << " )";
}
