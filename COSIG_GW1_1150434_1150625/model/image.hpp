//
//  image.hpp
//  COSIG_GW1_1150434_1150625
//
//  Created by Fábio Lourenço on 20/02/2019.
//  Copyright © 2019 Fábio Lourenço. All rights reserved.
//

#ifndef image_hpp
#define image_hpp

#include <stdio.h>
#include <iostream>

class Image {
    
public:
    double width = 0;
    double height = 0;
    
    double red = 0;
    double green = 0;
    double blue = 0;
    
    Image();
    
    Image(
          double width,
          double height,
          double red,
          double green,
          double blue);
    
    friend std::ostream& operator<<(std::ostream&, const Image&);
};

#endif /* image_hpp */
