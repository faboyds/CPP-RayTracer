#include "../model/material.hpp"
#include "../model/transformation.hpp"
#include "../model/camera.hpp"
#include "../model/image.hpp"
#include "../model/light.hpp"
#include "../model/box.hpp"
#include "../model/sphere.hpp"
#include "../model/triangles.hpp"
#include "../model/vertex.hpp"
#include "../model/sceneObject.hpp"


namespace import_file {
	void importScene(Image &image,
		std::vector<Material> &materials,
		std::vector<Transformation> &transformations,
		std::vector<Light> &lights,
		std::vector<SceneObject> &objects,
		Camera camera);

	void get_image_information(Image &image);
	void get_materials_information(std::vector<Material> &materials);
	void get_transformation_information(std::vector<Transformation> &transformations);
	void get_lights_information(std::vector<Light> &lights, std::vector<Transformation> &transformations);
	void get_triangles_information(std::vector<SceneObject> &objects, std::vector<Transformation> &transformations, std::vector<Material> &materials);
	void get_box_information(std::vector<SceneObject> &objects, std::vector<Transformation> &transformations, std::vector<Material> &materials);
	void get_sphere_information(std::vector<SceneObject> &objects, std::vector<Transformation> &transformations, std::vector<Material> &materials);
	void get_camera_information(Camera &camera, std::vector<Transformation> &transformations);

}


