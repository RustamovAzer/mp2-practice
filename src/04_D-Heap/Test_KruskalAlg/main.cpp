#include "../Algorithms/Algorithms.h"
#include "iostream"

int main()
{
    int verticesCount = 6;
    int* vertices = new int[verticesCount];
    for (int i = 0; i < verticesCount; i++)
        vertices[i] = i;
    int edgesCount = 11;
    TEdge edges[11] = { TEdge(0, 5, 2), TEdge(0, 4, 3), TEdge(0, 1, 8), TEdge(1, 4, 6),
                        TEdge(1, 2, 10), TEdge(1, 3, 1), TEdge(1, 5, 2), TEdge(2, 3, 5),
                        TEdge(2, 4, 2), TEdge(2, 5, 9), TEdge(3, 4, 4) };

    TGraph tmp(verticesCount, vertices, edges, edgesCount);
    std::cout << tmp << std::endl;
    TGraph spanningTree = KruskalAlgorithm::kruskalAlgorithm(tmp);
    std::cout << spanningTree;
    spanningTree.printAdjacencyMatrix();

    std::cout << "//~~~~~~~~~~~~~~~~~~~~~~~~~~~//" << std::endl << std::endl;
    delete[] vertices;
    system("pause");
    return 0;
}