#pragma once


#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

#include <GL/glew.h>

class ShaderOpenGL {
public:
	GLuint Program;

	ShaderOpenGL(const GLchar* vertexSourcePath, const GLchar* fragmentSourcePath);

	void Use();
};
