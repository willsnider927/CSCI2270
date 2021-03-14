#include "MovieTree.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

// Helper function: Create new node using provided args
MovieNode* getMovieNode(int rank, string t, int y, float r) {
    MovieNode* nn = new MovieNode;
    nn->title = t;
    nn->ranking = rank;
    nn->year = y;
    nn->rating = r;
    return nn;
}

MovieTree::MovieTree() {
  root = 0;
}

void MovieTreeDel(MovieNode* location) {
  if (!location) return;
  MovieTreeDel(location->left);
  MovieTreeDel(location->right);
  delete location;
  location = 0;
}

MovieTree::~MovieTree() {
  //write your code
  MovieTreeDel(root);
}

void _printMovieInventory(MovieNode* location) {
 if (!location) return;
 _printMovieInventory(location->left);
 cout << "Movie: " << location->title << " (" << location->rating << ")" << endl;
 _printMovieInventory(location->right);
}

void MovieTree::printMovieInventory() {
   //write your code
  if (!root) {
    cout << "Tree is Empty. Cannot print." << endl;
    return;
  }
  _printMovieInventory(root);
}

void _addMovieNode(MovieNode* &location, int ranking, string title, int year, float rating) {
  if(!location) {
    location = getMovieNode(ranking, title, year, rating);
    return;
  }
  else {
    if (title < location->title) _addMovieNode(location->left, ranking, title, year, rating);
    else _addMovieNode(location->right, ranking, title, year, rating);
  }
}

void MovieTree::addMovieNode(int ranking, string title, int year, float rating) {
  //write your code
  _addMovieNode(root, ranking, title, year, rating);
}

MovieNode* _findMovie(MovieNode* location, string title) {
  if(!location) {
    return 0;
  }
  else {
    if (title == location->title) return location;
    else if (title < location->title) return _findMovie(location->left, title);
    else return _findMovie(location->right, title);
  }
}

void MovieTree::findMovie(string title) {
  //write your code
  MovieNode* movie = _findMovie(root, title);
  if (movie) {
    cout << "Movie Info:" << endl;
    cout << "==================" << endl;
    cout << "Ranking:" << movie->ranking << endl;
    cout << "Title  :" << movie->title << endl;
    cout << "Year   :" << movie->year << endl;
    cout << "Rating :" << movie->rating << endl;
    return;
  }
  cout << "Movie not found." << endl;
}

void _queryMovies(MovieNode* location, float rating, int year) {
  if (!location) return;
  else if (location->rating >= rating && location->year > year) {
    cout << location->title << " (" << location->year << ") " << location->rating << endl;
  }
  _queryMovies(location->left, rating, year);
  _queryMovies(location->right, rating, year);
}

void MovieTree::queryMovies(float rating, int year) {
  //write your code
  if (!root) {
    cout << "Tree is Empty. Cannot query Movies." << endl;
    return;
  }
  cout << "Movies that came out after " << year << "with rating at least " << rating << ":" <<endl;
  _queryMovies(root, rating, year);
}

float _sum(MovieNode* location) {
  if (!location) return 0;
  return location->rating + _sum(location->left) + _sum(location->right);
}

int _total(MovieNode* location) {
  if (!location) return 0;
  return 1 + _total(location->right) + _total(location->left);
}

void MovieTree::averageRating() {
  //write your code
  float average = _sum(root)/(float)_total(root);
  cout << "Average Rating:" << average << endl;
}

void _printLevelNodes(MovieNode* location, int level) {
  if (location) { //if NULL, nothing happens
    _printLevelNodes(location->left, level - 1); //left first so that it prints correct order
    if (!level) { // check if at correct level
      cout << "Movie:" << location->title << " (" << location->rating << ")" << endl; 
    }
    _printLevelNodes(location->right, level - 1); //now do the right
  }
}

void MovieTree::printLevelNodes(int level) {
  //write your code
  _printLevelNodes(root, level);
}
