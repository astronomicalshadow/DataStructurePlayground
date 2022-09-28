#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int input, number = 3;
    cin >> input;
    vector<int> PrimeArry;
    PrimeArry.push_back(2);
    while (PrimeArry.back() <= input)
    {
        bool isprime = true;
        for (const auto& j : PrimeArry)
        {
            if (number % j == 0)
            {
                isprime = false;
                break;
            }
        }
        if (isprime)
        {
            PrimeArry.push_back(number);
        }
        number++;
    }
    cout << PrimeArry.back();
}
