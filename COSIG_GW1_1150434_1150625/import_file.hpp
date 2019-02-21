#include "material.hpp"
#include "transformation.hpp"
#include "camera.hpp"
#include "image.hpp"
#include "light.hpp"
#include "box.hpp"
#include "sphere.hpp"
#include "triangles.hpp"
#include "vertex.hpp"
#include "sceneObject.hpp"


namespace import_file {
	void importScene(Image &image,
		std::vector<Material> &materials,
		std::vector<Transformation> &transformations,
		std::vector<Light> &lights,
		std::vector<SceneObject> &objects);

}


