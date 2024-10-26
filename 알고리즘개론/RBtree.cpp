#include <iostream>
#include <ctime>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

enum Color {
  RED,
  BLACK
};

struct Node {
  int data;
  Color color;
  Node* left, * right, * parent;

  Node(int data) : data(data), left(nullptr), right(nullptr), parent(nullptr), color(RED) {}
};

class RBtree {
private:
  int leftRotations = 0;
  int rightRotations = 0;
  int insertions = 0;
  int deletions = 0;
  vector<vector<Node*>> form;
  int floor;

  Node* change_p(Node* n, Node* p) {
    n->parent = p;
    Node* out = nullptr;
    if (p != nullptr) {
      if (n->data > p->data) {
        if (p->right != nullptr) {
          p->right->parent = nullptr;
          out = p->right;
        }
        p->right = n;
      }
      else {
        if (p->left != nullptr) {
          p->left->parent = nullptr;
          out = p->left;
        }
        p->left = n;
      }
    }
    else {
      root = n;
    }

    return out;
  }
  Node* change_l(Node* n, Node* l) {
    n->left = l;
    Node* out = nullptr;
    if (l != nullptr) {
      if (l->parent != nullptr) {
        if (l == l->parent->left) l->parent->left = nullptr;
        else l->parent->right = nullptr;
        out = l->parent;
      }
      l->parent = n;
    }

    return out;
  }
  Node* change_r(Node* n, Node* r) {
    n->right = r;
    Node* out = nullptr;
    if (r != nullptr) {
      if (r->parent != nullptr) {
        if (r == r->parent->left) r->parent->left = nullptr;
        else r->parent->right = nullptr;
        out = r->parent;
      }
      r->parent = n;
    }

    return out;
  }

