#pragma once
#include "item.h"
#include "vertex.h"
#include <vector>
#include <string>


std::vector<std::string> split(std::string s, const char* sep1, const char* sep2);

bool ItemComparator(const Item* item1, const Item* item2);

float crossProduct(const Vertex& v1, const Vertex& v2);

bool isPointInTriangle(const Vertex& p, const Vertex& a, const Vertex& b, const Vertex& c);


int mod(int k, int n); 