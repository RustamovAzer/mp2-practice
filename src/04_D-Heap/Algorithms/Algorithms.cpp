#include "Algorithms.h"
#include "iostream"



void HeapSort::heapSort(int _size, int _array[])
{
    int size = _size;
    TDHeap<int> heap(2, size, size, _array);
    for (int i = size - 1; i >= 0; i--)
    {
        _array[size - i - 1] = heap.getRoot();
        heap.removeMinKey();
    }
}

TGraph KruskalAlgorithm::kruskalAlgorithm(const TGraph& _graph)
{
    int verticesCount = _graph.verticesCount;
    TDisjointSet vertices(verticesCount, _graph.vertices);
    for (int i = 0; i < verticesCount; i++)
        vertices.makeSet(i);
    TDHeap<TEdge> edges(2, _graph.edgesCount, _graph.edgesCount, _graph.edges);
    TGraph resultTree(verticesCount, _graph.vertices);


    while (resultTree.edgesCount != verticesCount - 1)
    {
        TEdge edgeWithMinWeight = edges.getRoot();
        edges.removeMinKey();
        if (vertices.find(edgeWithMinWeight.startVertex) != vertices.find(edgeWithMinWeight.endVertex))
        {
            vertices.unite(edgeWithMinWeight.startVertex, edgeWithMinWeight.endVertex);
            resultTree.addNewEdge(edgeWithMinWeight);
        }
    }

    return resultTree;
}