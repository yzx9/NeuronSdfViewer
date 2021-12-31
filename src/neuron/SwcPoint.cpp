#include <regex>
#include "SwcPoint.hpp"

constexpr auto pattern =
"\\s*"
"(\\d+)\\s"                 // index
"(\\d+)\\s"                 // type
"(-?\\d*(?:\\.\\d+)?)\\s"   // x
"(-?\\d*(?:\\.\\d+)?)\\s"   // y
"(-?\\d*(?:\\.\\d+)?)\\s"   // z
"(-?\\d*(?:\\.\\d+)?)\\s"   // radius
"(-1|\\d+)\\s*";            // parent

std::regex regex(pattern);

bool SwcPoint::try_parse(const std::string& s, SwcPoint& out) {
    std::smatch match;
    if (!std::regex_match(s, match, regex)) {
        return false;
    }

    out.id = std::stoi(match[1]);
    out.type = std::stoi(match[2]);
    out.x = std::stof(match[3]);
    out.y = std::stof(match[4]);
    out.z = std::stof(match[5]);
    out.raidus = std::stof(match[6]);
    out.parent = std::stoi(match[7]);
    return true;
}
