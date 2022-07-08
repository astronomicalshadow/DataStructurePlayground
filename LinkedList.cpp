#include <iostream>
#include <vector>

template<class T> 
class One_Way_LinkedList
{
    struct m_Node
    {
        T data;
        struct m_Node* NextNode = nullptr;
    };

    m_Node* m_Head = nullptr;

    m_Node* m_Cursor = nullptr;

public:

    void CreateList(std::vector<T> items) // create a node to initialize m_Head and m_Cursor
    {
        if (m_Head != nullptr) // can only create list once
        {
            AppendItems(items); // append items
            return;
        }

        m_Cursor = m_Head = new m_Node;

        m_Head->data = items[0];

        if (items.size() > 1)
        {
            AppendItems(items.begin() + 1, items.end()); // if items > 1, then start appending
        }
    }

    void AppendItems(std::vector<T> items) // append items to list
    {
        while(m_Cursor->NextNode)
        {
            m_Cursor = m_Cursor->NextNode;
        }

        m_Cursor->NextNode = new m_Node;

        m_Cursor = m_Cursor->NextNode;

        m_Cursor->data = items[0];
        
        if (items.size() > 1) // 1 item is problem
        {
            AppendItems(items.begin() + 1, items.end());
        }
    }

    void AppendItems(typename std::vector<T>::iterator items, typename std::vector<T>::iterator end) // append items to list
    {
        while(m_Cursor->NextNode)
        {
            m_Cursor = m_Cursor->NextNode;
        }

        m_Cursor->NextNode = new m_Node;

        m_Cursor = m_Cursor->NextNode;

        m_Cursor->data = items[0];
        
        if (items + 1 != end)
        {
            AppendItems(items + 1, end);
        }
    }

    void PrintList()
    {
        m_Cursor = m_Head;

        while (m_Cursor)
        {
            std::cout << m_Cursor->data << " ";

            m_Cursor = m_Cursor->NextNode;
        }

    }

    void DeleteList()
    {
        m_Cursor = m_Head;

        while (m_Cursor->NextNode)
        {
            m_Cursor = m_Head->NextNode;

            delete m_Head;

            m_Head = m_Cursor;
        }

        delete m_Cursor;

    }

};

// template<class T> 
// class Two_Way_LinkedList
// {};

// template<class T> // maybe, maybe not, redundant work?
// class LinkedList_3D
// {};

int main()
{
    One_Way_LinkedList<int> List1Way;

    List1Way.CreateList({1, 2});

    List1Way.AppendItems({3, 4, 5, 6});

    List1Way.CreateList({8}); // will append instead of create new

    List1Way.PrintList();

    List1Way.DeleteList();

    return 0;
}