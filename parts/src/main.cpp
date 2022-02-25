#include "item.h"
#include "inventory.h"
#include "userlist.h"
#include "map.h"
#include "display.h"
#include "shader.h"
#include "mesh.h"
#include "texture.h"
#include "transform.h"

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

int main(){
    std::vector<std::string> names = {"frooti", "rice", "eggs"};
    std::vector<Category> cats = {Category::medium, Category::hard, Category::soft};
    
    std::vector<Item> items;
    for (int i = 0; i != names.size(); ++i){
        items.emplace_back(Item(names[i], cats[i]));
    }

    // for (Item i : items){
    //     cout << i.getName() << " ";
    //     cout << i.getSoftness() << endl; 
    // }
    // sortItems(items);
    // for (Item i : items){
    //     cout << i.getName() << " ";
    //     cout << i.getSoftness() << endl; 
    // }

    Inventory inventory("inventory.csv");
    inventory.printInventory();
    std::cout << std::endl << std::endl;

    UserList userList("userlist.txt", inventory);
    userList.printListItems();

    Map map("../src/map.csv");
    map.printMap();

 

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


	//mesh for the grid
	//currently for rectangles only, figure out when shop's a polygon
	float xMin, xMax, yMin, yMax;
	xMin = yMin = INT32_MAX;
	xMax = yMax = INT32_MIN;
	const std::vector<Vertex>& shopVertices = map.getPolygons()[0].getVertices();

	for (Vertex i : shopVertices){
		xMin = std::min(xMin, i.getX());
		xMax = std::max(xMax, i.getX());
		yMin = std::min(yMin, i.getY());
		yMax = std::max(yMax, i.getY());
	}
	std::cout << xMin << " " << xMax << " " << yMin << " " << yMax << std::endl;


	

	//
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
		mesh.Draw(GL_TRIANGLES);	
		display.Update();
		counter += inc;
	}
	return 0;
}
