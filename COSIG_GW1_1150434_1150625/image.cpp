//
//  image.cpp
//  COSIG_GW1_1150434_1150625
//
//  Created by Fábio Lourenço on 20/02/2019.
//  Copyright © 2019 Fábio Lourenço. All rights reserved.
//

#include "image.hpp"

Image::Image()
{
}

Image::Image(int width, int height,
             double red, double green, double blue): width(width), height(height), red(red), green(green), blue(blue)
{
}

std::ostream& operator<<(std::ostream &strm, const Image &i) {
    return strm << "Image( width: " << i.width << ", height: " << i.height << ", red: " << i.red << ", green: " << i.green << ", blue: " << i.blue << " )";
}
