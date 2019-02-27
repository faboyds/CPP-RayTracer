#ifndef hitable_hpp
#define hitable_hpp

#include "ray.hpp"

struct hit_record {
	float t;
	vec3 p;
	vec3 normal;
};

class Hitable {
    
public:
        
	virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const = 0;
};

#endif
