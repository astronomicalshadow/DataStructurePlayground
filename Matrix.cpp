#include <iostream>
#include <vector>
#include <array>

template<typename Type = double>
class Matrix
{   

    std::vector<std::vector<Type>> m_Matrix; // make it vector of std::array

public:

    Matrix(const std::vector<std::vector<Type>>& Matrix)
    {
        for (int i = 0; i < Matrix.size() - 1; i++)
        {
            if (Matrix[i].size() != Matrix[i+1].size())
            {
                std::cout << "error";
            }
        }

        m_Matrix = Matrix;
    };

    auto GetMatrix() const
    {
        return m_Matrix;
    }

    // operator overload
    std::vector<std::vector<Type>> operator + (Matrix& RHS) const
    {
        auto RHS_Matrix = RHS.GetMatrix();

        if(RHS_Matrix.size() != m_Matrix.size() || RHS_Matrix[0].size() != m_Matrix[0].size())
        {
            throw;
        }

        std::vector<std::vector<Type>> Array(m_Matrix.size());

        for(int Row = 0; Row < m_Matrix.size(); Row++)
        {
            std::vector<Type> CArray(m_Matrix[0].size());

            for(int Column = 0; Column < m_Matrix[0].size(); Column++)
            {
                CArray[Column] = m_Matrix[Row][Column] + RHS_Matrix[Row][Column];
            }

            Array[Row] = {CArray};
        }

        return std::move(Array);
    };

    auto operator - (Matrix& RHS) const
    {
        auto RHS_Matrix = RHS.GetMatrix();

        if(RHS_Matrix.size() != m_Matrix.size() || RHS_Matrix[0].size() != m_Matrix[0].size())
        {
            throw;
        }

        std::vector<std::vector<Type>> Array(m_Matrix.size());

        for(int Row = 0; Row < m_Matrix.size(); Row++)
        {
            std::vector<Type> CArray(m_Matrix[0].size());

            for(int Column = 0; Column < m_Matrix[0].size(); Column++)
            {
                CArray[Column] = m_Matrix[Row][Column] - RHS_Matrix[Row][Column];
            }

            Array[Row] = {CArray};
        }

        return std::move(Array);
    };

    // auto operator * (const Matrix& Other){};

    // auto Dot(const Matrix& Other){};

    // auto Cross(const Matrix& Other){};

    // auto Det(const Matrix& Other){};
    
    void print() const
    {
        for(const auto &row : m_Matrix)
        {
            for(const auto &s : row)
            {
                std::cout << s << ' ';
            }
            std::cout << "\n";
        };
    } 
};

int main()
{

    Matrix<int> a({
                {1, 2},
                {2, 3}
                });

    Matrix<int> b({
                {1, 1},
                {2, 3}
                });

    Matrix<int> c = b - a;

    Matrix<int> d = a - b;

    d.print();
    return 0;
}

