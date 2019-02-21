
#ifndef camera_hpp
#define camera_hpp

#include <stdio.h>
#include <iostream>
#include "transformation.hpp"

class Camera {

public:
	Transformation transformation;

	double distance;

	double field_of_view;

	Camera(Transformation transformation,
		double distance,
		double field_of_view);

	friend std::ostream& operator<<(std::ostream&, const Camera&);
};

#endif /* camera_hpp */
