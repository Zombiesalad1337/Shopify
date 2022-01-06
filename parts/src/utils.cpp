#include "utils.h"
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

bool ItemComparator(const Item* item1, const Item* item2){
    return item1->getSoftness() < item2->getSoftness();
}