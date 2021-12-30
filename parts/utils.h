#pragma once
#include <bits/stdc++.h>
#include "item.h"

using namespace std;

vector<string> split(std::string s, const char* sep1, const char* sep2);

bool ItemComparator(const Item* item1, const Item* item2);