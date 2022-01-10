#include <chrono>
#include <functional>
#include <exception>
#include <type_traits>
#include <string>

void print_duration_info(const std::string &title, std::chrono::steady_clock::time_point start, std::chrono::steady_clock::time_point stop);

template <typename Func, typename... Args>
auto run_with_duration(const std::string &title, const Func &func, Args... args)
{
    if constexpr (std::is_same<std::result_of_t<Func(Args...)>, void>::value)
    {
        auto start = std::chrono::steady_clock::now();
        func(args...);
        auto stop = std::chrono::steady_clock::now();

        print_duration_info(title, start, stop);
    }
    else
    {
        auto start = std::chrono::steady_clock::now();
        std::result_of_t<Func(Args...)> result = func(args...);
        auto stop = std::chrono::steady_clock::now();

        print_duration_info(title, start, stop);

        return result;
    }
}
