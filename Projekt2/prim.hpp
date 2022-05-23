#pragma once
#include <cmath>
#include "graph.hpp"
#include "graphMat.hpp"

template<typename T>
struct Node
{
    T vertex;
    int edge;
    T parent;
};
//Deklaracje kopca
inline int parent(int i)   
{
    return std::ceil(i / 2.f) - 1;
}

inline int left(int i)
{
    return (i * 2) + 1;
}

inline int right(int i)
{
    return (i * 2) + 2;
}

template <typename T>
void min_heapify(list<Node<T>>& tab, int size, int i)
{
    int l = left(i);
    int r = right(i);
    int q = i;
    if (l < size && tab[l].edge < tab[i].edge)
    {
        q = l;
    }
    if (r < size && tab[r].edge < tab[q].edge)
    {
        q = r;
    }
    if (q != i)
    {
        std::swap(tab[i], tab[q]);
        min_heapify(tab, size, q);
    }
}

template <typename T>
void build_min_heap(list<Node<T>>& tab, int size)
{
    for (int i = (size / 2) + 1; i >= 0; --i)
    {
        min_heapify(tab, size, i);
    }
}


template<typename T>
list<Node<T>> prim(Graph<T, int> G, T start) //Algorytm Prima dla listy sasiedztwa
{
    list<Node<T>> U;
    auto ver = G.vertices(); //lista wierzcholkow

    for (int i = 0; i < ver.size(); ++i) //inicjalizacja listy
    {
        U.insert(Node<T>());
        U[i].vertex = ver[i];
        U[i].edge = 100000000;
          if (ver[i] == start)
        {
            U[i].edge = 0;
            U[i].parent = ver[i];
        }
    }

    build_min_heap(U, U.size());

    for (int j = 0; j < U.size(); ++j)
    {
        build_min_heap(U, U.size() - j); //najmniejszy element na gorze
        auto min = U[0];

        auto edges = G.incidentEdges(min.vertex); //sprawdzanie krawedzi najmniejszego elementu
        for (int i = 0; i < edges.size(); ++i)
        {
            T opp = G.opposite(min.vertex, edges[i]); //sprawdzanie sasiadow min wierzcholka
            int found = -1;
            for (int k = 0; k < U.size() - j; ++k) //przeszukanie listy wierzcholkow z tym sasiadem
                if (opp == U[k].vertex)
                    found = k;
            if (found != -1)
                if (U[found].edge > edges[i])
                {
                    U[found].parent = min.vertex;
                    U[found].edge = edges[i];
                }
        }
        std::swap(U[0], U[U.size() - j - 1]);
    }
    return U;
}

template<typename T, size_t N>
list<Node<T>> prim(GraphMat<T, int, N> G, T start) //algorytm prima dla macierzy sasiedztwa
{
    list<Node<T>> U;
    auto ver = G.vertices(); //lista wierzcholkow

    for (int i = 0; i < ver.size(); ++i) //inicjalizacja listy
    {
        U.insert(Node<T>());
        U[i].vertex = ver[i];
        U[i].edge = 100000000;
        if (ver[i] == start)
        {
            U[i].edge = 0;
            U[i].parent = ver[i];
        }
    }

    build_min_heap(U, U.size());

    for (int j = 0; j < U.size(); ++j)
    {
        build_min_heap(U, U.size() - j); //najmniejszy element na gorze
        auto min = U[0];

        auto edges = G.incidentEdges(min.vertex); //sprawdzanie krawedzi najmniejszego elementu
        for (int i = 0; i < edges.size(); ++i)
        {
            T opp = G.opposite(min.vertex, edges[i]); //sprawdzanie sasiadow min wierzcholka
            int found = -1;
            for (int k = 0; k < U.size() - j; ++k) //przeszukanie listy wierzcholkow z tym sasiadem
                if (opp == U[k].vertex)
                    found = k;
            if (found != -1)
                if (U[found].edge > edges[i])
                {
                    U[found].parent = min.vertex;
                    U[found].edge = edges[i];
                }
        }
        std::swap(U[0], U[U.size() - j - 1]);
    }
    return U;
}