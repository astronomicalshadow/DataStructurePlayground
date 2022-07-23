#include <iostream>
#include <vector>
#include <cmath>

template<typename T = double>
class MergeSort
{
    // i could use smart pointers
    std::vector<std::vector<T>*> ArrayPointers;
public:
    ~MergeSort()
    {
        // delete pointers;
        for (const auto& iter : ArrayPointers)
        {
            delete iter;
        }
    }

    void Split(const std::vector<T>& array)
    {
        if (array.size() > 1)
        {
            std::vector<T>* TempArrayLeft = new std::vector<T>(array.begin(), array.begin() + ceil(array.size() * 0.5));   
            std::vector<T>* TempArrayRight = new std::vector<T>(array.begin() + ceil(array.size() * 0.5), array.end());

            TempArrayLeft->size() > 1 ? Split(TempArrayLeft) : ArrayPointers.push_back(TempArrayLeft);

            TempArrayRight->size() > 1 ? Split(TempArrayRight) : ArrayPointers.push_back(TempArrayRight);
        }
        else
        {
            // i could throw exception, but don't know how to structure the Sort function
            std::cout << "Array must be > 1";
            std::exit(0);
        }
    }

    void Split(std::vector<T>* array)
    {
        std::vector<T>* TempArrayLeft = new std::vector<T>(array->begin(), array->begin() + ceil(array->size() * 0.5));   
        std::vector<T>* TempArrayRight = new std::vector<T>(array->begin() + ceil(array->size() * 0.5), array->end());

        delete array;

        TempArrayLeft->size() > 1 ? Split(TempArrayLeft) : ArrayPointers.push_back(TempArrayLeft);

        TempArrayRight->size() > 1 ? Split(TempArrayRight) : ArrayPointers.push_back(TempArrayRight);
    }

    void Merge()
    {
        while (ArrayPointers.size() > 1)
        {
            for (int i = 0; i < ArrayPointers.size() && ArrayPointers[i] != ArrayPointers.back(); i++)
            {
                auto* TempVector = new std::vector<T>();
                int LeftCounter = 0;
                int RightCounter = 0;

                while(LeftCounter < ArrayPointers[i]->size())
                {
                    if (RightCounter == ArrayPointers.back()->size())
                    {
                        TempVector->push_back(ArrayPointers[i]->at(LeftCounter));
                        LeftCounter++;
                        continue;
                    }

                   while(ightCounter < ArrayPointers.back()->size())
                    {
                        // optional statement
                        if (ArrayPointers[i]->at(LeftCounter) == ArrayPointers.back()->at(RightCounter))
                        {
                            // if equal push both and skip 1 iteration, hopefully this is faster
                            TempVector->push_back(ArrayPointers[i]->at(LeftCounter));
                            TempVector->push_back(ArrayPointers.back()->at(RightCounter));
                            LeftCounter++;
                            RightCounter++;
                            break;
                        }
                        // end of optional
 
                        if (ArrayPointers[i]->at(LeftCounter) < ArrayPointers.back()->at(RightCounter))
                        {
                            TempVector->push_back(ArrayPointers[i]->at(LeftCounter));   
                            LeftCounter++;
                            break;
                        }
                        else
                        {
                            TempVector->push_back(ArrayPointers.back()->at(RightCounter));
                            RightCounter++;
                        }
                    }
                }

                while (RightCounter != ArrayPointers.back()->size())
                {
                    TempVector->push_back(ArrayPointers.back()->at(RightCounter));
                    RightCounter++;
                }

                delete ArrayPointers[i];
                ArrayPointers[i] = TempVector;

                delete ArrayPointers.back();
                ArrayPointers.pop_back();
            }
        }
    }

    auto Sort(const std::vector<T>& array)
    {
        Split(array);
        Merge();
        return ArrayPointers[0];
    }
};

int main()
{
    MergeSort m;
    for (const auto& iter : *m.Sort({9,10,1}))
    {
        std::cout << iter <<' ';
    }
    return 0;
}