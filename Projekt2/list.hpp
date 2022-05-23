#pragma once

#include <cassert>
#include <cstddef>

template <typename T>  // Zdefiniowana Lista jednokierunkowa
class list
{
    public:
        list();
 
        void insert(T value);
        void remove(T value);
        size_t size() const;

        T& operator[](size_t index);
        const T& operator[](size_t index) const;
    private:
        struct Node
        {
            T value;
            Node* next;
            Node* prev;
        };
    private:
        Node* mBegin;
        Node* mEnd;
        size_t mSize;
};

template<typename T>
list<T>::list()
: mBegin(nullptr)
, mEnd(nullptr)
, mSize(0)
{ }

template<typename T>
void list<T>::insert(T value)  //Dodawanie
{
    if (mBegin == nullptr)
    {
        mBegin = new Node;
        mEnd = mBegin;

        mBegin->value = value;
        mBegin->next = mEnd;
        mBegin->prev = nullptr;

        mEnd->next = nullptr;
        mEnd->prev = mBegin;
    }
    else
    {
        Node* n = new Node;
        n->value = value;
        n->prev = mEnd;
        n->next = nullptr;
        mEnd->next = n;
        mEnd = n;
    }
    mSize++;
}

template<typename T>
void list<T>::remove(T value)  //Usuwanie
{
    if (mSize <= 0)
        return;

    if (mBegin == mEnd)
    {
        Node* rem = mBegin;
        mBegin = nullptr;
        mEnd = nullptr;
        delete rem;
        mSize--;
        return;
    }

    if (mBegin->value == value)
    {
        Node* rem = mBegin;
        mBegin = mBegin->next;
        mBegin->prev = nullptr;
        delete rem;
        mSize--;
        return;
    }

    for (Node* b = mBegin; b != mEnd; b = b->next)
    {
        if (b->value == value)
        {
            b->prev->next = b->next;
            b->next->prev = b->prev;
            delete b;
            mSize--;
            return;
        }
    }

    if (mEnd->value == value)
    {
        Node* rem = mEnd;
        mEnd = mEnd->prev;
        mEnd->next = nullptr;
        delete rem;
        mSize--;
        return;
    }
}

template<typename T>
size_t list<T>::size() const   // Rozmiar 
{
    return mSize;
}

template<typename T>
const T& list<T>::operator[](size_t index) const  // Operator [] const
{
    assert(index < mSize && index >= 0);
    int i = 0;
    for (Node* b = mBegin; b != nullptr; b = b->next)
    {
        if (i == index)
            return b->value;
        ++i;
    }
}

template<typename T>
T& list<T>::operator[](size_t index)   //Operator []
{
    assert(index < mSize && index >= 0);
    int i = 0;
    for (Node* b = mBegin; b != nullptr; b = b->next)
    {
        if (i == index)
            return b->value;
        ++i;
    }
}

#include <queue>
using namespace std;