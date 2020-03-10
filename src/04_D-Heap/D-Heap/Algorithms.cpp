#include <iostream>
#include "Algorithms.h"

void HeapSort::heapSort(int _size, int _arr[])
{
    int size = _size;
    TDHeap<int> heap(2, size, size, _arr);
    for (int i = size - 1; i >= 0 ; i--)
    {
        _arr[size - i - 1] = heap.getRoot();
        heap.removeMinKey;
    }
}

TGraph KruskalAlgorithm::kruskalAlgorithm(const TGraph& _graph)
{
    int verticesCount = _graph.verticesCount;
    TDisjointSet vertices(verticesCount, _graph.vertices);
    for (int i = 0; i < verticesCount; i++)
        vertices.makeSet(i);
    TDHeap<TEdge> edges(2, _graph.edgesCount, _graph.edgesCount, _graph.edges);
    TGraph result(verticesCount, _graph.vertices);
    while (result.edgesCount != verticesCount - 1)
    {
        TEdge minWeightEdge = edges.getRoot();
        edges.removeMinKey;
        if ((vertices.find(minWeightEdge.startVertex)
            != vertices.find(minWeightEdge.endVertex)))
        {
            result.addNewEdge(minWeightEdge);
        }
    }
    return result;
}