  void leftRotate(Node* n) {
    Node* r = n->right;
    Node* p = n->parent;

    change_r(n, r->left);
    change_l(r, n);
    change_p(r, p);

    leftRotations++;
  }
  void rightRotate(Node* n) {
    Node* l = n->left;
    Node* p = n->parent;

    change_l(n, l->right);
    change_r(l, n);
    change_p(l, p);

    rightRotations++;
  }
  void insertFixUp(Node* n) {
    Node* p = n->parent;
    
    while (n != nullptr && n != root && p->color == RED) {
      p = n->parent;
      Node* g = p->parent;
      Node* u = nullptr;
      if (g->left == p)
        u = g->right;
      else
        u = g->left;

      if (u != nullptr && u->color == RED) {
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
  void deleteFixUp(Node* x) {
    Node* w;
    while (x != root && x->color == BLACK) {
      if (x == x->parent->left) {
        w = x->parent->right;
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
        else if (w->right->color == BLACK) {
          w->left->color = BLACK;
          w->color = RED;
          rightRotate(w);
          w = x->parent->right;
        }
        w->color = x->parent->color;
        x->parent->color = BLACK;
        w->right->color = BLACK;
        leftRotate(x->parent);
        root = x;
      }
      else {

      }
    }

  }
  
  void replace_child(Node* a, Node* b) {
    if (a->parent == nullptr)
      root = b;
    else if (a == a->parent->left)
      a->parent->left = b;
    else
      a->parent->right = b;

    if (b != nullptr) {
      b->parent = a->parent;
      b->left = a->left;
      if(a->left!=nullptr)
        a->left->parent = b;
      b->right = a->right;
      if (a->right != nullptr)
        a->right->parent = b;
    }
  }
  Node* base_insert(int k) {
    Node* n = new Node(k);
    if (root == nullptr) {
      root = n;
      return n;
    }

    if (search(k) != nullptr) return nullptr;

    Node* c = root;
    Node* p = nullptr;
    while (c != nullptr) {
      p = c;
      if (k < c->data)
        c = c->left;
      else
        c = c->right;
    }

    n->parent = p;
    if (k < p->data)
      p->left = n;
    else
      p->right = n;
    return n;
  }
  void base_delete(int k) {
    Node* z = search(k);
    Node* y = nullptr;
    Node* x = nullptr;
    if (z->left == nullptr || z->right == nullptr) {
      y = z;
    }
    else {
      Node* suc = z->right;
      while (suc->left != nullptr) suc = suc->left;
      y = suc;
    }
    if (y->left != nullptr) {
      x = y->left;
    }
    else {
      x = y->right;
    }
    x->parent = y->parent;
    if (y->parent == nullptr) {
      root = x;
    }
    else if(y==y->parent->left){
      y->parent->left = x;
    }
    else {
      y->parent->right = x;
    }
    if (y != z) {
      z->data = y->data;
    }
    if (y->color == BLACK) {
      deleteFixUp(x);
    }

  }

  void make_vector(Node* root) {
    if (!root) return;

    queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
      int size = q.size();
      vector<Node*> c;

      for (int i = 0; i < size; i++) {
        Node* temp = q.front();
        q.pop();

        c.push_back(temp);

        if (temp->left) q.push(temp->left);
        if (temp->right) q.push(temp->right);
      }

      form.push_back(c);
    }
  }

public:
  Node* root;
  Node* search(int k) {
    Node* n = root;
    while (n != nullptr && n->data != k) {
      if (k < n->data)
        n = n->left;
      else
        n = n->right;
    }
    return n;
  }
  void insert(int k) {
    Node* n = base_insert(k);
    if (n) {
      insertFixUp(n);
      insertions++;
    }
  }
  void remove(int k) {
    base_delete(k);
    deletions++;
  }
  int height(Node* root) {
    if (root == nullptr)
      return 0;
    return max(height(root->left), height(root->right)) + 1;
  }

  int getcol(int h) {
    if (h == 1)
      return 1;
    return getcol(h - 1) + getcol(h - 1) + 1;
  }

  void printTree(int** M, Color** C, Node* root, int col, int row, int height) {
    if (root == nullptr)
      return;
    M[row][col] = root->data;
    C[row][col] = root->color;
    printTree(M, C, root->left, col - pow(2, height - 2), row + 1, height - 1);
    printTree(M, C, root->right, col + pow(2, height - 2), row + 1, height - 1);
  }

  void print() {
    int h = height(root);
    int col = getcol(h);

    int** M = new int* [h];
    Color** C = new Color * [h];
    for (int i = 0; i < h; i++) {
      M[i] = new int[col]();
      C[i] = new Color[col];
    }

    printTree(M, C, root, col / 2, 0, h);

    for (int i = 0; i < h; i++) {
      for (int j = 0; j < col; j++) {
        if (M[i][j] == 0)
          cout << "   ";
        else {
          string colorIndicator = (C[i][j] == RED) ? "R" : "B";
          cout << M[i][j] << colorIndicator << " ";
        }
      }
      cout << endl;
    }

    float avglI = (float)leftRotations / insertions;
    float avgrI = (float)rightRotations / insertions;
    float avglD = deletions != 0 ? (float)leftRotations / deletions : 0;
    float avgrD = deletions != 0 ? (float)rightRotations / deletions : 0;
    cout << "avg left rotations per insertions: " << avglI << ", avg right rotations per insertions: " << avgrI << endl;
    cout << "avg left rotations per deletions: " << avglD << ", avg right rotations per deletions: " << avgrD << endl;
  }

};

int main() {
  RBtree tree;
  vector<int> values;
  srand(time(nullptr));

  while (values.size() < 10) {
    int randomNum = rand() % 50;
    if (std::find(values.begin(), values.end(), randomNum) == values.end()) {
      values.push_back(randomNum);
    }
  }

  cout << "Inserted numbers: ";
  for (int num : values) {
    tree.insert(num);
    cout << num << " ";
  }
  cout << endl;

  tree.print();

  cout << "\n17 insert: " << endl;
  if (tree.search(17) == nullptr) {
    tree.insert(17);
    tree.print();
  }
  cout << "\n22 insert: " << endl;
  if (tree.search(22) == nullptr) {
    tree.insert(22);
    tree.print();
  }
  cout << "\n2 insert: " << endl;
  if (tree.search(2) == nullptr) {
    tree.insert(2);
    tree.print();
  }
  cout << "\n38 insert: " << endl;
  if (tree.search(38) == nullptr) {
    tree.insert(38);
    tree.print();
  }
  cout << "\n16 insert: " << endl;
  if (tree.search(16) == nullptr) {
    tree.insert(16);
    tree.print();
  }

  return 0;
}