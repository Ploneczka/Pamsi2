#pragma once

#include "list.hpp"
#include "pair.hpp"

template <typename Vertex, typename Edge, size_t N>
class GraphMat
{
    public:
        GraphMat();
        Pair<Vertex> endVertices(Edge e);
        Vertex opposite(Vertex v, Edge e);
        bool areAdjacent(Vertex v, Vertex w);
        void replaceVertex(Vertex v, Vertex x);
        void replaceEdge(Edge v, Edge x);
        void insertVertex(Vertex o);
        void insertEdge(Vertex v, Vertex w, Edge o);
        void removeVertex(Vertex v);
        void removeEdge(Edge e);
        //void merge(GraphMat& g);
        bool isPath(Vertex v, Vertex w);
        list<Edge> incidentEdges(Vertex v);
        list<Vertex> vertices();
        list<Edge> edges();
        list<Edge> sortEdges();
    public:
        struct Ver;
        struct Ed;

        struct Ver
        {
            Vertex value;
            int Lp;
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
        Ed* mat[N][N];
};

template<typename Vertex, typename Edge, size_t N>
GraphMat<Vertex, Edge, N>::GraphMat()
: mVertices()
, mEdges()
, mat{nullptr}
{ }

template<typename Vertex, typename Edge, size_t N>
Pair<Vertex> GraphMat<Vertex, Edge, N>::endVertices(Edge e)
{
     for (int i = 0; i < mEdges.size(); ++i)
        if (mEdges[i].value == e)
            return {mEdges[i].vertices.first->value, mEdges[i].vertices.second->value};
}

template<typename Vertex, typename Edge, size_t N>
Vertex GraphMat<Vertex, Edge, N>::opposite(Vertex v, Edge e)
{
    for (int i = 0; i < mEdges.size(); ++i)
        if (mEdges[i].value == e)
            if (mEdges[i].vertices.first->value == v)
                return mEdges[i].vertices.second->value;
            else
                return mEdges[i].vertices.first->value;
}

template<typename Vertex, typename Edge, size_t N>
bool GraphMat<Vertex, Edge, N>::areAdjacent(Vertex v, Vertex w)
{
   for (int i = 0; i < mEdges.size(); ++i)
        if ((mEdges[i].vertices.first->value == v && mEdges[i].vertices.second->value == w) 
        || (mEdges[i].vertices.first->value == w && mEdges[i].vertices.second->value == v))
            return true;
    return false; 
}

template<typename Vertex, typename Edge, size_t N>
void GraphMat<Vertex, Edge, N>::replaceVertex(Vertex v, Vertex x)
{
    for (int i = 0; i < mVertices.size(); ++i)
        if (mVertices[i].value == v)
            mVertices[i].value = x;
}

template<typename Vertex, typename Edge, size_t N>
void GraphMat<Vertex, Edge, N>::replaceEdge(Edge v, Edge x)
{
    for (int i = 0; i < mEdges.size(); ++i)
        if (mEdges[i].value == v)
            mEdges[i].value = x;
}

template<typename Vertex, typename Edge, size_t N>
void GraphMat<Vertex, Edge, N>::insertVertex(Vertex o)
{
    Ver inserted;
    inserted.value = o;
    inserted.Lp = mVertices.size();
    mVertices.insert(inserted);
}

template<typename Vertex, typename Edge, size_t N>
void GraphMat<Vertex, Edge, N>::insertEdge(Vertex v, Vertex w, Edge o)
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

    mat[V->Lp][W->Lp] = O;
    mat[W->Lp][V->Lp] = O;
    mEdges.insert(*O);
}

template<typename Vertex, typename Edge, size_t N>
void GraphMat<Vertex, Edge, N>::removeVertex(Vertex v)
{
    Ver* V;
    for (int i = 0; i < mVertices.size(); ++i)
        if (mVertices[i].value == v)
            V = &mVertices[i];
    
    for (int i = 0; i < V->edges.size(); ++i)
        removeEdge(V->edges[i]->value);

    mVertices.remove(*V);
}

template<typename Vertex, typename Edge, size_t N>
void GraphMat<Vertex, Edge, N>::removeEdge(Edge e)
{
    Ed* O;
    for (int i = 0; i < mEdges.size(); ++i)
        if (mEdges[i].value == e)
            O = &mEdges[i];

    mat[O->vertices.first->Lp][O->vertices.second->Lp] = nullptr;
    mat[O->vertices.second->Lp][O->vertices.first->Lp] = nullptr;

    mEdges.remove(*O);
}

template<typename Vertex, typename Edge, size_t N>
list<Edge> GraphMat<Vertex, Edge, N>::incidentEdges(Vertex v)
{
    list<Edge> ret;
    Ver* V;
    for (int i = 0; i < mVertices.size(); ++i)
        if (mVertices[i].value == v)
            V = &mVertices[i];

    for (int i = 0; i < N; ++i)
        if (mat[V->Lp][i] != nullptr)
            ret.insert(mat[V->Lp][i]->value);

    return ret;
}

// template<typename Vertex, typename Edge, size_t N>
// void GraphMat<Vertex, Edge, N>::merge(GraphMat& g)
// {
//     auto e = g.edges();

//     for (int i = 0; i < e.size(); ++i)
//     {
//         auto v = g.endVertices(e[i]);
//         insertVertex(v.first);
//         insertVertex(v.second);
//         insertEdge(v.first, v.second, e[i]);
//     }
// }

template<typename Vertex, typename Edge, size_t N>
bool GraphMat<Vertex, Edge, N>::isPath(Vertex v, Vertex w)
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
template<typename Vertex, typename Edge, size_t N>
list<Vertex> GraphMat<Vertex, Edge, N>::vertices()
{
    list<Vertex> ret;
    for (int i = 0; i < mVertices.size(); ++i)
        ret.insert(mVertices[i].value);

    return ret;
}

template<typename Vertex, typename Edge, size_t N>
list<Edge> GraphMat<Vertex, Edge, N>::edges()
{
    list<Edge> ret;
    for (int i = 0; i < mEdges.size(); ++i)
        ret.insert(mEdges[i].value);

    return ret;
}

template<typename Vertex, typename Edge, size_t N>
list<Edge> GraphMat<Vertex, Edge, N>::sortEdges()
{
    list <Edge> sorte;
    for(int i = 0 ; i < mEdges.size(); ++i)
    {
        for (int j = 0; j <mEdges.size() - i; ++j)
        {
            
        }
    }

    return sorte;
}
