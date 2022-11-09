/*************************************************************************
 *
 * Project 1: IMDB Actor and Movie Linked List
 *
 * File Name: ImdbDriver.cpp
 * Course:    CPTR 242
 * Date:      May 14, 2021
 */
#include "ImdbGraphMenu.h"
#include "Array.h"
#include "Bridges.h"
#include "BridgesUser.h"
#include "DataSource.h"
#include "ImdbGraph.h"
#include "SLelement.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

void ImdbGraphMenu(std::istream &inStream, std::ostream &outStream,
                   std::string outputLabel) {
  // Used for test driver functionality.
  std::string option;

  // Used to interact with Actor/Movie graph.
  std::string vertex;
  std::string vertex2;
  std::string vertexColor, edgeColor;

  ImdbGraph imdbGraph;
  bool found; // For use with GetActor
  int numOptions;

  outStream << outputLabel << std::endl;
  inStream >> option;

  // create the Bridges object, set credentials
  BridgesUser bUser;
  Bridges bridges(bUser.getBridgesNumber(), bUser.getBridgesUserID(),
                  bUser.getBridgesAPIKey());

  bridges.setTitle("List with IMDB Actor/Movie Data");
  bridges.setDescription("Here the data is processed to be a graph of actors "
                         "with all movies they have been in.");

  // get the actor movie IMDB data
  DataSource ds(&bridges);
  vector<ActorMovieIMDB> am_imdb = ds.getActorMovieIMDBData();

  // Test driver menu and options
  numOptions = 0;
  while (option != "Quit") {
    std::cout << option;
    if (option == "Menu") {
      outStream << "Select options" << std::endl;
      outStream << "AddVertex <actorOrMovie>. Add Vertex to the graph."
                << std::endl;
      outStream << "AddActor <actorOrMovie>. Add Actor to the graph."
                << std::endl;
      outStream
          << "AddEdge <actorOrMovie> <actorOrMovie>. Add edge to the graph."
          << std::endl;
      outStream
          << "GetBaconNumber <actor1> <actor2>. Calculates the Bacon Number."
          << std::endl;
      outStream << "setVertexColor <actorOrMovie> <color>. Change the color "
                   "of the vertex."
                << std::endl;
      outStream << "setEdgeColor <actorOrMovie> <actorOrMovie> <color>. "
                   "Change the color of the edge."
                << std::endl;
      outStream << "ResetVisualizer. Reset the visualization of all edges and "
                   "vertices."
                << std::endl;
      outStream
          << "Visualize. Builds the bridges visualization and prints the URL."
          << std::endl;
      outStream << "AddAll. Adds all actors and movies to the graph."
                << std::endl;
      outStream << "doesVertexExist <actorOrMovie>. Returns a boolean if "
                   "Vertex exist in graph."
                << std::endl;
      outStream << "getVertexColor <actorOrMovie>. Returns vertex Color in "
                   "hexadecimal."
                << std::endl;
      outStream << "doesEdgeExist <actorOrMovie> <actorOrMovie>. Returns a "
                   "boolean if "
                   "edge exist betweem two vertexs in graph."
                << std::endl;
      outStream << "getEdgeColor <actorOrMovie> <actorOrMovie>. Returns edge "
                   "Color in "
                   "hexadecimal."
                << std::endl;
      outStream << "checkDefaultVisualization. Returns a boolean if nodes in "
                   "graph are resetted to default values"
                << std::endl;
      outStream << "Print. Prints" << std::endl;
      outStream << "Quit. Quit application." << std::endl;
      outStream << "Menu. Display menu." << std::endl;
    } else if (option == "AddVertex") {
      inStream >> vertex;
      imdbGraph.AddVertex(vertex);
    } else if (option == "doesVertexExist") {
      inStream >> vertex;
      found = imdbGraph.doesVertexExist(vertex);
      if (found) {
        outStream << "\tVertex {" << vertex << "} exist in graph" << std::endl;
      } else {
        outStream << "\tVertex {" << vertex << "} does not exist in graph"
                  << std::endl;
      }
    } else if (option == "AddEdge") {
      inStream >> vertex;
      inStream >> vertex2;
      imdbGraph.AddEdge(vertex, vertex2);
    } else if (option == "doesEdgeExist") {
      inStream >> vertex;
      inStream >> vertex2;
      found = imdbGraph.doesEdgeExist(vertex, vertex2);
      if (found) {
        outStream << "\tEdge from {" << vertex << "} to {" << vertex2
                  << "} has been corretly added to the graph" << std::endl;
      } else {
        outStream << "\tCould not create Edge from {" << vertex << "} to {"
                  << vertex2 << "}" << std::endl;
      }
    } else if (option == "GetBaconNumber") {
      inStream >> vertex;
      inStream >> vertex2;
      int baconNumber = imdbGraph.GetBaconNumber(vertex, vertex2);
      outStream << vertex << " and " << vertex2 << " have a Bacon Number of "
                << baconNumber << "." << std::endl;
    } else if (option == "setVertexColor") {
      inStream >> vertex;
      inStream >> vertexColor;
      imdbGraph.setVertexColor(vertex, vertexColor);
    } else if (option == "getVertexColor") {
      inStream >> vertex;
      vertexColor = imdbGraph.getVertexColor(vertex);
      outStream << "Vertex {" << vertex << "} has a color {" << vertexColor
                << "}" << std::endl;
    } else if (option == "setEdgeColor") {
      inStream >> vertex;
      inStream >> vertex2;
      inStream >> edgeColor;
      imdbGraph.setEdgeColor(vertex, vertex2, edgeColor);
    } else if (option == "getEdgeColor") {
      inStream >> vertex;
      inStream >> vertex2;
      edgeColor = imdbGraph.getEdgeColor(vertex, vertex2);
      outStream << "Vertex1: {" << vertex << "} & Vertex2: {" << vertex2
                << "} has an edge color of {" << edgeColor << "}" << std::endl;
    } else if (option == "ResetVisualizer") {
      imdbGraph.ResetVisualizer();
    } else if (option == "checkDefaultVisualization") {
      found = imdbGraph.checkDefaultVisualization(imdbGraph.GetGraph());
      if (found) {
        outStream << "Graph has been correctly resetted to default settings"
                  << std::endl;
      } else {
        outStream << "Graph has not been correctly resetted to default settings"
                  << std::endl;
      }
    } else if (option == "Visualize") {
      // TODO remove after server has been fixed.
      bridges.setServer("clone");

      GraphAdjList<string> *graph = imdbGraph.GetGraph();
      bridges.setDataStructure(graph);
      bridges.visualize();
      outStream << "Graph was visualized." << std::endl;
    } else if (option == "AddActor") {
      int movie_count = 0;
      inStream >> vertex;
      for (auto im : am_imdb) {
        string actor = im.getActor();
        if (actor.compare(vertex) == 0) {
          string movie = im.getMovie();
          imdbGraph.AddVertex(actor);
          imdbGraph.AddVertex(movie);
          imdbGraph.AddEdge(actor, movie);
          movie_count++;
        }
      }
      if (movie_count > 0) {
        outStream << "Actor " << vertex << " was found and " << movie_count
                  << " movies have been added." << std::endl;
      } else {
        outStream << "Actor " << vertex << " was NOT found." << std::endl;
      }
    } else if (option == "AddAll") {
      for (auto im : am_imdb) {
        string actor = im.getActor();
        string movie = im.getMovie();
        imdbGraph.AddVertex(actor);
        imdbGraph.AddVertex(movie);
        imdbGraph.AddEdge(actor, movie);
      }
      outStream << "All actors and movies have been added." << std::endl;
    } else {
      std::cout << option << " is not a valid command." << std::endl;
    }
    numOptions++;
    std::cout << " Command number " << numOptions << " completed." << std::endl;
    inStream >> option;
  };
  outStream << "Test Complete." << std::endl;
  std::cout << "Quit" << std::endl << "Testing completed." << std::endl;
}
