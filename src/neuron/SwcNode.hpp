#pragma once
#include <string>
#include <memory>

class SwcNode
{
public:
    static bool try_parse(const std::string &s, std::unique_ptr<SwcNode> &out);

    int id;
    int type;
    float x;
    float y;
    float z;
    float raidus;
    int parent;

    std::unique_ptr<SwcNode> child;
    std::unique_ptr<SwcNode> next;
};
