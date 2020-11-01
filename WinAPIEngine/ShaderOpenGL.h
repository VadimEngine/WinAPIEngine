#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>

class ShaderOpenGL {
public:
	GLuint Program;

	ShaderOpenGL(const GLchar* vertexSourcePath, const GLchar* fragmentSourcePath);

	void Use();
};
