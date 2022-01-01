#include <chrono>
#include <stdlib.h>
#include <iostream>
#include <exception>
#include <Eigen/Dense>
#include <opencv2/opencv.hpp>
#include "render/Render.hpp"
#include "render/camera/OrthographicCamera.hpp"
#include "neuron/NeuronScene.hpp"

constexpr auto title = "neuron-sdf-viewer";
constexpr auto width = 620;
constexpr auto height = 480;

constexpr auto model = "../assets/228-1-NBSS.CNG.swc";

void renderImage();

int main()
{
    try {
        auto start = std::chrono::system_clock::now();
        renderImage();
        auto stop = std::chrono::system_clock::now();

        std::cout << "Render complete: \n";
        std::cout << "Time taken: " << std::chrono::duration_cast<std::chrono::hours>(stop - start).count() << " hours\n";
        std::cout << "          : " << std::chrono::duration_cast<std::chrono::minutes>(stop - start).count() << " minutes\n";
        std::cout << "          : " << std::chrono::duration_cast<std::chrono::seconds>(stop - start).count() << " seconds\n";

        cv::waitKey(0);
        return EXIT_SUCCESS;
    }
    catch (std::exception& ex) {
        std::cerr << ex.what() << std::endl;
        return EXIT_FAILURE;
    }
}

void renderImage() {
    NeuronScene scene;
    scene.load(model);

    OrthographicCamera camera(-width / 2, width / 2, height / 2, -height / 2, 0.5, 2000);

    Render render(width, height);
    render.draw(scene, camera);

    auto& colorBuffer = render.get_frame_buffer();
    cv::Mat img(height, width, CV_8UC3, colorBuffer.data());
    cv::imshow(title, img);
}
