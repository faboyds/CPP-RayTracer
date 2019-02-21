#include "camera.hpp"

Camera::Camera()
{
}

Camera::Camera(Transformation transformation, double distance, double field_of_view) :
	transformation(transformation),
	distance(distance),
	field_of_view(field_of_view)
{
}

std::ostream& operator<<(std::ostream &strm, const Camera &c) {
	return strm << "Camera( transformation: " << c.transformation << ", distance: " << c.distance << ", field_of_view: " << c.field_of_view << " )";
}
