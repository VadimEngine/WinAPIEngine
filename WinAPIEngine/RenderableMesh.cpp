#include "RenderableMesh.h"


RenderableMesh::RenderableMesh() {
}


RenderableMesh::RenderableMesh(const char* path, int color)
    :color(color){
    float scale = 1.0;
    std::ifstream myfile(path);

    std::string line;
    char type;

    while (myfile >> type) {
        OutputDebugString(line.c_str());
        if (type == 'v') {
            float x;
            float y;
            float z;
            myfile >> x >> y >> z;
            vertices.push_back(glm::vec3(x * scale, y * scale, z * scale));
        }else if (type == 'f') {
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

RenderableMesh::RenderableMesh(std::vector<glm::vec3> vertices, std::vector<unsigned int> indices, int color)
    :color(color) {
    this->vertices = vertices;
    this->indicies = indices;
}

void RenderableMesh::renderOpenGL(GraphicsOpenGL& graphics, Camera cam) {
    unsigned int oldSize = graphics.theVertices.size() / 6;

    for (unsigned int i = 0; i < vertices.size(); i++) {
        //add coordinate
        graphics.theVertices.push_back(vertices[i].x);
        graphics.theVertices.push_back(vertices[i].y);
        graphics.theVertices.push_back(vertices[i].z);
        //add color
        //int theColor = inputMesh.color;
        int theColor = this->color;
        int red = (theColor >> 16) & 0x000000FF;
        int green = (theColor >> 8) & 0x000000FF;
        int blue = (theColor) & 0x000000FF;

        graphics.theVertices.push_back(red/255.0f);
        graphics.theVertices.push_back(green/255.0f);
        graphics.theVertices.push_back(blue/255.0f);
    }

    for (unsigned int i = 0; i < indicies.size(); i++) {
        unsigned int newIndex = indicies[i] + oldSize;
        graphics.theIndices.push_back(newIndex);
    }
}

//renderDirect3D(graphics, Camera)
void RenderableMesh::renderDirect3D(GraphicsD3D& graphics, Camera cam) {

}

/*
//renderCustom(Graphics, Camera)
void RenderableMesh::renderCustom(GraphicsGDI& graphics, Camera cam) {
    float scale = 1;
    for (int i = 0; i < indicies.size(); i+=3) {
        unsigned int i1 = indicies[i];
        unsigned int i2 = indicies[i + 1];
        unsigned int i3 = indicies[i + 2];

        Vec3 v1(vertices[i1].x * scale, vertices[i1].y * scale, vertices[i1].z * scale);
        Vec3 v2(vertices[i2].x * scale, vertices[i2].y * scale, vertices[i2].z * scale);
        Vec3 v3(vertices[i3].x * scale, vertices[i3].y * scale, vertices[i3].z * scale);
        
        v1 = Calculator::rotateAroundCenter(v1, cam.pos, cam.dir);
        v2 = Calculator::rotateAroundCenter(v2, cam.pos, cam.dir);
        v3 = Calculator::rotateAroundCenter(v3, cam.pos, cam.dir);

        graphics.drawTriangle(v1,v2, v3, this->color);
        graphics.drawLine(v1, v2, 0x000000);
        graphics.drawLine(v2, v3, 0x000000);
        graphics.drawLine(v3, v1, 0x000000);
    }

}
*/