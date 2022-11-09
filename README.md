# CPTR 242: Project -- Graphs

## Problem Overview

This project will use the BRIDGES API with an actor/movie dataset from IMDB.
You be building a graph using BRIDGES elements, which will enable you to visualize the network of connections between actors and movies.
Note that the BRIDGES visualization will also be a means to debug your program, as it will let you view your data structure and its contents after each operation.
The actor/movie dataset has been curated from IMDB as a text file containing a set of actor/movie pairs, one pair per line.

The driver will be managing the actors and movies details so you can focus on operations related to the graph.

The primary function you will be writing is to determine the Bacon Number.
The concept is a game created to demonstrate _six degrees of separation_ as it plays out for actors.
The goal is to link any actor to Kevin Bacon through other actors and the movies they were in.
Each actor counts as one degree and the complete process should be six or less.

## Learning Objectives

* Understanding of a adjancey list graph structure
* Able to read C++ library documentation
* Able to create complete tests
* Visualize the data structure using the BRIDGES API


## Resources

* Bacon Number: <https://en.wikipedia.org/wiki/Six_Degrees_of_Kevin_Bacon>
* Six degrees of separation: <https://en.wikipedia.org/wiki/Six_degrees_of_separation>
* Bridges Site: <http://bridgesuncc.github.io/>
  * Getting Started: <http://bridgesuncc.github.io/bridges_setup.html>
  * API Documentation: <http://bridgesuncc.github.io/doc/cxx-api/current/html/index.html>

## Solution Specifications

Your solution to this problem must meet the following criteria.

1. Implement __AddVertex__, __AddEdge__, __VisualizeVertex__, __VisualizeEdge__, __ResetVisualizer__, and __GetBaconNumber__ for the adjacency graph implementation in _ImdbGraph.cpp_.
    A class header and function stubs has been given to you.
    Please read the header file for detailed description of the functions.
2. Submitty will be used grade through automated all tests.

## Test Driver

The project continues to follow the testing structure from prior homework.
The Submitty tests are based on this test driver.
Here is a sample set of input to get you started.

```txt
AddVertex Cary_Grant
AddVertex Denzel_Washington
Visualize
AddActor Billy_Bob_Thornton
AddActor Adam_Sandler_(I)
AddActor Bill_Murray_(I)
AddActor Kevin_Bacon_(I)
Visualize
setVertexColor Billy_Bob_Thornton red
setVertexColor Adam_Sandler_(I) yellow
setVertexColor Bill_Murray_(I) yellow
setVertexColor Kevin_Bacon_(I) green
setVertexColor Going_Overboard_(1989) yellow
setEdgeColor Billy_Bob_Thornton Going_Overboard_(1989) yellow
setEdgeColor White_Chicks SAW yellow
setEdgeColor Adam_Sandler_(I) Going_Overboard_(1989) yellow
setVertexColor Saturday_Night_Live:_Game_Show_Parodies_(1998) yellow
setEdgeColor Adam_Sandler_(I) Saturday_Night_Live:_Game_Show_Parodies_(1998) yellow
setEdgeColor Bill_Murray_(I) Saturday_Night_Live:_Game_Show_Parodies_(1998) yellow
setVertexColor Saturday_Night_Live_Christmas_(1999) yellow
setEdgeColor Adam_Sandler_(I) Saturday_Night_Live_Christmas_(1999) yellow
setEdgeColor Bill_Murray_(I) Saturday_Night_Live_Christmas_(1999) yellow
setVertexColor Wild_Things_(1998) yellow
setEdgeColor Bill_Murray_(I) Wild_Things_(1998) yellow
setEdgeColor Kevin_Bacon_(I) Wild_Things_(1998) yellow
setVertexColor She's_Having_a_Baby_(1988) yellow
setEdgeColor Bill_Murray_(I) She's_Having_a_Baby_(1988) yellow
setEdgeColor Kevin_Bacon_(I) She's_Having_a_Baby_(1988) yellow
Visualize
AddAll
Visualize
Quit
```

* Create alternate tests to cover all the test functions
* Create an user input test file to allow for consistent and repeatable testing

## Sign Up For BRIDGES

**Note -- you only need todo this once. If you completed this step on the last project, you do not need to do it again.**

Please sign up for a BRIDGES account at [Bridges Sign Up](http://bridges-cs.herokuapp.com/signup).
Once you have an account, put your username and the API Sha1 key in the `BridgesUser.h` file.

1. Sign up for (bridges](http://bridges-cs.herokuapp.com/signup)
1. Navigate to your profile.
1. Put your __User Name__ in `BridgesUser.h` file
1. Put your __API Sha1 Key__ in `BridgesUser.h` file

These steps are need to make sure you have access to the IMDB data and visualization for the project.

## Setup Local IDE

**Note -- you only need todo this once. If you completed this step on the last project, you do not need to do it again.**

Follow the [Bridges Setup Directions](http://bridgesuncc.github.io/bridges_setup.html) to configure your system.
Please install the libraries in your `student242/include` folder for the `make` file to work properly.
(If you install in another directory, the make file will need to be altered.)

A script has been created for Code.CS.
If you are using a different IDE, take a look at the website for set up details.
You can also look at supplied set up script to see the exact commands which are being used by Code.CS. 

If you are using Code.CS, do the following:

```sh
cd student242
./setup_bridges_on_linux.sh
```

## Compiling Graph Implementations

A _make_ file has been provided to help with compiling your code.
Simply run ```make``` to compile your code after the set up has been completed.
Then execute ```./ImdbGraph.out```.
These commands have been tested on c9.io and the lab computers.

```sh
make
./ImdbGraph.out
```

The build files can be cleaned up by running ```make clean```.

## Tips

1. In this project, you will get familiar with reading library documentation.
   Bridges has fairly good documentation and you will need it to figure out the available options for completing this assignment.
2. Your IDE may show red marks due to the fact that it does not know about the BRIDGES library.
   You will still be able to build and run the software, even with these marks.
   Try compiling to see if there is really an issue.
