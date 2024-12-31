#pragma once
#include <iostream>
using namespace std;

class LNode
{
public:
    string data;
    LNode *next;

    LNode()
    {
        data = "";
        next = NULL;
    }

    LNode(string x)
    {
        data = x;
        next = NULL;
    }

    string getdata()
    {
        return data;
    }

    LNode *getnext()
    {
        return next;
    }

    void setdata(string dataa)
    {
        data = dataa;
    }

    void setnext(LNode *nextt)
    {
        next = nextt;
    }

    ~LNode()
    {
        delete next;
    }
};

class SLinkedList
{

public:
    LNode *head;

    SLinkedList()
    {
        head = NULL;
    }

    void insert(string data)
    {

        LNode *temp = new LNode(data);
        /*temp->setnext(head);
        head = temp;*/

        if (isEmpty())
        {
            head = temp;
        }

        else
        {

            LNode *ptr = head;

            while (ptr->next != NULL)
            {
                ptr = ptr->getnext();
            }
            ptr->setnext(temp);
        }
    }

    void insertAtHead(string data)
    {
        LNode *temp = new LNode(data);
        /*temp->setdata(x);
        temp->setnext(NULL);*/

        if (isEmpty())
        {
            head = temp;
        }

        else
        {

            LNode *ptr = temp;
            ptr->setnext(head);
            head = ptr;
        }
    }

    bool isEmpty()
    {

        if (head == NULL)
            return true;

        else
            return false;
    }

    int search(string data)
    {
        LNode *temp = head;
        int index = 0;

        while (temp != NULL)
        {
            if (temp->getdata() == data)
                return index;

            temp = temp->getnext();
            index++;
        }

        return -1;
    }

    void update(string value, string newValue)
    {

        LNode *ptr = head;

        while (ptr != NULL)
        {
            if (ptr->getdata() == value)
                ptr->setdata(newValue);
            ptr = ptr->getnext();
        }
    }

    void InsertAtIndex(string data, int index)
    {

        LNode *ptr = head;
        int counter = 0;

        if (index < 0 || index > counter)
            return;

        while (ptr != NULL)
        {
            counter++;

            if (counter == index)
            {
                ptr->data = data;
            }
            ptr = ptr->next;
        }
    }

    // void remove(string value)
    // {

    //     LNode *ptr = head;
    //     LNode *curr = head;

    //     while (curr->getnext()->getdata() != value)
    //     {
    //         curr = curr->getnext();
    //         ptr = curr->getnext();
    //     }

    //     curr->setnext(curr->getnext()->getnext());
    //     delete ptr;
    // }

    void print()
    {
        if (isEmpty())
        {
            return;
        }

        LNode *temp = head;
        while (temp != nullptr)
        {
            if (temp->getnext() == NULL)
            {
                cout << temp->getdata();
            }
            else
            {
                cout << temp->getdata() << " -> ";
            }
            temp = temp->getnext();
        }
        cout << endl;
    }

    ~SLinkedList()
    {
        LNode *temp = head;
        while (temp != NULL)
        {
            head = head->getnext();
            delete temp;
            temp = head;
        }
    }
};