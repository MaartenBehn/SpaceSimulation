#pragma once

#define RandFloat(x) (std::rand() % (x * 2)) - x
#define LogVec3(vec) std::cout << "X: " << vec.x << " Y: " << vec.y << " Z: " << vec.z << std::endl

class Knot;