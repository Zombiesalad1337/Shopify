#include "item.h"
#include "inventory.h"
#include "userlist.h"
#include "map.h"
#include "display.h"
#include "shader.h"
#include "mesh.h"
#include "texture.h"
#include "transform.h"
#include "gfxutils.h"
#include <vector>
#include <string>
#include <iostream>
#include <memory>
#include <algorithm>

#define BOUNDARY 0.98
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

int main(){
    /*std::vector<std::string> names = {"frooti", "rice", "eggs"};
    std::vector<Category> cats = {Category::medium, Category::hard, Category::soft};
    
    std::vector<Item> items;
    for (int i = 0; i != names.size(); ++i){
        items.emplace_back(Item(names[i], cats[i]));
    }*/

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

 
	GLfloat aspectRatio = (GLfloat) WINDOW_HEIGHT / WINDOW_WIDTH;
	std::string windowName = "tst";
	gfx::Display display(WINDOW_WIDTH, WINDOW_HEIGHT, windowName);	

	//executable is in bin directory
	gfx::Shader shader("../src/res/shaders/basicShader");

	gfx::Vertex vertices[] = {gfx::Vertex(glm::vec3(-0.5, -0.5, 0), glm::vec2(-0.5, -0.5)),
						gfx::Vertex(glm::vec3(0, 0.5, 0), glm::vec2(0.0, 0.5)),
						gfx::Vertex(glm::vec3(0.5, -0.5, 0), glm::vec2(0.5, -0.5)) };

	gfx::Mesh mesh(vertices, sizeof(vertices)/sizeof(vertices[0]), GL_TRIANGLES);

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


	//creating mesh
	std::vector<gfx::Vertex> lineVertices;
	GLfloat glLineWidthRange[2] = {0.0f, 0.0f};

	//line width range - [1, 7.375]
	glGetFloatv(GL_ALIASED_LINE_WIDTH_RANGE, glLineWidthRange);
	std::cout << glLineWidthRange[0] << " " << glLineWidthRange[1] << std::endl;

	std::vector<gfx::Vertex> mainLines;
	std::vector<gfx::Vertex> intermediateLines;

	float shopWidth = abs(xMax - xMin);
	
	float meter = 2 * BOUNDARY / shopWidth;
	float unit = meter * map.getResolution();

	std::cout << meter << " " << unit << std::endl;

	float offset = 0;
	float accumulate = meter;
	//coordinate axes is drawn twice
	while (offset <= BOUNDARY){
		if (abs(accumulate - meter) < 0.000001){
			// std::cout << "Diff" << abs(accumulate - meter) << std::endl;
			//vertical line right of origin
			mainLines.emplace_back(gfx::Vertex(glm::vec3(offset, -BOUNDARY, 0)));
			mainLines.emplace_back(gfx::Vertex(glm::vec3(offset, BOUNDARY, 0)));
			//vertical line left of origin
			mainLines.emplace_back(gfx::Vertex(glm::vec3(-offset, -BOUNDARY, 0)));
			mainLines.emplace_back(gfx::Vertex(glm::vec3(-offset, BOUNDARY, 0)));
			//horizontal line above origin
			mainLines.emplace_back(gfx::Vertex(glm::vec3(-BOUNDARY, offset, 0)));
			mainLines.emplace_back(gfx::Vertex(glm::vec3(BOUNDARY, offset, 0)));
			//horizontal line below origin
			mainLines.emplace_back(gfx::Vertex(glm::vec3(-BOUNDARY, -offset, 0)));
			mainLines.emplace_back(gfx::Vertex(glm::vec3(BOUNDARY, -offset, 0)));

			accumulate = 0;
		}
		else{
			//vertical line right of origin
			intermediateLines.emplace_back(gfx::Vertex(glm::vec3(offset, -BOUNDARY, 0)));
			intermediateLines.emplace_back(gfx::Vertex(glm::vec3(offset, BOUNDARY, 0)));
			//vertical line left of origin
			intermediateLines.emplace_back(gfx::Vertex(glm::vec3(-offset, -BOUNDARY, 0)));
			intermediateLines.emplace_back(gfx::Vertex(glm::vec3(-offset, BOUNDARY, 0)));
			//horizontal line above origin
			intermediateLines.emplace_back(gfx::Vertex(glm::vec3(-BOUNDARY, offset, 0)));
			intermediateLines.emplace_back(gfx::Vertex(glm::vec3(BOUNDARY, offset, 0)));
			//horizontal line below origin
			intermediateLines.emplace_back(gfx::Vertex(glm::vec3(-BOUNDARY, -offset, 0)));
			intermediateLines.emplace_back(gfx::Vertex(glm::vec3(BOUNDARY, -offset, 0)));
		}
		offset += unit;
		accumulate += unit;
	}

	//calls the default constructor of gfx::Vertex,
	//whose contents are later copied from the vectors above
	gfx::Vertex *mainLineVertices = new gfx::Vertex[mainLines.size()];
	gfx::Vertex *intermediateLineVertices = new gfx::Vertex[intermediateLines.size()];

	//calls the copy constructor for copying
	//not very efficient	
	for (int i = 0; i < mainLines.size(); ++i){
		mainLineVertices[i] = mainLines[i];
	}
	for (int i = 0; i < intermediateLines.size(); ++i){
		intermediateLineVertices[i] = intermediateLines[i];
	}
	
	std::cout << mainLines.size() << std::endl;
	std::cout << intermediateLines.size() << std::endl;

	// for (int i = 0; i < mainLines.size(); ++i){
	// 	std::cout << mainLines[i].getPos().x << " " << mainLines[i].getPos().y << std::endl;
	// }
	// std::cout << std::endl << std::endl;
	// for (int i = 0; i < intermediateLines.size(); ++i){
	// 	std::cout << intermediateLines[i].getPos().x << " " << intermediateLines[i].getPos().y << std::endl;
	// }

	gfx::Mesh mainLineMesh(mainLineVertices, mainLines.size(), GL_LINES);
	gfx::Mesh intermediateLineMesh(intermediateLineVertices, intermediateLines.size(), GL_LINES);


	gfx::Shader mainLineShader("../src/res/shaders/lineShaderThick");
	gfx::Shader intermediateLineShader("../src/res/shaders/lineShader");
    gfx::Shader circleShader("../src/res/shaders/circleShader");


	//polygon meshes
	//need to triangulate polygons
	std::cout << "polygon meshes" << std::endl << std::endl;	
	std::vector<std::unique_ptr<gfx::Mesh>> polygonMeshes;

	for (int i = 1; i < map.getPolygons().size(); ++i){
		// std::cout << "x" << std::endl;
		std::vector<Vertex> triangleVertices = map.getPolygons()[i].Triangulate();
	
		// std::cout << "m" << std::endl;
		gfx::Vertex* triangleVerticesArray = new gfx::Vertex[triangleVertices.size()];

		// std::cout << "z" << std::endl;
		for (int j = 0; j < triangleVertices.size(); ++j){
			// std::cout << "y" << std::endl;	
			float x = triangleVertices[j].getX() * meter;
			float y = triangleVertices[j].getY() * meter;

			triangleVerticesArray[j] = gfx::Vertex(glm::vec3(x, y, 0), glm::vec2(x, y));
		}
		// std::cout << triangleVertices.size() << std::endl;

		// for (int j = 0; j < triangleVertices.size(); ++j){
		// 	std::cout << triangleVertices[j].getX() << " " << triangleVertices[j].getY() << std::endl;
		// }

		// for (int j = 0; j < triangleVertices.size(); ++j){
		// 	std::cout << triangleVerticesArray[j].getPos().x << " " << triangleVerticesArray[j].getPos().y << std::endl;
		// }

		//JUST TOOK 2 HOURS OF DEBUGGING
		//FUCK U TEMPORARY OBJECT
		//https://stackoverflow.com/questions/46694577/drawing-vbos-in-opengl-not-working
		//NOW JUST HAVE TO FIX SHITTY TEXTURES
		polygonMeshes.emplace_back(new gfx::Mesh(triangleVerticesArray, triangleVertices.size(), GL_TRIANGLES));
		delete[] triangleVerticesArray;
	}

    std::vector<std::unique_ptr<gfx::Mesh>> circleMeshes;
    createCircleMesh(0, 0, 0, 0.1, 50, circleMeshes);

    //circles for TESTING
    
    createCircleMesh(-0.5, -0.5, 0, 0.1, 50, circleMeshes);
    createCircleMesh(-0.5, 0.5, 0, 0.1, 50, circleMeshes);
    createCircleMesh(0.5, -0.5, 0, 0.1, 50, circleMeshes);
    createCircleMesh(0.5, 0.5, 0, 0.1, 50, circleMeshes);

    std::vector<glm::vec4> circleColors;
    circleColors.emplace_back(glm::vec4{1.0,1.0,1.0,1.0f});
    circleColors.emplace_back(glm::vec4{0.0,1.0,1.0,1.0f});
    circleColors.emplace_back(glm::vec4{1.0,0.0,1.0,1.0f});
    circleColors.emplace_back(glm::vec4{1.0,1.0,0.0,1.0f});
    circleColors.emplace_back(glm::vec4{1.0,0.0,1.0,1.0f});

	while (!display.IsClosed()){
		display.Clear(0.0f, 0.0f, 0.0f, 1.0f);
		// float cosCounter = cosf(counter);
		// transform.GetPos().x = sinf(counter);
		// transform.GetPos().y = cosf(counter);
		// transform.GetRot().z += (inc * 500) * 1/180;
		// transform.GetRot().x += (inc * 500) * 1/180;
		// transform.GetRot().y += (inc * 500) * 1/180;
		// transform.SetScale(glm::vec3(cosCounter, cosCounter, cosCounter));
		
		transform.SetScale(glm::vec3(aspectRatio, 1.0f, 1.0f));
		// mesh.Draw();	
		mainLineShader.Bind();
		mainLineShader.Update(transform);
		glLineWidth(2);
		//mainLineMesh.Draw();

		mainLineShader.Bind();
		mainLineShader.Update(transform);

        circleShader.Bind();
        circleShader.Update(transform);
        //need to set uniform after binding the shader (so it knows what shader to set to)
        for (int i = 0; i < circleMeshes.size(); ++i){
            //circleShader.setColor(circleColors[i]);
            circleShader.setColor(circleColors[i]);
            circleMeshes[i]->Draw();
        }
		
		// intermediateLineShader.Bind();
		// intermediateLineShader.Update(transform);
		// glLineWidth(1);
		// intermediateLineMesh.Draw();

		//polygon meshes
		//currenly using basic shader for polygon
		//and the wood texture
		shader.Bind();
		texture.Bind(0);
		shader.Update(transform);

		//for (int i = 0; i < polygonMeshes.size(); ++i){
			//polygonMeshes[i]->Draw();
		//}
		// polygonMeshes[1]->Draw();
		// mesh.Draw();
		display.Update();
		// counter += inc;
	}

	delete[] mainLineVertices;
	delete[] intermediateLineVertices;
	return 0;

}
