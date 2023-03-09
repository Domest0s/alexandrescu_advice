#include <vector>
#include <random>

std::vector<int32_t> generateRandomArray(size_t size)
{
    std::vector<int32_t> arr(size);

    std::random_device rd;
    std::default_random_engine engine(rd());
    std::uniform_int_distribution<int32_t> uniform_dist(0, 1000);

    for (size_t i = 0; i < size; i++)
    {
        arr[i] = uniform_dist(engine);
    }

    return arr;
}