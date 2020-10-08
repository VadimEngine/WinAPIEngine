#include "GraphicsOpenGL.h"

#include "RenderableMesh.h"
#include <SOIL.h>




GraphicsOpenGL::GraphicsOpenGL(HWND hWnd) {
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


	image = SOIL_load_image("Images\\font.png", &width, &height, 0, SOIL_LOAD_RGBA);
	charKeyMap.insert({ 'A', glm::vec2(0,0) });
	charKeyMap.insert({ 'B', glm::vec2(1,0) });
	charKeyMap.insert({ 'C', glm::vec2(2,0) });
	charKeyMap.insert({ 'D', glm::vec2(3,0) });
	charKeyMap.insert({ 'E', glm::vec2(4,0) });
	charKeyMap.insert({ 'F', glm::vec2(5,0) });
	charKeyMap.insert({ 'G', glm::vec2(6,0) });
	charKeyMap.insert({ 'H', glm::vec2(7,0) });
	charKeyMap.insert({ 'I', glm::vec2(8,0) });
	charKeyMap.insert({ 'J', glm::vec2(9,0) });
	charKeyMap.insert({ 'K', glm::vec2(10,0) });
	charKeyMap.insert({ 'L', glm::vec2(11,0) });
	charKeyMap.insert({ 'M', glm::vec2(12,0) });
	charKeyMap.insert({ 'N', glm::vec2(13,0) });
	charKeyMap.insert({ 'O', glm::vec2(14,0) });
	charKeyMap.insert({ 'P', glm::vec2(15,0) });
	charKeyMap.insert({ 'Q', glm::vec2(16,0) });
	charKeyMap.insert({ 'R', glm::vec2(17,0) });
	charKeyMap.insert({ 'S', glm::vec2(18,0) });
	charKeyMap.insert({ 'T', glm::vec2(19,0) });
	charKeyMap.insert({ 'U', glm::vec2(20,0) });
	charKeyMap.insert({ 'V', glm::vec2(21,0) });
	charKeyMap.insert({ 'W', glm::vec2(22,0) });
	charKeyMap.insert({ 'X', glm::vec2(23,0) });
	charKeyMap.insert({ 'Y', glm::vec2(24,0) });
	charKeyMap.insert({ 'Z', glm::vec2(25,0) });

	charKeyMap.insert({ '.', glm::vec2(26,0) });
	charKeyMap.insert({ ',', glm::vec2(27,0) });

	charKeyMap.insert({ 'a', glm::vec2(0,1) });
	charKeyMap.insert({ 'b', glm::vec2(1,1) });
	charKeyMap.insert({ 'c', glm::vec2(2,1) });
	charKeyMap.insert({ 'd', glm::vec2(3,1) });
	charKeyMap.insert({ 'e', glm::vec2(4,1) });
	charKeyMap.insert({ 'f', glm::vec2(5,1) });
	charKeyMap.insert({ 'g', glm::vec2(6,1) });
	charKeyMap.insert({ 'h', glm::vec2(7,1) });
	charKeyMap.insert({ 'i', glm::vec2(8,1) });
	charKeyMap.insert({ 'j', glm::vec2(9,1) });
	charKeyMap.insert({ 'k', glm::vec2(10,1) });
	charKeyMap.insert({ 'l', glm::vec2(11,1) });
	charKeyMap.insert({ 'm', glm::vec2(12,1) });
	charKeyMap.insert({ 'n', glm::vec2(13,1) });
	charKeyMap.insert({ 'o', glm::vec2(14,1) });
	charKeyMap.insert({ 'p', glm::vec2(15,1) });
	charKeyMap.insert({ 'q', glm::vec2(16,1) });
	charKeyMap.insert({ 'r', glm::vec2(17,1) });
	charKeyMap.insert({ 's', glm::vec2(18,1) });
	charKeyMap.insert({ 't', glm::vec2(19,1) });
	charKeyMap.insert({ 'u', glm::vec2(20,1) });
	charKeyMap.insert({ 'v', glm::vec2(21,1) });
	charKeyMap.insert({ 'w', glm::vec2(22,1) });
	charKeyMap.insert({ 'x', glm::vec2(23,1) });
	charKeyMap.insert({ 'y', glm::vec2(24,1) });
	charKeyMap.insert({ 'z', glm::vec2(25,1) });

	charKeyMap.insert({ '0', glm::vec2(0,2) });
	charKeyMap.insert({ '1', glm::vec2(1,2) });
	charKeyMap.insert({ '2', glm::vec2(2,2) });
	charKeyMap.insert({ '3', glm::vec2(3,2) });
	charKeyMap.insert({ '4', glm::vec2(4,2) });
	charKeyMap.insert({ '5', glm::vec2(5,2) });
	charKeyMap.insert({ '6', glm::vec2(6,2) });
	charKeyMap.insert({ '7', glm::vec2(7,2) });
	charKeyMap.insert({ '8', glm::vec2(8,2) });
	charKeyMap.insert({ '9', glm::vec2(9,2) });
	charKeyMap.insert({ ':', glm::vec2(14,2) });

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
	ourShader = new ShaderOpenGL(  "ShadersOpenGL/basic.vert", "ShadersOpenGL/basic.frag");
	imageShader = new ShaderOpenGL("ShadersOpenGL/image.vert", "ShadersOpenGL/image.frag");
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

	//Create image data
	glGenVertexArrays(1, &imageVAO);
	glGenBuffers(1, &imageVBO);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	glGenVertexArrays(1, &imageVAO);
	glGenBuffers(1, &imageVBO);
}

