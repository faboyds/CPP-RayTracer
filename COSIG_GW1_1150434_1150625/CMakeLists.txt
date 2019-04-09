cmake_minimum_required(VERSION 3.13)
project(COSIG_GW1_1150434_1150625)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(resources)

add_executable(COSIG_GW1_1150434_1150625
        resources/evaluation_scene.txt
        resources/test_scene.txt
        box.cpp
        box.hpp
        camera.cpp
        camera.hpp
        image.cpp
        image.hpp
        import_file.cpp
        import_file.hpp
        light.cpp
        light.hpp
        main.cpp
        material.cpp
        material.hpp
        ray.hpp
        result.ppm
        sceneObject.cpp
        sceneObject.hpp
        sphere.cpp
        sphere.hpp
        test.ppm
        transformation.cpp
        transformation.hpp
        transformation_utils.hpp
        triangle.cpp
        triangle.hpp
        triangles.cpp
        triangles.hpp
        vec3.hpp
        vertex.cpp
        vertex.hpp
        boundingBox.hpp
        boundingBox.cpp)
