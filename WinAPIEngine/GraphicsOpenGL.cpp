#include "GraphicsOpenGL.h"



GraphicsOpenGL::GraphicsOpenGL(HWND hWnd) 
 : theMesh("Images\\ExportableFox.obj") {
	this->hDC = GetDC(hWnd);

	//MySetPixelFormat(m_hDC);
	
	PIXELFORMATDESCRIPTOR pfd;

	memset(&pfd, 0, sizeof(pfd));
	pfd.nSize = sizeof(pfd);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cDepthBits = 32;
	pfd.cColorBits = 32;

	int pf = ChoosePixelFormat(hDC, &pfd);

	if (pf == 0) {
		MessageBox(NULL, "ChoosePixelFormat() failed:  "
			"Cannot find a suitable pixel format.", "Error", MB_OK);
		return;
	}

	if (SetPixelFormat(hDC, pf, &pfd) == FALSE) {
		MessageBox(NULL, "SetPixelFormat() failed:  "
			"Cannot set format specified.", "Error", MB_OK);
		return;
	}

	DescribePixelFormat(hDC, pf, sizeof(PIXELFORMATDESCRIPTOR), &pfd);



	HGLRC hRC = wglCreateContext(hDC);
	
	
	bool temp = wglMakeCurrent(hDC, hRC);
	init();
}


GraphicsOpenGL::~GraphicsOpenGL() {
	//wglDeleteContext(hRC);
}

void GraphicsOpenGL::init() {
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	GLenum err = glewInit();

	if (GLEW_OK != err)
	{
		/* Problem: glewInit failed, something is seriously wrong. */
		auto temp = glewGetErrorString(err);
	}

	// Define the viewport dimensions
	glViewport(0, 0, WIDTH, HEIGHT);

	// Setup OpenGL options (Z-Buffer)
	glEnable(GL_DEPTH_TEST);

	// Build and compile our shader program
	//Shader ourShader("Shaders/basic.vert", "Shaders/basic.frag");
	ourShader = new ShaderOpenGL("ShadersOpenGL/basic.vert", "ShadersOpenGL/basic.frag");
	
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(sizeof(GLfloat) * 3));


	glBindBuffer(GL_ARRAY_BUFFER, 0); //// Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

	glBindVertexArray(0); // Unbind VAO

	//setVertices2(vertices2, indices2);


	//setVertices();
}

void GraphicsOpenGL::draw() {

	//addMeshVerts(&theMesh);
	setVertices2(vertices2, indices2);


	//Bind vertices
	//Bind end
	//setVertices2(vertices2, indices2);
	//bindVertices();


	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	ourShader->Use();

	glm::mat4 view(1.0f);
	view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

	glm::mat4 projection(1.0f);
	projection = glm::perspective(fov, (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);

	//update shader uniform
	//float timeValue = glfwGetTime();
	float timeValue = 1.0f;
	float sinCalc = sin(timeValue) / 2.0 + 0.5f;
	float cosCalc = cos(timeValue) / 2.0 + 0.5f;

	int vertexColorLocation = glGetUniformLocation(ourShader->Program, "red_color");
	//glUniform1f(vertexColorLocation, sinCalc);

	int shader_x_offset_loc = glGetUniformLocation(ourShader->Program, "x_offset");
	//glUniform1f(shader_x_offset_loc, cosCalc);

	int shader_y_offset_loc = glGetUniformLocation(ourShader->Program, "y_offset");
	//glUniform1f(shader_y_offset_loc, sinCalc);

	int shader_z_offset_loc = glGetUniformLocation(ourShader->Program, "z_offset");
	//glUniform1f(shader_z_offset_loc, sinCalc);


	GLint modelLoc = glGetUniformLocation(ourShader->Program, "model");
	GLint viewLoc = glGetUniformLocation(ourShader->Program, "view");
	GLint projLoc = glGetUniformLocation(ourShader->Program, "projection");

	// Pass the matrices to the shader
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
	glm::mat4 model(1.0f);
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));


	glBindVertexArray(VAO);
	//each vertex is 5 elements of the vertices

	//glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);
	glDrawElements(GL_TRIANGLES, indices2.size(), GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);

	SwapBuffers(hDC);			/* nop if singlebuffered */

	//Clear vertices
	vertices2.clear();
	indices2.clear();
}



