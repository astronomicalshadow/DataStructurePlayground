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
    } // end of create list

    void AppendItems(std::vector<T> items) // append items to list
    {
        while (m_Cursor->NextNode) // doesn't care where m_Cursor is because its appending,
        {                           // as long its at the end
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
    } // end of append items

    void AppendItems(typename std::vector<T>::iterator items, typename std::vector<T>::iterator end) // append items to list, overload function
    {
        while (m_Cursor->NextNode)
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
    } // end of append items iterator overload

    void InsertItems(int Position, std::vector<T> items)
    {

        if (items.empty()) return;

        if (m_ListSize <= 0) 
        {
            CreateList(items); // incase List was deleted
            return;
        }
        
        if (Position == 0) // for inserting from the beginning
        {
            struct m_Node* Temp = m_Head; // save position of the head

            m_Head = nullptr; // make a new list, see CreateList if condition

            CreateList(items);

            m_Cursor->NextNode = Temp; // m_Cursor is always nullptr of the last appended node

            return;
        }

        if (Position >= m_ListSize) // out of scope protection
        {
            AppendItems(items);

            return;
        }

        // for all other cases

        int element = 0;

        m_Cursor = m_Head;

        while (element < Position)
        {
            m_Cursor = m_Cursor->NextNode;
            element++;
        }

        struct m_Node* Temp = m_Cursor->NextNode;

        m_Cursor->NextNode = nullptr;

        AppendItems(items);

        m_Cursor->NextNode = Temp; // cursor position changed to last element of new item because
                                    // used in the AppendItems call
    } // end of insert items

    void RemoveItems (int Position, int AmountDelete = 1)
    { 
        if (AmountDelete == 0) return;

        if (Position < 0 || Position > m_ListSize) return; // out of scope

        if (Position == 0) // if delete from the front
        {
            int element = 0;

            if (AmountDelete >= m_ListSize)
            {
                DeleteList(); // delete the whole list if amount to delete >= size of List

                return;
            }

            struct m_Node* TempSave = nullptr;

            while (element != AmountDelete) // find the starting point after deletion
            {
                m_Cursor = m_Cursor->NextNode;

                element++;
            }

            TempSave = m_Cursor; // save position to Temp

            m_Cursor = m_Head;

            while (m_Cursor->NextNode != TempSave->NextNode)
            {
                m_Cursor = m_Cursor->NextNode;

                delete m_Head;

                m_ListSize--;

                m_Head = m_Cursor;
            }

            return;

        } // end of delete from front 

         // delete from anywhere else

        int element, deleted = 0; // track position and amount deleted

        m_Cursor = m_Head;

        while (element < Position)
        {
            m_Cursor = m_Cursor->NextNode;

            element++;
        }

        struct m_Node* TempSave,* TempMove = nullptr; 
        
        TempSave = m_Cursor; // use to save position

        TempMove, m_Cursor = m_Cursor->NextNode; // use to delete

        while (deleted != AmountDelete && m_Cursor->NextNode) // exit if there is no NextNode
        {
            m_Cursor = m_Cursor->NextNode;

            delete TempMove;

            deleted++;

            m_ListSize--;

            TempMove = m_Cursor;
        }

        if (deleted != AmountDelete) // check if we deleted enough
        {
            delete m_Cursor;
            m_Cursor = nullptr;
        }

        TempSave->NextNode = m_Cursor; // connect Nodes together

    } // end of remove items

    void PrintList()
    {
        if (m_ListSize == 0) 
        {
            std::cout << "No List present\n";
            return;
        }

        m_Cursor = m_Head;

        while (m_Cursor->NextNode)
        {
            std::cout << m_Cursor->data << " ";

            m_Cursor = m_Cursor->NextNode;
        }

        std::cout << m_Cursor->data << " "; // print last node

        std::cout << "\n";

    }

    void DeleteList()
    {
        if (m_ListSize == 0) return;

        m_Cursor = m_Head;

        while (m_Cursor->NextNode)
        {
            m_Cursor = m_Head->NextNode;

            delete m_Head;

            m_Head = m_Cursor;
        }

        delete m_Cursor;

        m_Head = nullptr; // point at head incase more operations

        m_ListSize = 0;

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

    List1Way.CreateList({7});

    List1Way.AppendItems({8});

    List1Way.PrintList();

    List1Way.InsertItems(20, {-1, 0});

    List1Way.PrintList();

    // List1Way.RemoveItems(0, 20);

    // List1Way.PrintList();

    // List1Way.DeleteList();

    return 0;
}