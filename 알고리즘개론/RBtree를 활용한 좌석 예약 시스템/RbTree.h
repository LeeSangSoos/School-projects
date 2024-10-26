#ifndef RbTREE_H
#define RbTREE_H

#include <string>
#include <memory>

using namespace std;

enum Color { RED, BLACK };

extern int IdMaker;
int getNewId();

//RbTree Node
struct Node {
  Color color;
  Node* parent;
  Node* left;
  Node* right;

  int reserve_id;
  string movie_name;
  int start_time;
  int day;
  string seat_number;
  bool isnil;

  // Constructor for regular nodes
  Node(const int movie_id, const string& movieName,
    int startTime, int dayOfWeek, const string& seatNumber)
    : reserve_id(movie_id + getNewId()), movie_name(movieName), start_time(startTime),
    day(dayOfWeek), seat_number(seatNumber),
    color(RED), isnil(false) {
    // Creating individual NIL nodes for left, right, and parent
    left = new Node();
    left->parent = this;
    right = new Node();
    right->parent = this;
    parent = new Node();
  }

  // Constructor for NIL nodes
  Node() : color(BLACK), parent(nullptr), left(nullptr), right(nullptr), isnil(true) {}
};

//RbTree functions
class RbTree {
private:
  //change color to string
  string colorToString(Color color);

  Node* change_p(Node* n, Node* p); // change parent of node n
  Node* change_l(Node* n, Node* l); // change left child of node n
  Node* change_r(Node* n, Node* r); // change right child of node n

  // Rotation
  void leftRotate(Node* n); 
  void rightRotate(Node* n);

  //Insert functions
  Node* base_insert(Node* n);
  void insertFixUp(Node* n);

  //Remove functions
  Node* findSuccessor(Node* x);
  void moveData(Node* x, Node* y);
  bool base_remove(int k);
  void removeFixUp(Node* n);

public:
  Node* root = new Node();
  Node* search(int k);
  void insert(Node* newNode);
  string remove(int k);
  void print();
};

#endif