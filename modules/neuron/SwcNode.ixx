module;
#include <string>
#include <memory>
#include <regex>
export module Neuron:SwcNode;

constexpr auto pattern =
    "\\s*"
    "(\\d+)\\s"                 // index
    "(\\d+)\\s"                 // type
    "(-?\\d*(?:\\.\\d+)?)\\s"   // x
    "(-?\\d*(?:\\.\\d+)?)\\s"   // y
    "(-?\\d*(?:\\.\\d+)?)\\s"   // z
    "(-?\\d*(?:\\.\\d+)?)\\s"   // radius
    "(-1|\\d+)"                 // parent
    "\\s*";

std::regex regex(pattern);

export class SwcNode
{
public:
    static bool try_parse(const std::string& s, std::unique_ptr<SwcNode>& out)
    {
        std::smatch match;
        if (!std::regex_match(s, match, regex))
            return false;

        out = std::make_unique<SwcNode>();
        out->id = std::stoi(match[1]);
        out->type = std::stoi(match[2]);
        out->x = std::stof(match[3]);
        out->y = std::stof(match[4]);
        out->z = std::stof(match[5]);
        out->raidus = std::stof(match[6]);
        out->parent = std::stoi(match[7]);
        out->child = nullptr;
        out->next = nullptr;
        return true;
    };

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
