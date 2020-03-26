#ifndef __TGRAPH__H__
#define __TGRAPH__H__

#include "TDisjointSet.h"
#include "iostream"

struct TEdge
{
    int startVertex;
    int endVertex;
    int weight;

    TEdge() :startVertex(0), endVertex(0), weight(0) {};
    TEdge(int _startVertex, int _endVertex, int _weight)
        : startVertex(_startVertex), endVertex(_endVertex), weight(_weight) {};
    TEdge(const TEdge& _edge);
    ~TEdge() {};

    bool operator>(const TEdge& _edge);
    bool operator<(const TEdge& _edge);
    bool operator==(const TEdge& _edge);

    const TEdge& operator=(const TEdge& _edge);
};

class TGraph
{
public:
    int* vertices;
    int verticesCount;
    TEdge* edges;
    int edgesCount;

    TGraph(int _verticesCount, int* _vertices);
    TGraph(int _verticesCount, int* _vertices, TEdge* _edges, int _edgesCount);
    TGraph(const TGraph& _graph);
    ~TGraph();

    void addNewEdge(const TEdge& _newEdge);
    bool isEdgeInGraph(const TEdge& _edge);

    int* getAdjacencyMatrix();
    void printAdjacencyMatrix();

    friend std::ostream& operator<<(std::ostream& out, const TGraph& _graph);

};

#endif // !__TGRAPH__H__