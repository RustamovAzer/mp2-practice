#include "TGraph.h"
#include <exception>


TGraph::TGraph(int _verticesCount, int* _vertices)
{
    verticesCount = _verticesCount;
    vertices = new int[verticesCount];
    for (int i = 0; i < verticesCount; i++)
        vertices[i] = _vertices[i];
    edgesCount = _verticesCount * (_verticesCount - 1) / 2;
    edges = new TEdge[edgesCount];
    edgesCount = 0;
}

TGraph::TGraph(int _verticesCount, int* _vertices, TEdge* _edges, int _edgesCount)
{
    verticesCount = _verticesCount;
    vertices = new int[verticesCount];
    for (int i = 0; i < verticesCount; i++)
        vertices[i] = _vertices[i];
    edgesCount = _edgesCount;
    edges = new TEdge[edgesCount];
    for (int j = 0; j < edgesCount; j++)
        edges[j] = _edges[j];
}

TGraph::TGraph(const TGraph& _graph)
{
    verticesCount = _graph.verticesCount;
    edgesCount = _graph.edgesCount;
    vertices = new int[verticesCount];
    for (int i = 0; i < verticesCount; i++)
        vertices[i] = _graph.vertices[i];
    edges = new TEdge[edgesCount];
    for (int j = 0; j < edgesCount; j++)
        edges[j] = _graph.edges[j];
}

TGraph::~TGraph()
{
    delete[] vertices;
    delete[] edges;
}

void TGraph::addNewEdge(const TEdge& _newEdge)
{
    int maxCountOfEdges = verticesCount * (verticesCount - 1) / 2;
    if (edgesCount + 1 > maxCountOfEdges)
        throw std::exception("Incorrect number of edges");
    if (!isEdgeInGraph(_newEdge))
        edges[edgesCount++] = _newEdge;
}

bool TGraph::isEdgeInGraph(const TEdge& _edge)
{
    for (int i = 0; i < edgesCount; i++)
        if (edges[i] == _edge)
            return true;
    return false;
}

TEdge::TEdge(const TEdge& _edge)
{
    startVertex = _edge.startVertex;
    endVertex = _edge.endVertex;
    weight = _edge.weight;
}

bool TEdge::operator>(const TEdge& _edge)
{
    return this->weight > _edge.weight;
}

bool TEdge::operator<(const TEdge& _edge)
{
    return this->weight < _edge.weight;
}

bool TEdge::operator==(const TEdge& _edge)
{
    if ((this->startVertex == _edge.startVertex)
        && (this->endVertex == _edge.endVertex))
        return true;
    if ((this->startVertex == _edge.endVertex)
        && (this->endVertex == _edge.startVertex))
        return true;
    return false;
}

const TEdge& TEdge::operator=(const TEdge& _edge)
{
    if (*this == _edge)
        return *this;
    startVertex = _edge.startVertex;
    endVertex = _edge.endVertex;
    weight = _edge.weight;
    return *this;
}

std::ostream& operator<<(std::ostream& out, const TGraph& _graph)
{
    out << "Vertices: [ ";
    for (int i = 0; i < _graph.verticesCount; i++)
        out << _graph.vertices[i] << " ";
    out << "]" << std::endl;
    out << "Edges: [ ";
    for (int i = 0; i < _graph.edgesCount; i++)
        out << "(" << _graph.edges[i].startVertex << " " << _graph.edges[i].endVertex << ") ";
    //<< " " << _graph.edges[i].weight << ") ";
    out << "]" << std::endl;
    return out;
}

int* TGraph::getAdjacencyMatrix()
{
    int* adjacencyMatrix = new int[verticesCount * verticesCount];
    for (int k = 0; k < verticesCount * verticesCount; k++)
        adjacencyMatrix[k] = 0;

    for (int i = 0; i < edgesCount; i++)
    {
        TEdge currentEdge = edges[i];
        int startVertex = currentEdge.startVertex;
        int endVertex = currentEdge.endVertex;
        adjacencyMatrix[startVertex * verticesCount + endVertex] = currentEdge.weight;
        adjacencyMatrix[endVertex * verticesCount + startVertex] = currentEdge.weight;
    }

    return adjacencyMatrix;
}

void TGraph::printAdjacencyMatrix()
{
    int* adjacencyMatrix = getAdjacencyMatrix();

    for (int i = 0; i < verticesCount; i++)
    {
        for (int j = 0; j < verticesCount; j++)
            std::cout << adjacencyMatrix[i * verticesCount + j] << " ";
        std::cout << std::endl;
    }

    delete[] adjacencyMatrix;
};