void GraphicsOpenGL::draw() {

	//addMeshVerts(&theMesh);
	bindVertices();

	glClearColor(backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);

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

	glDrawElements(GL_TRIANGLES, theIndices.size(), GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);


	//draw image

	glBindVertexArray(imageVAO);

	glBindBuffer(GL_ARRAY_BUFFER, imageVBO);
	glBufferData(GL_ARRAY_BUFFER, imageVertices.size() * sizeof(GLfloat), imageVertices.data(), GL_DYNAMIC_DRAW);
	//position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	//color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	//Texture cord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	imageShader->Use();//should use after bind?

	glBindVertexArray(imageVAO);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(glGetUniformLocation(imageShader->Program, "ourTexture"), 0);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//Wireframe
	//glDrawArrays(GL_TRIANGLES, 0, vertList.size()/3);
	//elements might use a EBO
	//glDrawElements(GL_TRIANGLES, vertList.size() / 6, GL_UNSIGNED_INT, 0);
	glDrawArrays(GL_TRIANGLES, 0, imageVertices.size() / 8);

	glBindVertexArray(0);//Unbind

	imageVertices.clear();






	SwapBuffers(hDC);			/* nop if singlebuffered */

	//Clear vertices
	clearVertices();
}


void GraphicsOpenGL::addVertices(std::vector<glm::vec3> vertices, vector<unsigned int> indicies) {
	unsigned int oldSize = theVertices.size();
	
	for (int i = 0; i < vertices.size(); i++) {
		//add coordinate
		theVertices.push_back(vertices[i].x);
		theVertices.push_back(vertices[i].y);
		theVertices.push_back(vertices[i].z);
		//add color
		float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		float g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		float b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		theVertices.push_back(r);
		theVertices.push_back(g);
		theVertices.push_back(b);
	}

	for (int i = 0; i < indicies.size(); i++) {
		//add indicies
		unsigned int newIndex = indicies[i] + oldSize;
		theIndices.push_back(newIndex);
	}
}

void GraphicsOpenGL::bindVertices() {
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, theVertices.size() * sizeof(GLfloat), theVertices.data(), GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, theIndices.size() * sizeof(unsigned int), theIndices.data(), GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0); //// Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

	glBindVertexArray(0); // Unbind VAO
}

