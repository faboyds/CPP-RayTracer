//
//  sceneObject.cpp
//  COSIG_GW1_1150434_1150625
//
//  Created by Fábio Lourenço on 20/02/2019.
//  Copyright © 2019 Fábio Lourenço. All rights reserved.
//

#include "sceneObject.hpp"

/*SceneObject::SceneObject(): transformation(), material()
{
}*/
SceneObject::SceneObject(Transformation &transformation): transformation(transformation), material()
{
}
SceneObject::SceneObject(Transformation &transformation, Material material): transformation(transformation), material(material)
{
}

std::ostream& operator<<(std::ostream &strm, const SceneObject &so) {
    return strm << "Scene Object( transformation: " << so.transformation << ", material: " << so.material << " )";
}