void GraphicsOpenGL::setVertices(std::vector<glm::vec3> vertices, std::vector<unsigned int> indicies) {
	
	vertices2.clear();
	indices2.clear();

	for (int i = 0; i < vertices.size(); i++) {
		//add coordinate
		vertices2.push_back(vertices[i].x);
		vertices2.push_back(vertices[i].y);
		vertices2.push_back(vertices[i].z);
		//add color
		float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		float g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		float b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		vertices2.push_back(r);
		vertices2.push_back(g);
		vertices2.push_back(b);
	}

	for (int i = 0; i < indicies.size(); i++) {
		//add indicies
		indices2.push_back(indicies[i]);
	}

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, vertices2.size() * sizeof(GLfloat), vertices2.data(), GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices2.size() * sizeof(unsigned int), indices2.data(), GL_DYNAMIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(sizeof(GLfloat) * 3));

	glBindBuffer(GL_ARRAY_BUFFER, 0); //// Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

	glBindVertexArray(0); // Unbind VAO
}


void GraphicsOpenGL::setVertices2(vector<GLfloat> vertices, vector<unsigned int> indices) {
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0); //// Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

	glBindVertexArray(0); // Unbind VAO
}

void GraphicsOpenGL::addVertices(std::vector<glm::vec3> vertices, vector<unsigned int> indicies) {
	unsigned int oldSize = vertices2.size();
	
	for (int i = 0; i < vertices.size(); i++) {
		//add coordinate
		vertices2.push_back(vertices[i].x);
		vertices2.push_back(vertices[i].y);
		vertices2.push_back(vertices[i].z);
		//add color
		float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		float g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		float b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		vertices2.push_back(r);
		vertices2.push_back(g);
		vertices2.push_back(b);
	}

	for (int i = 0; i < indicies.size(); i++) {
		//add indicies
		unsigned int newIndex = indicies[i] + oldSize;
		indices2.push_back(newIndex);
	}
}



void GraphicsOpenGL::bindVertices() {
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, vertices2.size() * sizeof(GLfloat), vertices2.data(), GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices2.size() * sizeof(unsigned int), indices2.data(), GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0); //// Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

	glBindVertexArray(0); // Unbind VAO
}


/**
	NEED TO BE CAREFUL WHEN ADDING INDICES SINCE THEY REFERENCE THE
	OLD LIST INDCIES NOT THE NEW LIST. POSSILBE SOLUTION IS TO ADD LIST'S 
	OLD SIZE TO EACH INDICES

*/
void GraphicsOpenGL::addMeshVerts(MeshGDI& inputMesh) {
	unsigned int oldSize = vertices2.size()/6;//Divide by 6 becuase indices are for the 
										      //begining of the "vertices" whihc consist of
											  //x y z r g b

	for (int i = 0; i < inputMesh.vertices.size(); i++) {
		//add coordinate
		vertices2.push_back(inputMesh.vertices[i].x);
		vertices2.push_back(inputMesh.vertices[i].y);
		vertices2.push_back(inputMesh.vertices[i].z);
		//add color
		int theColor = inputMesh.color;
		float red = (theColor >> 16) & 0x000000FF;
		float green = (theColor >> 8) & 0x000000FF;
		float blue = (theColor) & 0x000000FF;


		red /= float(255.0f);
		green /= float(255.0f);
		blue /= float(255.0f);


		//float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		//float g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		//float b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		vertices2.push_back(red);
		vertices2.push_back(green);
		vertices2.push_back(blue);
	}

	for (int i = 0; i < inputMesh.indicies.size(); i++) {
		unsigned int newIndex = inputMesh.indicies[i] + oldSize;
		indices2.push_back(newIndex);
	}

	//addVertices(glmVectices, indices2);

}
