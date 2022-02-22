#include "display.h"
#include "shader.h"
#include "mesh.h"
#include "texture.h"
#include "transform.h"
#include <iostream>

int main(){
	std::string windowName = "tst";
	gfx::Display display(800, 600, windowName);	

	//executable is in bin directory
	gfx::Shader shader("../src/res/shaders/basicShader");

	gfx::Vertex vertices[] = {gfx::Vertex(glm::vec3(-0.5, -0.5, 0), glm::vec2(-0.5, -0.5)),
						gfx::Vertex(glm::vec3(0, 0.5, 0), glm::vec2(0.0, 0.5)),
						gfx::Vertex(glm::vec3(0.5, -0.5, 0), glm::vec2(0.5, -0.5)) };

	gfx::Mesh mesh(vertices, sizeof(vertices)/sizeof(vertices[0]));

	gfx::Texture texture("../src/res/textures/wood.jpeg");

	gfx::Transform transform;

	float counter = 0.0f;
	float inc = 0.03f;

	while (!display.IsClosed()){
		display.Clear(0.0f, 0.0f, 0.0f, 1.0f);
		float cosCounter = cosf(counter);
		transform.GetPos().x = sinf(counter);
		transform.GetPos().y = cosf(counter);
		transform.GetRot().z += (inc * 500) * 1/180;
		transform.GetRot().x += (inc * 500) * 1/180;
		transform.GetRot().y += (inc * 500) * 1/180;
		transform.SetScale(glm::vec3(cosCounter, cosCounter, cosCounter));
		shader.Bind();
		texture.Bind(0);
		shader.Update(transform);
		mesh.Draw();	
		display.Update();
		counter += inc;
	}
	return 0;
}
