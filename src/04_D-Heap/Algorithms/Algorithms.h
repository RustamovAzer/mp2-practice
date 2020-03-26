#ifndef __ALGORITHMS__H__
#define __ALGORITHMS__H__

#include "TDHeap.h"
#include "TDisjointSet.h"
#include "TGraph.h"

static class HeapSort
{
public:
    static void heapSort(int _size, int _arr[]);
};

static class KruskalAlgorithm
{
public:
    static TGraph kruskalAlgorithm(const TGraph& _graph);
};

#endif // !__ALGORITHMS__H__
