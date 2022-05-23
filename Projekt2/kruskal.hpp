#pragma once
#include "graph.hpp"
#include "graphMat.hpp"

template<typename T>
void quick_sort(list<T>& tab, int left, int right) //quickosr listy 
{
	if(right <= left) return;
	
	int i = left - 1, j = right + 1, 
	pivot = tab[(left+right)/2];
	
	while(1)
	{
		while(i + 1 < tab.size() && pivot>tab[++i]);
		
		while(j - 1 >= 0 && pivot<tab[--j]);
		
		if( i <= j)
			std::swap(tab[i],tab[j]);
		else
			break;
	}

	if(j > left)
	quick_sort(tab, left, j);
	if(i < right)
	quick_sort(tab, i, right);
}

template<typename T, typename P>
Graph<T, P> kruskal(Graph<T, P> graph) //Algorytm kruskala dla listy sasiedztwa
{
    Graph<T, P> A;

    auto ver = graph.vertices(); //lista wierzcholkow
    for (int i = 0; i < ver.size(); ++i)
        A.insertVertex(ver[i]);  //graf bez wag

    list<int> edges = graph.edges(); //lista krawedzi
    quick_sort(edges, 0, edges.size() - 1); //sortowanie wagowe krawedzi

    for (int i = 0; i < edges.size(); ++i)
    {
        auto p = graph.endVertices(edges[i]); //zwracamy pare wierzcholkow danej krawedzi

        if (!A.isPath(p.first, p.second))
        {
            A.insertEdge(p.first, p.second, edges[i]);
        }
    }

    return A;
}

template<typename T, typename P, size_t N>
GraphMat<T, P, N> kruskal(GraphMat<T, P, N> graph)  //Algorytm kruskala dla macierzy sasiedztwa
{
    GraphMat<T, P, N> A;

    auto ver = graph.vertices(); //lista wierzcholkow
    for (int i = 0; i < ver.size(); ++i)
        A.insertVertex(ver[i]);  //graf bez wag

    list<int> edges = graph.edges(); //lista krawedzi
    quick_sort(edges, 0, edges.size() - 1); //sortowanie wagowe krawedzi

    for (int i = 0; i < edges.size(); ++i)
    {
        auto p = graph.endVertices(edges[i]); //zwracamy pare wierzcholkow danej krawedzi

        if (!A.isPath(p.first, p.second))
        {
            A.insertEdge(p.first, p.second, edges[i]);
        }
    }

    return A;
}