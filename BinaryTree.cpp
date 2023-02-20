#include <iostream>
#include <vector>

template<class T>
class BinarySearchTree
{
public:
    BinarySearchTree(const std::vector<T> &Data)
    {
        m_Head.data = Data[0];
        // begin()++ doesn't work
        std::vector<T> Vector(Data.begin() + 1, Data.end());
        Insert(Vector);
    }

    void Insert(const std::vector<T> &Data)
    {
        m_Cursor = &m_Head;
        // go through the list
        for (auto &Iter : Data)
        {
            if (Iter <= m_Cursor->data)
            {
                m_Cursor->LeftNode = new m_Node();
                m_Cursor = m_Cursor->LeftNode;
                m_Cursor->data = Iter;
                m_Height++;
                m_Width++;
            }
            else
            {
                m_Cursor->RightNode = new m_Node();
                m_Cursor = m_Cursor->RightNode;
                m_Cursor->data = Iter;
                m_Height++;
                m_Width++;
            }

        }
    }

    void Print()
    {
        // only prints left node and the last element doesn't get printed
        m_Cursor = &m_Head;
        while(m_Cursor->LeftNode != nullptr)
        {
            std::cout << m_Cursor->data;
            m_Cursor = m_Cursor->LeftNode;
        }
    }

private:
    struct m_Node
    {
        T data;
        struct m_Node *LeftNode, *RightNode = nullptr;
        int NodeDegree = 0;
    };

    m_Node m_Head{};
    m_Node *m_Cursor = nullptr;
    int m_Height, m_Width = 0;
};

int main()
{
    BinarySearchTree<int> Tree({6, 4, 2, 1, 0});
    Tree.Print();



}