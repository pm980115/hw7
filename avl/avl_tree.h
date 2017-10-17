#ifndef AVL_TREE_H
#define AVL_TREE_H

struct BinaryNode {
  BinaryNode(const int key) : key(key), left(NULL), right(NULL) {}

  ~BinaryNode() {
    delete left;
    delete right;
    left = right = NULL;
  }

  int key;
  int height;
  BinaryNode *left, *right;
};

class AVLTree {

public:
  AVLTree() : root(NULL) {}
  ~AVLTree() { 
    delete root;
  }

  void insert(const int key);
  void print(char key);
  void inorder(BinaryNode* root);
  void inorderH(BinaryNode* root);
  BinaryNode* leftRotate(BinaryNode* node);
  BinaryNode* rightRotate(BinaryNode* node);
  void remove(const int key);
  BinaryNode* remove(BinaryNode* node, int key);
  int getBalance(BinaryNode* node);
  int getHeight(BinaryNode* node);
  int max(int a, int b){
    if (a > b) return a;
    return b;
  }

private:
  BinaryNode* insert(const int key, BinaryNode* node);

  BinaryNode* root;
};

#endif
