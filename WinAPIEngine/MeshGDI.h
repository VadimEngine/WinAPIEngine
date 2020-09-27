#pragma once

#include "vector"
#include "Vec3.h"

class MeshGDI {

public:

    std::vector<Vec3> vertices;
    std::vector<unsigned int> indicies;
    int color;

    //ADD A FLOAT SCALE SO THE MESH CAN BE RESIZED WHEN LOADED

    MeshGDI(const char* path);


    MeshGDI(const char* path, int color);

    MeshGDI(const char* path, int color, float scale);

    MeshGDI(std::vector<Vec3> vertices, std::vector<unsigned int> indicies, int color);


};

