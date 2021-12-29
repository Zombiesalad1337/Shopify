#include "item.h"
#include "inventory.h"
#include <bits/stdc++.h>
#include <boost/tokenizer.hpp>
using namespace std;

vector<string> split(std::string s, const char* sep1, const char* sep2)
{
    vector<string> tokens;
    boost::char_separator<char> sep(sep1, sep2);
    boost::tokenizer<boost::char_separator<char> > tok(s, sep);
    for(auto i = tok.begin(); i!=tok.end(); ++i)
        tokens.emplace_back(*i);
    return tokens;
}


Inventory::Inventory(string filename){
    map<string, Category> catMap;
    catMap["hard"] = Category::hard;
    catMap["medium"] = Category::medium;
    catMap["soft"] = Category::soft;

    ifstream fin;
    fin.open(filename);
    string line;
    getline(fin, line);

    int count = 0;
    while (fin){
        getline(fin, line);
        //first line contains headers, read from 2nd line
        if (line.size()){
            vector<string> tokens = split(line, ",", "");
            items.emplace_back(Item(tokens[0], catMap[tokens[1]]));
            mapItems[tokens[0]] = count;
            count++;
        }
    }
}