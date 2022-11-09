using namespace std;
#include <string>

#include "GraphAdjList.h"

using namespace bridges;
#include "Bridges.h"
#include "DataSource.h"
#include "ImdbGraph.h"
#include "SLelement.h"
#include "data_src/ActorMovieIMDB.h"

bool ImdbGraph::doesVertexExist(string actorOrMovie) {
  unordered_map<string, Element<string> *> *vertices = graph.getVertices();
  bool isFound = (vertices->find(actorOrMovie) != vertices->end());
  return isFound;
}

std::string ImdbGraph::getVertexColor(string actorOrMovie) {
  unordered_map<string, Element<string> *> *vertices = graph.getVertices();
  std::string vertexColor;
  bool vertexMatch = (vertices->find(actorOrMovie) != vertices->end());
  if (vertexMatch) {
    vertexColor = graph.getVisualizer(actorOrMovie)->getColor().getHexValue();
  } else {
    vertexColor = "NA";
  }
  return vertexColor;
}

bool ImdbGraph::doesEdgeExist(string actorOrMovie1, string actorOrMovie2) {
  unordered_map<string, Element<string> *> *vertices = graph.getVertices();
  bool isEdge = false;
  bool vertexOneExist = (vertices->find(actorOrMovie1) != vertices->end());
  bool vertexTwoExist = (vertices->find(actorOrMovie2) != vertices->end());
  if (vertexOneExist && vertexTwoExist) {
    std::string vertexStart =
        graph.getEdge(actorOrMovie1, actorOrMovie2).from();
    std::string vertexEnd = graph.getEdge(actorOrMovie1, actorOrMovie2).to();
    if (vertexStart == actorOrMovie1 && vertexEnd == actorOrMovie2) {
      isEdge = true;
    }
  }
  return isEdge;
}

std::string ImdbGraph::getEdgeColor(string actorOrMovie1,
                                    string actorOrMovie2) {
  unordered_map<string, Element<string> *> *vertices = graph.getVertices();
  std::string edgeColor;
  bool vertexOneExist = (vertices->find(actorOrMovie1) != vertices->end());
  bool vertexTwoExist = (vertices->find(actorOrMovie2) != vertices->end());

  if (vertexOneExist && vertexTwoExist) {
    edgeColor =
        graph.getEdge(actorOrMovie1, actorOrMovie2).getColor().getHexValue();
  } else {
    edgeColor = "NA";
  }
  return edgeColor;
}

bool ImdbGraph::checkDefaultVisualization(GraphAdjList<string> *graph) {
  std::string color, edgeColor;
  for (auto &vertex : *graph->getVertices()) {
    color = graph->getVisualizer(vertex.first)->getColor().getHexValue();
    if (color != "#0000007f") {
      return false;
    }
    // get adjacency list of vertex
    auto sl_list = graph->getAdjacencyList(vertex.first);
    for (auto sle = sl_list; sle != NULL; sle = sle->getNext()) {
      // get destination vertex
      auto destination = ((Edge<string>)sle->getValue()).to();
      edgeColor =
          graph->getEdge(vertex.first, destination).getColor().getHexValue();
      if (edgeColor != "#87cefaff") {
        return false;
      }
    }
  }
  return true;
}