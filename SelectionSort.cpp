#include <iostream>
#include <vector>

template <typename T>
std::vector<T> SelectionSort(std::vector<T>& Array)
{
    T SmallestValue{};
    uint32_t SmallestIndex{};

    for (uint32_t i = 0; i < Array.size(); i++)
    {
        SmallestValue = Array[i];
        SmallestIndex = i;
        for (uint32_t j = i; j < Array.size(); j++)
        {
            if(Array[j] < SmallestValue)
            {
                SmallestIndex = j;
                SmallestValue = Array[j];
            }
        }
        Array[SmallestIndex] = Array[i];
        Array[i] = SmallestValue;
    }

    return Array;
}

int main()
{
    std::vector<int> Vec{2, 5, 8, 3, 20, -3, -96, 3};
    auto Sorted = SelectionSort<int>(Vec);

    for (const auto& iter : Sorted)
    {
        std::cout << iter << " ";
    }
}