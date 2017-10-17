#include <iostream>
#include "avl_tree.h"

void AVLTree::insert(const int key) {
  this->root = insert(key, this->root);

}

BinaryNode* AVLTree::insert(const int key, BinaryNode* node) {
  //normal bst insert
  if (node == NULL) {
    return new BinaryNode(key);
  }

  if(key < node->key) {
    if(node->left == NULL) {
      node->left = new BinaryNode(key); 
    } 
    else {
      node->left = insert(key, node->left);
    }
  }
  else {
    if(node->right == NULL) {
      node->right = new BinaryNode(key); 
    } 
    else {
      node->right = insert(key, node->right);
    }
  }

  //return node;
//update height
  node->height = max(getHeight(node -> left), getHeight(node -> right)) + 1;
//check balancedness 
  int bFactor = getBalance(node);

  //left cases
  if(bFactor > 1){
    if (key < node->left->key){
      return rightRotate(node); // left left
    }
    else{
      node->left = leftRotate(node->left);
      return rightRotate(node); // left right
    }
  }

  //right cases
  if(bFactor < -1){
    if (key > node->right->key){
      return leftRotate(node); // right right
    }
    else{
      node->right = rightRotate(node->right);
      return leftRotate(node); // right left
    }
  } 
  return node;
}

void AVLTree::remove(const int key) {
  this->root = remove(this->root, key);

}

BinaryNode* AVLTree::remove(BinaryNode* root, int key){
  if (root == NULL) return root;
  if (key < root->key)
     root ->left = remove(root->left, key);
  else if (key > root->key)
     root ->right = remove(root->right, key);
  else{
    if ((root->left == NULL) || (root->right == NULL)){
      BinaryNode* tmp;
      if (root->left ==NULL) tmp = root->right;
      else tmp = root->left;
      if (tmp == NULL){
	tmp = root;
	root = NULL;
      }
    else *root = *tmp;
    free(tmp);
    }
  else{
    BinaryNode* tmp = root->right;
    while (tmp -> left != NULL)
      tmp = tmp ->left;
    root -> key = tmp -> key;
    root->right = remove(root->right, tmp ->key);
    }
  }
if(root == NULL) return root;
//update height
  root->height = max(getHeight(root -> left), getHeight(root -> right)) + 1;
//check balancedness 
  int bFactor = getBalance(root);

  //left cases
  if(bFactor > 1){
    if (key < root->left->key){
      return rightRotate(root); // left left
    }
    else{
      root->left = leftRotate(root->left);
      return rightRotate(root); // left right
    }
  }

  //right cases
  if(bFactor < -1){
    if (key > root->right->key){
      return leftRotate(root); // right right
    }
    else{
      root->right = rightRotate(root->right);
      return leftRotate(root); // right left
    }
  } 
  return root;
}


 
int AVLTree::getHeight(BinaryNode* node){
  if (node == NULL) return 0;
  return node -> height;
}
int AVLTree::getBalance(BinaryNode* node){
  if (node == NULL) return 0;
  return getHeight(node -> left) - getHeight(node -> right);
}

BinaryNode* AVLTree::leftRotate(BinaryNode* root){
  BinaryNode* r = root->right;
  BinaryNode* l = r ->left;
  r->left = root;
  root->right = l;

  //update height

  root->height = max(getHeight(root -> left), getHeight(root -> right)) + 1;
  r->height = max(getHeight(r -> left), getHeight(r -> right)) + 1;



}

BinaryNode* AVLTree::rightRotate(BinaryNode* root){
  BinaryNode* l = root ->left;
  BinaryNode* r = l->right;
  l->right = root;
  root->left = r;

  //update height

  root->height = max(getHeight(root -> left), getHeight(root -> right)) + 1;
  l->height = max(getHeight(l -> left), getHeight(l -> right)) + 1;



}
void AVLTree::print(char k){
  if (k == 'p') inorder(AVLTree::root);
  if (k == 'h') inorderH(AVLTree::root);
  std::cout<<"\n";
  return;
}
void AVLTree::inorder(BinaryNode* root){
  if (root != NULL){
    inorder(root->left);
    std::cout<<root->key<<" ";
    inorder(root->right);
  }
  //std::cout<<"\n";
}

void AVLTree::inorderH(BinaryNode* root){
  if (root != NULL){
    inorder(root->left);
    std::cout<<root->height<<" ";
    inorder(root->right);
  }
  //std::cout<<"\n";
}
