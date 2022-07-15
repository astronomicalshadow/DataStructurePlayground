#include <iostream>
#include <vector>

template<class T>
class BinaryTree
{
    enum TreeType
    {
        BST,
        BBT
    };

    struct m_Node
    {
        T data;
        struct m_Node* LeftNode,* RightNode = nullptr;
        int NodeDegree = 0;
    };

    struct m_Node* m_Head = nullptr;
    int m_TreeSize;

public:

    void CreateTree(std::vector<T> items)
    {
        if (m_TreeSize > 0)
        {
            void Insert(items);
            return;
        }
        
        m_Head = new m_Node;
        m_Head->data = items[0];
        if (items.size() > 1)
        {
            Insert(items);
        }

    }

    void Insert(std::vector<T> items, TreeType TreeType)
    {}
};

int main()
{
    BinaryTree<int> tree;

    std::cout << "Hello World";

}