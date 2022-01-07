module;
#include <chrono>
#include <string>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <exception>
#include <functional>
export module Utils.Debug;

export void runWithClockInfo(const std::string& title, std::function<void()> task)
{
    auto start = std::chrono::steady_clock::now();
    task();
    auto stop = std::chrono::steady_clock::now();
    auto nanoseconds = stop - start;

    auto hours = std::chrono::duration_cast<std::chrono::hours>(nanoseconds);
    nanoseconds -= hours;

    auto minutes = std::chrono::duration_cast<std::chrono::minutes>(nanoseconds);
    nanoseconds -= minutes;

    auto seconds = std::chrono::duration_cast<std::chrono::seconds>(nanoseconds);
    nanoseconds -= seconds;

    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(nanoseconds);

    std::cout << title << " complete: " << std::endl
        << "Time taken: " << std::setw(4) << hours.count() << " hours, " << std::endl
        << "            " << std::setw(4) << minutes.count() << " minutes, " << std::endl
        << "            " << std::setw(4) << seconds.count() << " seconds, " << std::endl
        << "            " << std::setw(4) << milliseconds.count() << " milliseconds." << std::endl
        << std::endl;
}
