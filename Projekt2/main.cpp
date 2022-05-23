#include <iostream>
#include <cstdlib>
#include <chrono>
#include "kruskal.hpp"
#include "prim.hpp"

int main()
{
    
  
    // std::srand(std::chrono::steady_clock::now().time_since_epoch().count());
    // //Graph<int, int> G;
    
    // constexpr int vsize = 500;
    // constexpr int esize = (vsize / 2);
    // GraphMat<int, int, vsize> G;
    // for (int i = 0; i < vsize; ++i)
    //     G.insertVertex(i);
    // for (int i = 0; i < vsize; ++i)
    //     G.insertEdge(i, vsize - i - 1, rand());

    // auto start = std::chrono::steady_clock::now();
    // kruskal(G);
    // //prim(G,0);
    // auto end = std::chrono::steady_clock::now();
    // unsigned int time = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    // std::cout << "Time: " << time << std::endl;


    Graph<int, int> V;
    //GraphMat<int, int, 6> V;
    V.insertVertex(0);
    V.insertVertex(1);
    V.insertVertex(2);
    V.insertVertex(3);
    V.insertVertex(4);
    V.insertEdge(0, 1, 3);
    V.insertEdge(1, 2, 6);
    V.insertEdge(2, 3, 1);
    V.insertEdge(3, 0, 5);
    V.insertEdge(3, 4, 2);
    V.insertEdge(1, 3, 4);

    
    // auto a = kruskal(V);
    // auto e = a.edges();
    // for (int i = 0; i < e.size(); ++i)
    // {
    //     auto v = a.endVertices(e[i]);
    //     std::cout << v.first << " " << v.second << " " << e[i] << std::endl;
    // }

    auto a = prim(V, 0);
    for (int i = 0; i < a.size(); ++i)
        std::cout << a[i].vertex << " " << a[i].parent << " " << a[i].edge << std::endl;

}