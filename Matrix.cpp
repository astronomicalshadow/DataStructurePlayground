#include <iostream>
#include <vector>
#include <array>

template<typename T = double> 
class Matrix
{   

    std::vector<std::vector<T>> m_Matrix; // make it vector of std::array

public:

    Matrix() = delete;

    constexpr Matrix(const std::vector<std::vector<T>>& matrix)
    {
        for (int i = 0; i != matrix.size() - 1; i++)
        {
            if (matrix[i].size() != matrix[i+1].size())
            {
                throw;
            }
        }

        m_Matrix = matrix;
    };

    // operator overload
    // Matrix* operator+(Matrix& matrixB){};

    // Matrix* operator-(Matrix& matrixB){};

    // Matrix* operator*(Matrix& matrixB){};

    // // calculations
    // Matrix* dot(Matrix& matrixB){};

    // Matrix* cross(Matrix& matrixB){};
    
    inline void print()
    {
        for ( const auto &row : m_Matrix )
        {
            for ( const auto &s : row ) std::cout << s << ' ';
            std::cout << "\n";
        };
    } 
};

int main()
{

    Matrix a({{1,2},{2,3},{3,4,3}});
 
    return 0;
}