void GraphicsOpenGL::addMeshVerts(MeshGDI& inputMesh) {
	unsigned int oldSize = theVertices.size()/6;//Divide by 6 becuase indices are for the 
										      //begining of the "vertices" whihc consist of
											  //x y z r g b

	for (int i = 0; i < inputMesh.vertices.size(); i++) {
		//add coordinate
		theVertices.push_back(inputMesh.vertices[i].x);
		theVertices.push_back(inputMesh.vertices[i].y);
		theVertices.push_back(inputMesh.vertices[i].z);
		//add color
		int theColor = inputMesh.color;
		float red = (theColor >> 16) & 0x000000FF;
		float green = (theColor >> 8) & 0x000000FF;
		float blue = (theColor) & 0x000000FF;

		red /= float(255.0f);
		green /= float(255.0f);
		blue /= float(255.0f);

		theVertices.push_back(red);
		theVertices.push_back(green);
		theVertices.push_back(blue);
	}

	for (int i = 0; i < inputMesh.indicies.size(); i++) {
		unsigned int newIndex = inputMesh.indicies[i] + oldSize;
		theIndices.push_back(newIndex);
	}
}


void GraphicsOpenGL::clearVertices() {
	theVertices.clear();
	theIndices.clear();
}


void GraphicsOpenGL::setBackGroundColor(glm::vec4 theColor) {
	this->backgroundColor = theColor;
}



void GraphicsOpenGL::startFrame() {
	clearVertices();
}

