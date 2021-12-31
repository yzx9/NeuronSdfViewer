#include <exception>
#include <fstream>
#include <string>
#include <Eigen/Dense>
#include "SwcLoader.hpp"
#include "SwcPoint.hpp"
#include "../render/object/SdfSphere.hpp"

using objects = std::vector<std::unique_ptr<SdfObject>>;

objects SwcLoader::load(const std::string& filepath)
{
    std::ifstream file(filepath);
    if (!file.is_open())
    {
        throw std::runtime_error("Open SWC file failed!");
    }

    objects objs;
    SwcPoint point;
    std::string s;
    while (std::getline(file, s))
    {
        if (!s.starts_with('#') && SwcPoint::try_parse(s, point)) {
            auto sphere = std::make_unique<SdfSphere>(Eigen::Vector3f(point.x, point.y, point.z), point.raidus);
            objs.emplace_back(std::move(sphere));
        }
    }

    file.close();
    return objs;
}
