//
//  vertex.hpp
//  COSIG_GW1_1150434_1150625
//
//  Created by Fábio Lourenço on 20/02/2019.
//  Copyright © 2019 Fábio Lourenço. All rights reserved.
//

#ifndef vertex_hpp
#define vertex_hpp

#include <stdio.h>
#include <iostream>

class Vertex {
    
public:
    double x;
    double y;
    double z;
    
    Vertex(double x, double y, double z);
    
    friend std::ostream& operator<<(std::ostream&, const Vertex&);
};

#endif /* vertex_hpp */
