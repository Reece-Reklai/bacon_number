/*************************************************************************
 *
 * Project: ImdbGraph implementation
 *
 * File Name: ImdbGraph.cpp
 * Name:      ??
 * Course:    CPTR 242
 * Date:      ??
 *
 */
#include <iostream>
#include <queue>
#include <string>
#include <vector>

using namespace std;

#include "Bridges.h"
#include "DataSource.h"
#include "GraphAdjList.h"
#include "ImdbGraph.h"
#include "SLelement.h"
#include "data_src/ActorMovieIMDB.h"

using namespace bridges;

// Constructor
ImdbGraph::ImdbGraph() {}

// Destructor
ImdbGraph::~ImdbGraph() {}

// Function: Adds a vertex to the graph.
// Pre:  Graph has been initialized.
// Post: The actor or movie will be added as a vertex.
//          No duplicate vertics will be created.
void ImdbGraph::AddVertex(string actorOrMovie) {
  // TODO Add code here.
  auto vertices = graph.getVertices();
  // Add Vertex with its respective colors
  if (vertices->find(actorOrMovie) == vertices->end()) {
    graph.addVertex(actorOrMovie);
    graph.getVisualizer(actorOrMovie)->setColor(Color("blue"));
  }
}

// Function: Adds a edge to the graph.
// Pre:  Graph has been initialized.
//          Vertics have been already added to the graph.
// Post: The actor movie edge will be added to the graph.
//          No duplicate edges will be created.
void ImdbGraph::AddEdge(string actorOrMovie, string movieOrActor) {
  // TODO Add code here.
  // Add Edge and make it connect to each other (both direction)
  graph.addEdge(actorOrMovie, movieOrActor, "1");
  graph.addEdge(movieOrActor, actorOrMovie, "1");
  // Just coloration for the edges
  graph.getLinkVisualizer(actorOrMovie, movieOrActor)
      ->setColor(Color("yellow"));
  graph.getLinkVisualizer(movieOrActor, actorOrMovie)
      ->setColor(Color("yellow"));
}

// Function: Updates the visualization for to vertex.
// Pre:  Graph has been initialized.
//          Vertex is in the graph.
// Post: The vertex will display the new color.
void ImdbGraph::setVertexColor(string actorOrMovie, string color) {
  // TODO Add code here.
  // Set the color of teh vertext and its size and visibility
  graph.getVisualizer(actorOrMovie)->setColor(Color(color));
  graph.getVisualizer(actorOrMovie)->setSize(25);
  graph.getVisualizer(actorOrMovie)->setOpacity(1.5);
}

// Function: Updates the visualization for to edge.
// Pre:  Graph has been initialized.
//          Edge is in the graph.
// Post: The edge will display the new color.
void ImdbGraph::setEdgeColor(string actorOrMovie, string movieOrActor2,
                             string color) {
  // TODO Add code here.
  // Color to respective edges
  graph.getLinkVisualizer(actorOrMovie, movieOrActor2)->setColor(Color(color));
  graph.getLinkVisualizer(movieOrActor2, actorOrMovie)->setColor(Color(color));
  graph.getLinkVisualizer(actorOrMovie, movieOrActor2)->setThickness(5.);
  graph.getLinkVisualizer(movieOrActor2, actorOrMovie)->setThickness(5.);
}

// Function: Resets all visualizations to the default.
// Pre:  Graph has been initialized.
// Post: The vertics and edges will display the default color.
void ImdbGraph::ResetVisualizer() {
  // TODO Add code here.
  // Reset the start vertex
  for (auto &vertex : *graph.getVertices()) {
    graph.getVisualizer(vertex.first)->setColor(Color("#4682b4"));
    auto sl_list = graph.getAdjacencyList(vertex.first);
    // Reset the destination vertex
    for (auto sle = sl_list; sle != NULL; sle = sle->getNext()) {
      auto destination = ((Edge<string>)sle->getValue()).to();
      graph.getLinkVisualizer(vertex.first, destination)
          ->setColor(Color("#4682b4"));
    }
  }
}

// Function: Calculates the Bacon Number for two actors.
//           In addition to returning the number, the graph is update to
//           highlight the path.
//           https://en.wikipedia.org/wiki/Six_Degrees_of_Kevin_Bacon
// Pre:  Graph has been initialized.
//          Vertices are in the graph.
//          Edges connect the actors in the graph.
// Post: The number returned will be lowest number of actor connections used to
// connect them.w
//          The graph will visually show the path to connect the actors.
int ImdbGraph::GetBaconNumber(string sourceActor, string destinationActor) {
  // TODO Add code here.
  // This entire code was technically inspired through the graph 7 HW (BFS)
  bool found = false;
  queue<string> toCheck;
  map<string, string> parents;
  toCheck.push(sourceActor);
  int baconNumber = 0;
  // If the source actor and destination actor are actually existent
  while (!toCheck.empty()) {
    string srcActor = toCheck.front();
    toCheck.pop();
    if (srcActor == destinationActor) {
      found = true;
      break;
    }
    //  adjacent actors to the source actor
    auto adjacentlist = graph.getAdjacencyList(srcActor);
    for (auto edge = adjacentlist; edge != nullptr; edge = edge->getNext()) {
      auto dest = edge->getValue().to();
      if (parents.count(dest) == 0) {
        parents.emplace(dest, srcActor);
        toCheck.push(dest);
      }
    }
  }
  // Steps to determine bacon number if the actor is found
  if (found) {
    string currParent = destinationActor;
    setVertexColor(currParent, "#4682b4");
    while (currParent != sourceActor) {
      string parent = parents.at(currParent);
      LinkVisualizer *edge = graph.getLinkVisualizer(parent, currParent);
      setEdgeColor(parent, currParent, "#4682b4");
      setVertexColor(parent, "#4682b4");
      baconNumber++;
      currParent = parent;
    }
    setVertexColor(sourceActor, "#4682b4");
    return baconNumber / 2;
  }
  return -1;
}
