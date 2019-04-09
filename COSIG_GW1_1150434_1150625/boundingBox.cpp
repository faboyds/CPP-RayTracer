//
// Created by Fábio Lourenço on 2019-04-09.
//

#include "boundingBox.hpp"

BoundingBox::BoundingBox(vec3 pMin, vec3 pMax): pMin(pMin), pMax(pMax)
{
}

inline bool BoundingBox::hit_object(ray &r) {

    // If Dx=0, then ray is parallel
    if (r.direction().x() == 0) return false;

    // X axis ----------------------------------------------------------------------------------------------------------
    double tx1 = (pMin.x() - r.origin().x()) / r.direction().x();
    double tx2 = (pMax.x() - r.origin().x()) / r.direction().x();

    if (tx1 > tx2) {
        double temp = tx1;
        tx1 = tx2;
        tx2 = temp;
    }

    // Y axis ----------------------------------------------------------------------------------------------------------
    double ty1 = (pMin.y() - r.origin().y()) / r.direction().y();
    double ty2 = (pMax.y() - r.origin().y()) / r.direction().y();

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
    double tz1 = (pMin.z() - r.origin().z()) / r.direction().z();
    double tz2 = (pMax.z() - r.origin().z()) / r.direction().z();

    if (tz1 > tz2) {
        double temp = tz1;
        tz1 = tz2;
        tz2 = temp;
    }

    if (tnear > tz2 || tz1 > tfar) return false;
    if (tz1 > tnear) tnear = tz1;
    if (tz2 < tfar) tfar = tz2;

    if (tfar < 0) return false;

    return true;
}