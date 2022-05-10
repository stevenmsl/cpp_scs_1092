#ifndef NODE_H
#define NODE_H

#include <vector>
#include <cinttypes>
using namespace std;

namespace sol1092
{
    struct Node
    {
        vector<Node *> next;
        bool isWord;
        Node() : isWord(false), next(vector<Node *>(26, nullptr)){};
    };
}
#endif