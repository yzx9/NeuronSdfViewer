#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

constexpr auto WIDTH = 640;
constexpr auto HEIGHT = 480;

class Viewer {
public:
    void run();

private:
    GLFWwindow* window;

    VkInstance instance;

    void initWindow();

    void initVulkan();

    void mainLoop();

    void cleanup();

    void createInstance();
};
