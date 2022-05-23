#pragma once

#include "list.hpp"
#include "pair.hpp"

template <typename Vertex, typename Edge>
class Graph
{
    public:
        Graph();
        Pair<Vertex> endVertices(Edge e);
        Vertex opposite(Vertex v, Edge e);
        bool areAdjacent(Vertex v, Vertex w);
        void replaceVertex(Vertex v, Vertex x);
        void replaceEdge(Edge v, Edge x);
        void insertVertex(Vertex o);
        void insertEdge(Vertex v, Vertex w, Edge o);
        void removeVertex(Vertex v);
        void removeEdge(Edge e);
        void merge(Graph& g);
        bool isPath(Vertex v, Vertex w);
        list<Edge> incidentEdges(Vertex v);
        list<Vertex> vertices();
        list<Edge> edges();
    public:
        struct Ver;
        struct Ed;

        struct Ver
        {
            Vertex value;
            list<Ed*> edges;
            bool operator==(const Ver& rhs) const { return value == rhs.value; }
        };

        struct Ed
        {
            Edge value;
            Pair<Ver*> vertices;
            bool operator==(const Ed& rhs) const { return value == rhs.value; }
        };
    private:
        list<Ver> mVertices;
        list<Ed> mEdges;
};

template<typename Vertex, typename Edge>
Graph<Vertex, Edge>::Graph()
: mVertices()
, mEdges()
{ }

template<typename Vertex, typename Edge>
Pair<Vertex> Graph<Vertex, Edge>::endVertices(Edge e) //wierzcholki krawedzi
{
    for (int i = 0; i < mEdges.size(); ++i)
        if (mEdges[i].value == e)
            return {mEdges[i].vertices.first->value, mEdges[i].vertices.second->value};
}

template<typename Vertex, typename Edge>
Vertex Graph<Vertex, Edge>::opposite(Vertex v, Edge e) //przeciwny wierzcholek
{
    for (int i = 0; i < mEdges.size(); ++i)
        if (mEdges[i].value == e)
            if (mEdges[i].vertices.first->value == v)
                return mEdges[i].vertices.second->value;
            else
                return mEdges[i].vertices.first->value;
}

template<typename Vertex, typename Edge>
bool Graph<Vertex, Edge>::areAdjacent(Vertex v, Vertex w) //sprawdzenie czy wierzcholki sa sasiednie
{
    for (int i = 0; i < mEdges.size(); ++i)
        if ((mEdges[i].vertices.first->value == v && mEdges[i].vertices.second->value == w) 
        || (mEdges[i].vertices.first->value == w && mEdges[i].vertices.second->value == v))
            return true;
    return false;
}

template<typename Vertex, typename Edge>
void Graph<Vertex, Edge>::replaceVertex(Vertex v, Vertex x) //zastap wierzcholek
{
    for (int i = 0; i < mVertices.size(); ++i)
        if (mVertices[i].value == v)
            mVertices[i].value = x;
}

template<typename Vertex, typename Edge>
void Graph<Vertex, Edge>::replaceEdge(Edge v, Edge x) //zastap krawedz
{
    for (int i = 0; i < mEdges.size(); ++i)
        if (mEdges[i].value == v)
            mEdges[i].value = x;
}

template<typename Vertex, typename Edge>
void Graph<Vertex, Edge>::insertVertex(Vertex o) // dodaj wierzcholek
{
    Ver inserted;
    inserted.value = o;
    mVertices.insert(inserted);
}

template<typename Vertex, typename Edge>
void Graph<Vertex, Edge>::insertEdge(Vertex v, Vertex w, Edge o) //dodaj krawedz
{
    Ver* V;
    Ver* W;
    for (int i = 0; i < mVertices.size(); ++i)
    {
        if (mVertices[i].value == v)
            V = &mVertices[i];
        if (mVertices[i].value == w)
            W = &mVertices[i];
    }

    Ed* O = new Ed;
    O->value = o;
    O->vertices = {V, W};

    V->edges.insert(O);
    W->edges.insert(O);
    mEdges.insert(*O);
}

template<typename Vertex, typename Edge>
void Graph<Vertex, Edge>::removeVertex(Vertex v) //usun wierzcholek wraz z krawedziami
{
    Ver* V;
    for (int i = 0; i < mVertices.size(); ++i)
        if (mVertices[i].value == v)
            V = &mVertices[i];
    
    for (int i = 0; i < V->edges.size(); ++i)
        removeEdge(V->edges[i]->value);

    mVertices.remove(*V);
}

template<typename Vertex, typename Edge>
void Graph<Vertex, Edge>::removeEdge(Edge e) //usun krawedz
{
    Ed* O;
    for (int i = 0; i < mEdges.size(); ++i)
        if (mEdges[i].value == e)
            O = &mEdges[i];

    O->vertices.first->edges.remove(O);
    O->vertices.second->edges.remove(O);

    mEdges.remove(*O);
}

template<typename Vertex, typename Edge>
void Graph<Vertex, Edge>::merge(Graph& g)
{
    auto e = g.edges();

    for (int i = 0; i < e.size(); ++i)
    {
        auto v = g.endVertices(e[i]);
        insertVertex(v.first);
        insertVertex(v.second);
        insertEdge(v.first, v.second, e[i]);
    }
}

template<typename Vertex, typename Edge>
bool Graph<Vertex, Edge>::isPath(Vertex v, Vertex w)  //Sprawdzanie czy isnieje droga pomiedzy wierzcholkami
{
    list<Vertex> visted;
    queue<Vertex> q;
    q.push(v);
    while (!q.empty())
    {
        Vertex a = q.front();
        q.pop();

        auto kurwa = incidentEdges(a);
        for (int i = 0; i < kurwa.size(); ++i)
        {
            Vertex b = opposite(a, kurwa[i]);
            if (b == w)
                return true;
            bool isVisted = false;
            for (int j = 0; j < visted.size(); ++j)
                if (visted[j] == b)
                    isVisted = true;
            if (!isVisted)
                q.push(b);
            visted.insert(a);
        }
    }
    return false;

}

template<typename Vertex, typename Edge>
list<Edge> Graph<Vertex, Edge>::incidentEdges(Vertex v) //krawedzie przylegajace do wierzcholka
{
    list<Edge> ret;
    Ver* V;
    for (int i = 0; i < mVertices.size(); ++i)
        if (mVertices[i].value == v)
            V = &mVertices[i];

    for (int i = 0; i < V->edges.size(); ++i)
        ret.insert(V->edges[i]->value);

    return ret;
}

template<typename Vertex, typename Edge>
list<Vertex> Graph<Vertex, Edge>::vertices() //wszystkie wierzcholki
{
    list<Vertex> ret;
    for (int i = 0; i < mVertices.size(); ++i)
        ret.insert(mVertices[i].value);

    return ret;
}

template<typename Vertex, typename Edge>
list<Edge> Graph<Vertex, Edge>::edges() //wszystkie krawedzie
{
    list<Edge> ret;
    for (int i = 0; i < mEdges.size(); ++i)
        ret.insert(mEdges[i].value);

    return ret;
}
