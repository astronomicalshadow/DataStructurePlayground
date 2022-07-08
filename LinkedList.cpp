#include <iostream>
#include <vector>

template<class T> 
class OneWayLinkedList
{
    struct m_Node
    {
        T data;
        struct m_Node* NextNode = nullptr;
    };

    m_Node* m_Head = nullptr;

    m_Node* m_Cursor = nullptr;

    int m_ListSize = 0;

public:

    void CreateList(std::vector<T> items) // create a node to initialize m_Head and m_Cursor
    {
        
        if (items.empty()) return;

        if (m_Head != nullptr) // can only create list once
        {
            AppendItems(items); // append items
            return;
        }

        m_Cursor = m_Head = new m_Node;

        m_Head->data = items[0];

        m_ListSize++;

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

        m_ListSize++;

        m_Cursor = m_Cursor->NextNode;

        m_Cursor->data = items[0];

        
        if (items.size() > 1) // 1 item is problem
        {
            AppendItems(items.begin() + 1, items.end());
        }
    }

    void AppendItems(typename std::vector<T>::iterator items, typename std::vector<T>::iterator end) // append items to list, overload function
    {
        while(m_Cursor->NextNode)
        {
            m_Cursor = m_Cursor->NextNode;
        }

        m_Cursor->NextNode = new m_Node;
        
        m_ListSize++;

        m_Cursor = m_Cursor->NextNode;

        m_Cursor->data = items[0];
        
        if (items + 1 != end)
        {
            AppendItems(items + 1, end);
        }
    }

    void InsertItems(int Position, std::vector<T> items)
    {

        if (items.empty()) return;

        int element = 0;

        m_Cursor = m_Head;

        while (element != Position)
        {
            m_Cursor = m_Cursor->NextNode;
            element++;
        }

        struct m_Node* Temp = m_Cursor->NextNode;

        m_Cursor->NextNode = nullptr;

        AppendItems(items);

        m_Cursor->NextNode = Temp; // cursor position changed to last element of new item because
                                    // used in the AppendItems call

        Temp = nullptr;
    }

    void RemoveItems (int Position, int AmountDelete = 1)
    { 
        if (AmountDelete == 0) return;
        if (Position < 0 || Position > m_ListSize) return;

        int element = 0;
        int deleted = 0;

        m_Cursor = m_Head;

        while (element < Position)
        {
            m_Cursor = m_Cursor->NextNode;
            element++;
        }

        struct m_Node* TempFront, *TempBack = nullptr; 
        
        TempFront = m_Cursor;

        TempBack, m_Cursor = m_Cursor->NextNode;

        while (deleted != AmountDelete && m_Cursor->NextNode)
        {
            m_Cursor = m_Cursor->NextNode; // might be error because it could point to null

            delete TempBack;

            deleted++;

            m_ListSize--;

            TempBack = m_Cursor;
        }

        if (deleted != AmountDelete)
        {
            delete m_Cursor;
            m_Cursor = nullptr;
        }

        TempFront->NextNode = m_Cursor;

        TempFront, TempBack = nullptr;
    }

    void PrintList()
    {
        m_Cursor = m_Head;

        while (m_Cursor)
        {
            std::cout << m_Cursor->data << " "; // segfault??????

            m_Cursor = m_Cursor->NextNode;
        }

        std::cout << std::endl;

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
// class TwoWayLinkedList
// {
//     struct m_Node
//     {
//         T data;

//         struct m_Node* PreviousNode, NextNode = nullptr;
//     }

//     struct m_Node* m_Head, m_Cursor = nullptr;

// public:

//     void Create2WayList (std::vector<T> items)
//     {
//         if (items.empty()) return;

//         m_Cursor = m_Head = new m_Node;

//         m_Head->data = items[0];

//         // if(items.size > 1)
//         // {
//     }

//     void PushBackItems() // add items to back

//     void SqueezeItems() // add items to front

// };

// template<class T> // maybe, maybe not, redundant work?
// class LinkedList_3D
// {};

int main()
{
    OneWayLinkedList<int> List1Way;

    List1Way.CreateList({1, 2});

    List1Way.AppendItems({3, 4, 5, 6});

    List1Way.CreateList({7}); // will append instead of create new

    List1Way.PrintList();

    List1Way.InsertItems(0, {4, 3}); // currently will only work from the second element up

    List1Way.PrintList();

    List1Way.RemoveItems(0, 20); // currently will only work from the second element up

    List1Way.PrintList();

    List1Way.DeleteList();

    return 0;
}