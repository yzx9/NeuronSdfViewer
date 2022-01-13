#pragma once
#include <string>
#include <regex>
#include <memory>

class SwcNode
{
public:
    int id;
    int type;
    float x;
    float y;
    float z;
    float raidus;
    int parent;

    std::unique_ptr<SwcNode> child;
    std::unique_ptr<SwcNode> next;

    static bool try_parse(const std::string &s, std::unique_ptr<SwcNode> &out)
    {
        constexpr auto pattern =
            "\\s*"
            "(\\d+)\\s"               // index
            "(\\d+)\\s"               // type
            "(-?\\d*(?:\\.\\d+)?)\\s" // x
            "(-?\\d*(?:\\.\\d+)?)\\s" // y
            "(-?\\d*(?:\\.\\d+)?)\\s" // z
            "(-?\\d*(?:\\.\\d+)?)\\s" // radius
            "(-1|\\d+)\\s*";          // parent

        const static std::regex regex(pattern);

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

    void add_brother(std::unique_ptr<SwcNode> brother)
    {
        if (next)
            next->add_brother(std::move(brother));
        else
            next = std::move(brother);
    };

    void add_child(std::unique_ptr<SwcNode> new_child)
    {
        if (child)
            child->add_brother(std::move(new_child));
        else
            child = std::move(new_child);
    }
};
