#include "display.h"
#include "shader.h"
#include "mesh.h"
#include <iostream>

int main(){
	std::string windowName = "tst";
	Display display(800, 600, windowName);	

	//executable is in bin directory
	Shader shader("../src/res/shaders/basicShader");

	Vertex vertices[] = { Vertex(glm::vec3(-0.5, -0.5, 0)),
						Vertex(glm::vec3(0, 0.5, 0)),
						Vertex(glm::vec3(0.5, -0.5, 0)) };

	Mesh mesh(vertices, sizeof(vertices)/sizeof(vertices[0]));

	while (!display.IsClosed()){
		display.Clear(0.0f, 1.0f, 1.0f, 1.0f);
		shader.Bind();
		mesh.Draw();	
		display.Update();
	}
	return 0;
}
