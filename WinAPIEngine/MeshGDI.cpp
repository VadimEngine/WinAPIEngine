#include "MeshGDI.h"

#include <fstream>
#include <iostream>
#include <string>

#include "CustomWindow.h"

MeshGDI::MeshGDI(const char* path): MeshGDI(path, 0x000000, 1.0f) {}

MeshGDI::MeshGDI(const char* path, int color) : MeshGDI(path, color, 1.0f) {}


MeshGDI::MeshGDI(const char* path, int color, float scale){
    this->color = color;
    std::ifstream myfile(path);

    std::string line;
    char type;

    while (myfile >> type) {
        OutputDebugString(line.c_str());

        //if next == 'v'
        if (type == 'v') {
            float x;
            float y;
            float z;

            myfile >> x >> y >> z;

            vertices.push_back(Vec3(x * scale, y * scale, z * scale));
        }

        if (type == 'f') {
            int i1;
            int i2;
            int i3;

            myfile >> i1 >> i2 >> i3;

            indicies.push_back(i1 - 1);
            indicies.push_back(i2 - 1);
            indicies.push_back(i3 - 1);
        }
    }
}

MeshGDI::MeshGDI(std::vector<Vec3> vertices, std::vector<unsigned int> indicies, int color) {
    this->vertices = vertices;
    this->indicies = indicies;
    this->color = color;
}

