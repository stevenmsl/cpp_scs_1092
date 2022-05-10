#include <string>
#include <sstream>
#include <algorithm>
#include "node.h"
#include "util.h"

using namespace std;
using namespace sol1092;

string Util::toString(vector<string> input)
{
    string result = "[";
    for (auto e : input)
    {
        result += e;
        result += ",";
    }
    /* remove the last comma */
    if (result.back() == ',')
        result.pop_back();
    result += "]";
    return result;
}

string Util::toString(vector<int> input)
{
    string result = "[";
    for (auto e : input)
    {
        result += to_string(e);
        result += ",";
    }
    /* remove the last comma */
    if (result.back() == ',')
        result.pop_back();
    result += "]";
    return result;
}

string Util::toString(vector<vector<int>> input)
{
    string result = "[";
    for (auto i : input)
        result += toString(i), result += ",";
    if (result.back() == ',')
        result.pop_back();
    result += "]";
    return result;
}

string Util::toString(vector<vector<string>> input)
{
    string result = "[";
    for (auto i : input)
        result += toString(i), result += ",";
    if (result.back() == ',')
        result.pop_back();
    result += "]";
    return result;
}

/* delimiter is the sapce */
vector<string> Util::split(string input)
{
    auto ss = stringstream(input);
    auto result = vector<string>();
    string token;
    while (ss >> token)
    {
        result.push_back(token);
    }
    return result;
}
vector<string> Util::split(string input, char delimiter)
{
    auto ss = stringstream(input);
    auto result = vector<string>();
    string token;
    while (getline(ss, token, delimiter))
    {
        result.push_back(token);
    }
    return result;
}

string Util::toLower(const string &s)
{
    auto result = string(s);
    transform(begin(s), end(s), begin(result), ::tolower);
    return result;
}

string Util::toString(vector<bool> input)
{
    auto result = vector<string>();
    for (auto i : input)
        result.push_back(i ? "true" : "false");
    return toString(result);
}

string Util::toString(vector<vector<bool>> input)
{
    auto result = vector<vector<string>>();
    for (auto i = 0; i < input.size(); i++)
    {
        result.push_back(vector<string>());
        for (auto j = 0; j < input[i].size(); j++)
            result[i].push_back(input[i][j] ? "true" : "false");
    }
    return toString(result);
}