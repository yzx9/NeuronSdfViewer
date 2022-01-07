module;
#include <functional>
export module Utils;

export
template <typename T, typename K, typename L = std::vector<T>>
void quick_partion_k(
    L &list,
    std::function<K(const T&)> const& val,
    int const&left,
    int const&right,
    int const&k
) {
    if (left >= right)
        return;

    auto i = left;
    auto j = right;

    while (i < j) {
        auto t = std::move(list[i]);
        auto k = val(t);

        while (i < j && val(list[j]) > k)
            j--;

        if (i < j && val(list[j]) <= k)
            list[i++] = std::move(list[j]);

        while (i < j && val(list[i]) < k)
            i++;

        if (i < j && val(list[i]) >= k)
            list[j--] = std::move(list[i]);

        list[i] = std::move(t);
    }

    if (i < k)
    {
        quick_partion_k(list, val, i + 1, right, k - i);
    }
    else if (i > k)
    {
        quick_partion_k(list, val, left, i - 1, k);
    }
}
