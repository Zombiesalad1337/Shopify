#pragma once
#include "item.h"
#include <vector>
#include <string>


std::vector<std::string> split(std::string s, const char* sep1, const char* sep2);

bool ItemComparator(const Item* item1, const Item* item2);