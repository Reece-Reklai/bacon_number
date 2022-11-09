/*************************************************************************
 *
 * Assignment: Test driver
 *
 * File Name: ImdbListMenu.h
 * Course:    CPTR 242
 */
#include "ImdbGraph.h"
#include <fstream>
#include <string>

using namespace bridges;

//  we will use this class to keep track of the number of movies that an
// 	actor has appeared in; we will use that to color/size the nodes
struct am_obj {
  std::string movies;
  int num_movies;
};

void ImdbGraphMenu(std::istream &inStream, std::ostream &outStream,
                   std::string outputLabel);
