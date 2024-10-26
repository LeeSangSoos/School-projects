#include "RbTree.h"

#include <iostream>
#include <queue>

using namespace std;

int IdMaker = 1;
int getNewId() {
  IdMaker++;  return (IdMaker * 100);
}

string RbTree::colorToString(Color color) {
  switch (color) {
  case RED: return "RED";
  case BLACK: return "BLACK";
  default: return "ERROR";
  }
}
Node* RbTree::change_p(Node* n, Node* p) {
  n->parent = p;
  Node* out = new Node();
  if (!p->isnil) {
    if (n->reserve_id > p->reserve_id) {
      if (!p->right->isnil) {
        p->right->parent ->isnil;
        out = p->right;
      }
      p->right = n;
    }
    else {
      if (!p->left->isnil) {
        p->left->parent ->isnil;
        out = p->left;
      }
      p->left = n;
    }
  }
  else {
    root = n;
  }

  //return node lossed parent
  return out;
}
Node* RbTree::change_l(Node* n, Node* l) {
  n->left = l;
  Node* out = new Node();
  if (!l->isnil) {
    if (!l->parent->isnil) {
      if (l == l->parent->left) l->parent->left ->isnil;
      else l->parent->right ->isnil;
      out = l->parent;
    }
    l->parent = n;
  }

  //return left parent
  return out;
}
Node* RbTree::change_r(Node* n, Node* r) {
  n->right = r;
  Node* out=new Node;
  if (!r->isnil) {
    if (!r->parent->isnil) {
      if (r == r->parent->left) r->parent->left ->isnil;
      else r->parent->right ->isnil;
      out = r->parent;
    }
    r->parent = n;
  }

  //return right parent
  return out;
}

void RbTree::leftRotate(Node* n) {
  Node* r = n->right;
  Node* p = n->parent;

  change_r(n, r->left);
  change_l(r, n);
  change_p(r, p);
}
void RbTree::rightRotate(Node* n) {
  Node* l = n->left;
  Node* p = n->parent;

  change_l(n, l->right);
  change_r(l, n);
  change_p(l, p);
}

Node* RbTree::base_insert(Node* n) {
  int k = n->reserve_id;
  if (root->isnil) {
    root = n;
    return n;
  }

  if (!search(k)->isnil) return new Node();

  Node* c = root;
  Node* p = new Node();
  while (!c->isnil) {
    p = c;
    if (k < c->reserve_id)
      c = c->left;
    else
      c = c->right;
  }

  n->parent = p;
  if (k < p->reserve_id)
    p->left = n;
  else
    p->right = n;
  return n;
}
void RbTree::insertFixUp(Node* n) {
  Node* p = n->parent;

  while (!n->isnil && n != root && p->color == RED) {
    p = n->parent;
    Node* g = p->parent;
    Node* u = new Node();
    if (g->left == p)
      u = g->right;
    else
      u = g->left;

    if (!u->isnil && u->color == RED) {
      p->color = BLACK;
      u->color = BLACK;
      g->color = RED;
      n = g;
      p = n->parent;
    }
    else {
      if ((n == p->left && p == g->left) || (n == p->right && p == g->right)) {
        if (n == p->left) {
          rightRotate(g);
        }
        else {
          leftRotate(g);
        }

        p->color = BLACK;
        g->color = RED;
      }
      else {
        if (n == p->right) {
          n = p;
          leftRotate(n);
        }
        else {
          n = p;
          rightRotate(n);
        }
      }
    }
  }
  root->color = BLACK;
}

Node* RbTree::findSuccessor(Node* x) {
  Node* y = new Node();
  if (!x->right->isnil) {
    y = x->right;
    while (!y->left->isnil) y = y->left;
  }
  else {
    y = x->parent;
    while (!y->isnil && x == y->right) {
      x = y;
      y = y->parent;
    }
  }

  return y;
}
void RbTree::moveData(Node* x, Node* y) {
  x->reserve_id = y->reserve_id;
  x->movie_name = y->movie_name;
  x->start_time = y->start_time;
  x->day = y->day;
  x->seat_number = y->seat_number;
}
bool RbTree::base_remove(int k) {
  
  Node* z = search(k);
  if (z->isnil) return false;
  Node* y = new Node();
  Node* x = new Node();

  if (z->left->isnil || z->right->isnil) {
    y = z;
  }
  else {
    y = findSuccessor(z);
  }

  if (!y->left->isnil) {
    x = y->left;
  }
  else {
    x = y->right;
  }

  if(!x->isnil)
    x->parent = y->parent;

  if (y->parent->isnil) {
    root = x;
  }
  else if (y == y->parent->left) {
    y->parent->left = x;
  }
  else {
    y->parent->right = x;
  }

  if (y != z) {
    moveData(z, y);
  }
  if (y->color == BLACK) {
    removeFixUp(x);
  }
  return true;
}
void RbTree::removeFixUp(Node* x) {
  while (x != root && x->color == BLACK) {
    if (x == x->parent->left) {
      Node* w = x->parent->right;
      if (w->color == RED) {
        w->color = BLACK;
        x->parent->color = RED;
        leftRotate(x->parent);
        w = x->parent->right;
      }
      if (w->left->color == BLACK && w->right->color == BLACK) {
        w->color = RED;
        x = x->parent;
      }
      else {
        if (w->right->color == BLACK) {
          w->left->color = BLACK;
          w->color = RED;
          rightRotate(w);
          w = x->parent->right;
        }
        w->color = x->parent->color;
        x->parent->color = BLACK;
        w->right->color = BLACK;
        leftRotate(x->parent);
        x = root;
      }
    }
    else {
      Node* w = x->parent->left;
      if (w->color == RED) {
        w->color = BLACK;
        x->parent->color = RED;
        rightRotate(x->parent);
        w = x->parent->left;
      }
      if (w->right->color == BLACK && w->left->color == BLACK) {
        w->color = RED;
        x = x->parent;
      }
      else {
        if (w->left->color == BLACK) {
          w->right->color = BLACK;
          w->color = RED;
          leftRotate(w);
          w = x->parent->left;
        }
        w->color = x->parent->color;
        x->parent->color = BLACK;
        w->left->color = BLACK;
        rightRotate(x->parent);
        x = root;
      }
    }
  }
  if(!x->isnil)
    x->color = BLACK;
}

Node* RbTree::search(int k) {
  Node* n = root;
  while (!n->isnil && n->reserve_id != k) {
    if (k < n->reserve_id)
      n = n->left;
    else
      n = n->right;
  }
  return n;
}
void RbTree::insert(Node* newNode) {
  Node* n = base_insert(newNode);
  if (n) {
    insertFixUp(n);
  }
}
string RbTree::remove(int k) {
  Node* n = search(k);
  if (base_remove(k)) {
    cout << "Cancelation Complete" << endl;
    return n->seat_number;
  }
  else {
    return "fail";
  }
}
void RbTree::print() {
  cout << "RbTree of reservation : " << endl;
  if (root->isnil) return;

  queue<Node*> q;
  q.push(root);
  q.push(nullptr); // Marker for end of level
  int level = 1;

  while (!q.empty()) {
    Node* current = q.front();
    q.pop();

    if (current) {
      // Print current node
      cout << "[" << current->reserve_id << " " << colorToString(current->color) << " " << level << "] ";

      // Enqueue children
      if (!current->left->isnil) q.push(current->left);
      if (!current->right->isnil) q.push(current->right);
    }
    else {
      // End of current level
      cout << endl;
      if (!q.empty()) q.push(nullptr); // Marker for next level
      level++;
    }
  }
}
