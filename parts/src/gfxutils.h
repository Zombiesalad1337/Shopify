#pragma once
#include "mesh.h"
#include <memory>
#include <vector>

namespace gfx{

void drawCircle(GLfloat x, GLfloat y, GLfloat z, GLfloat radius, GLint numSides, std::vector<std::unique_ptr<Mesh>>& circleMesh);


} //namespace gfx