void GraphicsOpenGL::drawFrame() {
	bindVertices();

	glClearColor(backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	ourShader->Use();

	glm::mat4 view(1.0f);
	//view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	view = glm::lookAt(camera->cameraPos, camera->cameraPos + camera->cameraFront, camera->cameraUp);



	glm::mat4 projection(1.0f);
	projection = glm::perspective(fov, (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);

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

	glDrawElements(GL_TRIANGLES, theIndices.size(), GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);




	//draw image

	glBindVertexArray(imageVAO);

	glBindBuffer(GL_ARRAY_BUFFER, imageVBO);
	glBufferData(GL_ARRAY_BUFFER, imageVertices.size() * sizeof(GLfloat), imageVertices.data(), GL_DYNAMIC_DRAW);
	//position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	//color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	//Texture cord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	imageShader->Use();//should use after bind?

	glBindVertexArray(imageVAO);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(glGetUniformLocation(imageShader->Program, "ourTexture"), 0);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//Wireframe
	//glDrawArrays(GL_TRIANGLES, 0, vertList.size()/3);
	//elements might use a EBO
	//glDrawElements(GL_TRIANGLES, vertList.size() / 6, GL_UNSIGNED_INT, 0);
	glDrawArrays(GL_TRIANGLES, 0, imageVertices.size() / 8);

	glBindVertexArray(0);//Unbind




	SwapBuffers(hDC);			/* nop if singlebuffered */

	imageVertices.clear();
}

void GraphicsOpenGL::drawMesh(RenderableMesh& theMesh) {
	unsigned int oldSize = theVertices.size() / 6;

	for (int i = 0; i < theMesh.vertices.size(); i++) {
		//add coordinate
		theVertices.push_back(theMesh.vertices[i].x);
		theVertices.push_back(theMesh.vertices[i].y);
		theVertices.push_back(theMesh.vertices[i].z);
		//add color
		//int theColor = inputMesh.color;
		int theColor = theMesh.color;
		float red = (theColor >> 16) & 0x000000FF;
		float green = (theColor >> 8) & 0x000000FF;
		float blue = (theColor) & 0x000000FF;

		red /= float(255.0f);
		green /= float(255.0f);
		blue /= float(255.0f);

		theVertices.push_back(red);
		theVertices.push_back(green);
		theVertices.push_back(blue);
	}

	for (int i = 0; i < theMesh.indicies.size(); i++) {
		unsigned int newIndex = theMesh.indicies[i] + oldSize;
		theIndices.push_back(newIndex);
	}
}

void GraphicsOpenGL::setCamera(Camera* camera) {
	this->camera = camera;
}

std::string GraphicsOpenGL::toString() {
	return "OpenGL";
}

void GraphicsOpenGL::drawString(std::string theString, float x, float y) {
	// 0,0 maps to -1, -1:
	//640,480 maps to 1,1
	// 320, 240 maps to 0,0:		x - (640/2))640

	x = (x - (640.0f/2.0f))/(640.0f/2.0f);
	y = -(y - (480.0f / 2.0f)) / (480 / 2.0f);


	for (int i = 0; i < theString.size(); i++) {
		if (charKeyMap.find(theString[i]) != charKeyMap.end()) {
			glm::vec2 charLoc = charKeyMap[theString[i]];
			renderSubImage(x + i * .03f, y, charLoc.x, charLoc.y, 6, 8, image);
		}
	}
}

void GraphicsOpenGL::renderImage(float x, float y) {

}

void GraphicsOpenGL::renderSubImage(float x, float y, float subX,
	float subY, float subWidth,
	float subHeight, unsigned char* theImage) {

	float size = 1.0f;
	glm::vec3 position = glm::vec3(x, y, 0);
	glm::vec3 color = glm::vec3(1,1,1);

	float width = (.06f / 2.0f) * size;
	float height = (.08f / 2.0f) * size;
	int texWidth = this->width;
	int texHeight = this->height;



	//add point 1 top left
	imageVertices.push_back(position.x);
	imageVertices.push_back(position.y);
	imageVertices.push_back(position.z);
	//add color
	imageVertices.push_back(color.x);
	imageVertices.push_back(color.y);
	imageVertices.push_back(color.z);
	//add texture
	imageVertices.push_back(0 + (subX * (subWidth / texWidth)));//good
	imageVertices.push_back(1 - (subY * (subHeight / texHeight)));

	//add point 2 bottom left
	imageVertices.push_back(position.x);
	imageVertices.push_back(position.y - height);
	imageVertices.push_back(position.z);
	//add color
	imageVertices.push_back(color.x);
	imageVertices.push_back(color.y);
	imageVertices.push_back(color.z);
	//add texture

	imageVertices.push_back(0 + (subX * (subWidth / texWidth)));
	imageVertices.push_back(1 - ((subY + 1) * (subHeight / texHeight)));

	//add point 3 bottom right
	imageVertices.push_back(position.x + width);
	imageVertices.push_back(position.y - height);
	imageVertices.push_back(position.z);
	//add color
	imageVertices.push_back(color.x);
	imageVertices.push_back(color.y);
	imageVertices.push_back(color.z);
	//add texture
	imageVertices.push_back(0 + ((subX + 1) * (subWidth / texWidth)));
	imageVertices.push_back(1 - ((subY + 1) * (subHeight / texHeight)));

	//add point 4 bottom right
	imageVertices.push_back(position.x + width);
	imageVertices.push_back(position.y - height);
	imageVertices.push_back(position.z);
	//add color
	imageVertices.push_back(color.x);
	imageVertices.push_back(color.y);
	imageVertices.push_back(color.z);
	//add texture
	imageVertices.push_back(0 + ((subX + 1) * (subWidth / texWidth)));
	imageVertices.push_back(1 - ((subY + 1) * (subHeight / texHeight)));

	//add point 5 top right
	imageVertices.push_back(position.x + width);
	imageVertices.push_back(position.y);
	imageVertices.push_back(position.z);
	//add color
	imageVertices.push_back(color.x);
	imageVertices.push_back(color.y);
	imageVertices.push_back(color.z);
	//add texture
	imageVertices.push_back(0 + ((subX + 1) * (subWidth / texWidth)));
	imageVertices.push_back(1 - (subY * (subHeight / texHeight)));

	//add point 6 top left
	imageVertices.push_back(position.x);
	imageVertices.push_back(position.y);
	imageVertices.push_back(position.z);
	//add color
	imageVertices.push_back(color.x);
	imageVertices.push_back(color.y);
	imageVertices.push_back(color.z);
	//add texture
	imageVertices.push_back(0 + (subX * (subWidth / texWidth)));
	imageVertices.push_back(1 - (subY * (subHeight / texHeight)));
}