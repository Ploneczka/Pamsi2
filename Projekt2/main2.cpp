#include "graph.hpp"
#include "graphMat.hpp"
#include <iostream>

int main()
{   
    //GraphMat<int, double, 3> a;
    Graph<int, double> a;
    a.insertVertex(3);
    a.insertVertex(2);
    a.insertVertex(1);
    a.insertVertex(4);
    a.insertVertex(5);
    a.insertVertex(6);
    a.insertVertex(7);
    a.insertVertex(8);
   
    a.insertEdge(1, 2, 0.5);
    a.insertEdge(1, 6, 1.5);
    a.insertEdge(1, 3, 1);

    a.insertEdge(3, 2, 1.1);
    a.insertEdge(3, 4, 2);
    
    a.insertEdge(4, 5, 1.7);
    a.insertEdge(4, 8, 1.3);

    a.insertEdge(5, 2, 0.7);
    a.insertEdge(5, 8, 1.9);
    a.insertEdge(5, 7, 1.4);

    a.insertEdge(6, 2, 0.4);
    a.insertEdge(6, 7, 0.1);

    a.insertEdge(8, 7, 0.2);

    auto v = a.endVertices(1.5);                                 // Ukazuje wierzcholki krawedzi o owadze 0.5
    std::cout << v.first << " " << v.second << std::endl;

    // auto e = a.vertices();                                       // Ukazuje wszytskie wierzcholki grafu
    // for (int i = 0; i < e.size(); ++i)
    //     std::cout << e[i] << std::endl;

     std::cout << a.opposite(2, 1.1) << " " << a.opposite(2, 0.5) << std::endl;       //Ukazuje drugi wierzcholek krawedzi 1.1 i wierzcholka 2

    // std::cout << a.areAdjacent(3, 2) << " " << a.areAdjacent(1, 3) << std::endl;     // Sprawdza czy dane wierzcholki sa polaczone krawedzia

    // a.replaceVertex(3, 4);                                           //Zmiana wierzcholka 3 na 4
    // std::cout << a.opposite(2, 1.1) << std::endl;

    // a.replaceEdge(1.1, 2.2);                                     //Zmiana krawedzi 1.1 na 2.2
    // std::cout << a.opposite(2, 2.2) << std::endl;

    // auto q = a.incidentEdges(2);                                 //Wypisanie krawedzi przyleglych do wierzcholka 2
    // for (int i = 0; i < q.size(); ++i)
    //     std::cout << q[i] << " ";

    
}