#include "display.h"
#include "shader.h"
#include "mesh.h"
#include "texture.h"
#include <iostream>

int main(){
	std::string windowName = "tst";
	Display display(800, 600, windowName);	

	//executable is in bin directory
	Shader shader("../src/res/shaders/basicShader");

	Vertex vertices[] = { Vertex(glm::vec3(-0.5, -0.5, 0), glm::vec2(-0.5, -0.5)),
						Vertex(glm::vec3(0, 0.5, 0), glm::vec2(0.0, 0.5)),
						Vertex(glm::vec3(0.5, -0.5, 0), glm::vec2(0.5, -0.5)) };

	Mesh mesh(vertices, sizeof(vertices)/sizeof(vertices[0]));

	Texture texture("../src/res/textures/wood.jpeg");

	while (!display.IsClosed()){
		display.Clear(0.0f, 0.0f, 0.0f, 1.0f);
		shader.Bind();
		texture.Bind(0);
		mesh.Draw();	
		display.Update();
	}
	return 0;
}
