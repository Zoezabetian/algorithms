#include "Dictionary.h"

#include <iostream>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <string>

// using namespace std;

// Implementation of the Node constructor
Dictionary::Node::Node(keyType k, valType v)
    : key(k),
      val(v),
      parent(nullptr),
      left(nullptr),
      right(nullptr),
      color(RED) {}

int Dictionary::maxDepth(Node* node) {
  if (node == nil) {
    return 0;
  } else {
    int lDepth = maxDepth(node->left);
    int rDepth = maxDepth(node->right);
    if (lDepth > rDepth) {
      return (lDepth + 1);
    } else {
      return (rDepth + 1);
    }
  }
}

void Dictionary::printTree() {
  if (this->root == this->nil) {
    return;
  }
  std::cout << "Print Tree\n";

  std::queue<Node *> nodesQueue;
  nodesQueue.push(this->root);
  int maxDepth = this->maxDepth(this->root);
  int spaces = pow(2, maxDepth);

  while (!nodesQueue.empty()) {
    int nodesAtCurrentLevel = nodesQueue.size();
    spaces /= 2;
    while (nodesAtCurrentLevel > 0) {
      Node *currentNode = nodesQueue.front();
      nodesQueue.pop();
      std::string parentKey =
          (currentNode->parent != currentNode->parent->parent) ? currentNode->parent->key : "root";
      std::cout << std::string(spaces, ' ') << currentNode->key << "("
                << (currentNode->color == RED
                        ? "red"
                        : (currentNode->color == BLACK ? "blk" : "?"))
                << " - " << parentKey << ") ";

      if (currentNode->left != this->nil) {
        nodesQueue.push(currentNode->left);
      }
      if (currentNode->right != this->nil) {
        nodesQueue.push(currentNode->right);
      }
      nodesAtCurrentLevel--;
    }
    std::cout << std::endl;
  }
  std::cout << " End Tree\n";
}

// RBT Helper Functions -----------------------------------------

// LeftRotate()
void Dictionary::LeftRotate(Node* x) {
  Node* y = x->right;  // Set y.
  x->right = y->left;  // Turn y's left subtree into x's right subtree.
  if (y->left != nil) {
    y->left->parent = x;
  }
  y->parent = x->parent;  // Link x's parent to y.
  if (x->parent == nil) {
    root = y;
  } else if (x == x->parent->left) {
    x->parent->left = y;
  } else {
    x->parent->right = y;
  }
  y->left = x;  // Put x on y's left.
  x->parent = y;
}

// RightRotate()
void Dictionary::RightRotate(Node* y) {
  Node* x = y->left;
  y->left = x->right;
  if (x->right != nil) {
    x->right->parent = y;
  }
  x->parent = y->parent;
  if (y->parent == nil) {
    root = x;
  } else if (y == y->parent->right) {
    y->parent->right = x;
  } else {
    y->parent->left = x;
  }
  x->right = y;
  y->parent = x;
}

// RB_InsertFixUP()
void Dictionary::RB_InsertFixUp(Node* z) {
  while (z->parent->color == RED) {
    if (z->parent == z->parent->parent->left) {
      Node* y = z->parent->parent->right;  // Uncle of z
      if (y->color == RED) {
        // Case 1
        z->parent->color = BLACK;
        y->color = BLACK;
        z->parent->parent->color = RED;
        z = z->parent->parent;
      } else {
        if (z == z->parent->right) {
          // Case 2
          z = z->parent;
          LeftRotate(z);
        }
        // Case 3
        z->parent->color = BLACK;
        z->parent->parent->color = RED;
        RightRotate(z->parent->parent);
      }
    } else {
      // Symmetric to the above
      Node* y = z->parent->parent->left;
      if (y->color == RED) {
        z->parent->color = BLACK;
        y->color = BLACK;
        z->parent->parent->color = RED;
        z = z->parent->parent;
      } else {
        if (z == z->parent->left) {
          z = z->parent;
          RightRotate(z);
        }
        z->parent->color = BLACK;
        z->parent->parent->color = RED;
        LeftRotate(z->parent->parent);
      }
    }
  }
  root->color = BLACK;
}

// RB_Transplant()
void Dictionary::RB_Transplant(Node* u, Node* v) {
  if (u->parent == nil) {
    root = v;
  } else if (u == u->parent->left) {
    u->parent->left = v;
  } else {
    u->parent->right = v;
  }
  v->parent = u->parent;
}

//RB_Delete()
void Dictionary::RB_Delete(Node* z) {
    Node* y = z;
    Color y_orig_color = y->color;
    Node* x = nullptr; // Define x outside the conditional blocks

    if (z->left == nil) {
        x = z->right;
        RB_Transplant(z, z->right);
    } else if (z->right == nil) {
        x = z->left;
        RB_Transplant(z, z->left);
    } else {
        y = findMin(z->right);
        y_orig_color = y->color;
        x = y->right; // Define x before using it
        if (y->parent == z) x->parent = y;
        else {
            RB_Transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        RB_Transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    if (y_orig_color == BLACK) RB_DeleteFixUp(x);
}


// RB_DeleteFixUp()
void Dictionary::RB_DeleteFixUp(Node* x) {
  while (x != root && x->color == BLACK) {
    if (x == x->parent->left) {
      Node* w = x->parent->right;
      if (w->color == RED) {
        w->color = BLACK;
        x->parent->color = RED;
        LeftRotate(x->parent);
        w = x->parent->right;
      }
      if (w->left->color == BLACK && w->right->color == BLACK) {
        w->color = RED;
        x = x->parent;
      } else {
        if (w->right->color == BLACK) {
          w->left->color = BLACK;
          w->color = RED;
          RightRotate(w);
          w = x->parent->right;
        }
        w->color = x->parent->color;
        x->parent->color = BLACK;
        w->right->color = BLACK;
        LeftRotate(x->parent);
        x = root;
      }
    } else {
      // Symmetric to the above
      Node* w = x->parent->left;
      if (w->color == RED) {
        w->color = BLACK;
        x->parent->color = RED;
        RightRotate(x->parent);
        w = x->parent->left;
      }
      if (w->right->color == BLACK && w->left->color == BLACK) {
        w->color = RED;
        x = x->parent;
      } else {
        if (w->left->color == BLACK) {
          w->right->color = BLACK;
          w->color = RED;
          LeftRotate(w);
          w = x->parent->left;
        }
        w->color = x->parent->color;
        x->parent->color = BLACK;
        w->left->color = BLACK;
        RightRotate(x->parent);
        x = root;
      }
    }
  }
  x->color = BLACK;
}
// Helper Functions (Optional) ---------------------------------------------

// inOrderString()
// Appends a string representation of the tree rooted at R to string s. The
// string appended consists of: "key : value \n" for each key-value pair in
// tree R, arranged in order by keys.
void Dictionary::inOrderString(std::string &s, Node *R) const
{
    if (R != nil)
    {
        inOrderString(s, R->left);
        s += R->key + " : " + std::to_string(R->val) +
             "\n"; // Correctly append "key : value\n"
        inOrderString(s, R->right);
    }
}

// preOrderString()
// Appends a string representation of the tree rooted at R to s. The appended
// string consists of keys only, separated by "\n", with the order determined
// by a pre-order tree walk.
void Dictionary::preOrderString(std::string &s, Node *R) const
{
    if (R != nil)
    {
        std::stringstream ss_key;
        ss_key << R->key;
        s += ss_key.str() + (R->color == RED ? " (RED)\n" : "\n"); // this assignment wants the color of the node to be printed
        preOrderString(s, R->left);
        preOrderString(s, R->right);
    }
}

// preOrderCopy()
// Recursively inserts a deep copy of the subtree rooted at R into this
// Dictionary. Recursion terminates at N.
Dictionary::Node *Dictionary::preOrderCopy(Node *src)
{
    // this test is diffferent but important.
    // since the src is ona different dictionary, we don't know what its unique nil is.
    // nil is a pointer to a special node that is unique to each dictionary.
    // if we did: if (src == nil) we would be comparing to this local dictionary's nil, not src's nil
    // one thing about nil that is shared everywhere is that its left is itself, and its right is itself
    if (src->left != src)
    {
        Node *dest = new Node(src->key, src->val);
        dest->color = src->color;  // Copy the color
        dest->left = preOrderCopy(src->left);
        dest->right = preOrderCopy(src->right);

        if (dest->left != nil) {
          dest->left->parent = dest;  // Set parent of left child
        }

        if (dest->right != nil) {
          dest->right->parent = dest;  // Set parent of right child
        }
        num_pairs++;
        return dest;
    }
    else
    {
        return nil;
    }
}

// postOrderDelete()
// Deletes all Nodes in the subtree rooted at R.
void Dictionary::postOrderDelete(Node *R)
{
    if (R != nil)
    {
        if (R->left != nil)
        {
            postOrderDelete(R->left);
        }
        if (R->right != nil)
        {
            postOrderDelete(R->right);
        }
        delete R;
    }
}

// search()
// Searches the subtree rooted at R for a Node with key==k. Returns
// the address of the Node if it exists, returns nil otherwise.
Dictionary::Node *Dictionary::search(Node *R, keyType k) const
{
    while (R != nil && R->key != k)
    {
        if (k < R->key)
        {
            R = R->left; // Search in the left subtree
        }
        else
        {
            R = R->right; // Search in the right subtree
        }
    }
    return R;
}

// findMin()
// If the subtree rooted at R is not empty, returns a pointer to the
// leftmost Node in that subtree, otherwise returns nil.
Dictionary::Node *Dictionary::findMin(Node *R)
{
    while (R != nil && R->left != nil)
    {
        R = R->left;
    }
    return R;
}

// findMax()
// If the subtree rooted at R is not empty, returns a pointer to the
// rightmost Node in that subtree, otherwise returns nil.
Dictionary::Node *Dictionary::findMax(Node *R)
{
    while (R != nil && R->right != nil)
    {
        R = R->right;
    }
    return R;
}

// findNext()
// If N does not point to the rightmost Node, returns a pointer to the
// Node after N in an in-order tree walk.  If N points to the rightmost
// Node, or is nil, returns nil.
Dictionary::Node *Dictionary::findNext(Node *N) const
{
    if (N == nil || N == nullptr)
    {
        return nil;
    }

    // If N has a right subtree, the next node is the leftmost node in that
    // subtree
    if (N->right != nil)
    {
        N = N->right;
        while (N->left != nil)
        {
            N = N->left;
        }
        return N;
    }

    // If N doesn't have a right subtree, we need to go up the tree until we find
    // a parent whose left child is N Then, that parent will be the next node in
    // the in-order traversal
    Node *parent = N->parent;
    while (parent != nil && N == parent->right)
    {
        N = parent;
        parent = parent->parent;
    }
    return parent;
}

// findPrev()
// If N does not point to the leftmost Node, returns a pointer to the
// Node before N in an in-order tree walk.  If N points to the leftmost
// Node, or is nil, returns nil.
Dictionary::Node *Dictionary::findPrev(Node *N)
{
    if (N == nullptr || N == nil)
    {
        return nil;
    }

    // If N has a left subtree, the previous node is the rightmost node in that
    // subtree
    if (N->left != nil)
    {
        N = N->left;
        while (N->right != nil)
        {
            N = N->right;
        }
        return N;
    }

    // If N doesn't have a left subtree, we need to go up the tree until we find a
    // parent whose right child is N Then, that parent will be the previous node
    // in the in-order traversal
    Node *parent = N->parent;
    while (parent != nil && N == parent->left)
    {
        N = parent;
        parent = parent->parent;
    }
    return parent;
}

// Class Constructors & Destructors ----------------------------------------
// function to make a new nil node
// We were not being conistent with the nil node, 
// between copy constructor, and the empty constructor
Dictionary::Node * Dictionary::Dictionary::makeNil() {
    Node *nil = new Node(keyType(), valType());
    nil->left = nil->right = nil->parent = nil;
    nil->key = "nil";  // helps with debugging
    nil->color = BLACK;

    return nil;
}

// Creates new Dictionary in the empty state.
Dictionary::Dictionary() : num_pairs(0)
{
    nil = makeNil();
    root = nil;    // Tree is initially empty, so root points to nil
    current = nil; // Current is also initialized to nil
}

// Copy constructor.
Dictionary::Dictionary(const Dictionary &D) : num_pairs(D.num_pairs)
{

    nil = makeNil();
    root = nil;
    current = nil;

    // Set num_pairs to 0 before calling preOrderCopy becasue we already make a count in preOrderCopy
    num_pairs = 0;

    // Perform a deep copy of the Dictionary D
    if (D.root != D.nil) {
        root = preOrderCopy(D.root);
        root->color = BLACK;
        root->parent = nil;
    }
}

// Destructor
Dictionary::~Dictionary()
{
    if (root != nil)
    {
        postOrderDelete(root);
    }
    delete nil;
    root = current = nullptr;
}

// Access functions --------------------------------------------------------

// size()
// Returns the size of this Dictionary.
int Dictionary::size() const
{
    return num_pairs;
}

// contains()
// Returns true if there exists a pair such that key==k, and returns false
// otherwise.
bool Dictionary::contains(keyType k) const
{
    Node *nodeFound = search(root, k);
    return nodeFound != nil;
}

// getValue()
// Returns a reference to the value corresponding to key k.
// Pre: contains(k)
valType &Dictionary::getValue(keyType k) const
{
    if (root == nullptr || root == nil)
    {
        throw std::logic_error("Dictionary is empty");
    }

    Node *target = search(root, k);
    if (target == nullptr || target == nil)
    {
        std::stringstream ss;
        ss << "Dictionary: getValue(): key \"" << k << "\" does not exist";
        throw std::logic_error(ss.str());
    }

    return target->val;
}

// hasCurrent()
// Returns true if the current iterator is defined, and returns false
// otherwise.
bool Dictionary::hasCurrent() const
{
    return current != nil;
}

// currentKey()
// Returns the current key.
// Pre: hasCurrent()
keyType Dictionary::currentKey() const
{
    if (root == nullptr || current == nil)
    {
        throw std::logic_error("Dictionary: currentKey(): current undefined");
    }
    return current->key;
}

// currentVal()
// Returns a reference to the current value.
// Pre: hasCurrent()
valType &Dictionary::currentVal() const
{
    if (root == nullptr || current == nil)
    {
        throw std::logic_error("Dictionary: currentVal(): current undefined");
    }
    return current->val;
}

// Manipulation procedures -------------------------------------------------

// clear()
// Resets this Dictionary to the empty state, containing no pairs.
void Dictionary::clear()
{
    if (root != nil)
    {
        postOrderDelete(root);

        root = nil;
    }
    current = nil;
    num_pairs = 0;
}

// setValue()
// If a pair with key==k exists, overwrites the corresponding value with v,
// otherwise inserts the new pair (k, v).
void Dictionary::setValue(keyType k, valType v)
{
    // Start from the root and keep track of the parent node
    Node *parent = nil;
    Node *current = root;

    while (current != nil)
    {
        parent = current;
        if (k < current->key)
        {
            current = current->left;
        }
        else if (k > current->key)
        {
            current = current->right;
        }
        else
        {
            // Key exists, update value
            current->val = v;
            return;
        }
    }

    // If we reach here, key does not exist, insert new node
    Node *newNode = new Node(k, v);
    newNode->parent = parent;

    if (parent == nil)
    {
        // The tree was empty, new node becomes root
        root = newNode;
        root->color = BLACK;
        root->parent = nil;

    }
    else if (k < parent->key)
    {
        parent->left = newNode;
    }
    else
    {
        parent->right = newNode;
    }

    // Adjust tree size
    num_pairs++;

    // New node's children are NIL initially
    newNode->left = newNode->right = nil;

    RB_InsertFixUp(newNode);
}

// remove()
// Deletes the pair for which key==k. If that pair is current, then current
// becomes undefined.
// Pre: contains(k).
// void Dictionary::remove(keyType k)
// {
//     if (root == nil || root == nullptr)
//     {
//         throw std::logic_error("Dictionary is empty");
//     }

//     Node *target = search(root, k); // Find the node to be removed

//     if (target == nullptr || target == nil)
//     {
//         std::stringstream ss;
//         ss << "Dictionary: remove(): key \"" << k << "\" does not exist";
//         throw std::logic_error(ss.str());
//     }

//     // Check if the current iterator is pointing to the node being removed
//     if (current == target)
//     {
//         current = nil; // Reset the current iterator
//     }
//     // Case 1: No children
//     if (target->left == nil && target->right == nil)
//     {
//         if (target == root)
//             root = nil;
//         else if (target == target->parent->left)
//             target->parent->left = nil;
//         else
//             target->parent->right = nil;
//         Node *parent = target->parent;
//         delete target; // Free memory
//         RB_DeleteFixUp(parent);

//     }
//     // Case 2: One child
//     else if (target->left == nil || target->right == nil)
//     {
//         Node *child = (target->left != nil) ? target->left : target->right;
//         if (target == root)
//             root = child;
//         else if (target == target->parent->left)
//             target->parent->left = child;
//         else
//             target->parent->right = child;
//         child->parent = target->parent;
//         Node *parent = target->parent;
//         delete target; // Free memory
//         RB_DeleteFixUp(parent);

//     }
//     // Case 3: Two children
//     else
//     {
//         // Find the inorder successor
//         Node *successor = target->right;
//         while (successor->left != nil)
//             successor = successor->left;
//         // Copy the successor's key and value to the target
//         target->key = successor->key;
//         target->val = successor->val;
//         // Remove the successor node (it will have at most one right child)
//         if (successor == successor->parent->left)
//             successor->parent->left = successor->right;
//         else
//             successor->parent->right = successor->right;
//         if (successor->right != nil)
//             successor->right->parent = successor->parent;
//         Node *parent = successor->parent;
//         delete successor;  // Free memory
//         RB_DeleteFixUp(parent);
//     }

//     num_pairs--; // Decrement size
// }

void Dictionary::remove(keyType k)
{
    if (root == nil || root == nullptr)
    {
        throw std::logic_error("Dictionary is empty");
    }

    Node *target = search(root, k); // Find the node to be removed

    if (target == nullptr || target == nil)
    {
        std::stringstream ss;
        ss << "Dictionary: remove(): key \"" << k << "\" does not exist";
        throw std::logic_error(ss.str());
    }

    // Check if the current iterator is pointing to the node being removed
    if (current == target)
    {
        current = nil; // Reset the current iterator
    }

    RB_Delete(target); // Call RB_Delete to handle the deletion and fix-up

    num_pairs--; // Decrement size
}

// begin()
// If non-empty, places current iterator at the first (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing.
void Dictionary::begin()
{
    if (root != nullptr)
    {
        current = findMin(root);
    }
}

// end()
// If non-empty, places current iterator at the last (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing.
void Dictionary::end()
{
    if (root != nullptr)
    {
        current = findMax(root); // Assuming findMax() returns the maximum element
    }
}

// next()
// If the current iterator is not at the last pair, advances current
// to the next pair (as defined by the order operator < on keys). If
// the current iterator is at the last pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::next()
{
    if (root == nullptr || root == nil)
    {
        throw std::logic_error("Dictionary is empty");
    }
    if (current == nil)
    {
        throw std::logic_error("Dictionary: next(): current undefined");
    }
    if (current->right != nil)
    {
        // If current node has a right child, find the leftmost node in its right
        // subtree
        current = findMin(current->right);
    }
    else
    {
        // Move up the tree until we find a node whose left child is an ancestor of
        // current
        Node *parent = current->parent;
        while (parent != nil && current == parent->right)
        {
            current = parent;
            parent = parent->parent;
        }
        current = parent; // Move to the next node
    }
}

// prev()
// If the current iterator is not at the first pair, moves current to
// the previous pair (as defined by the order operator < on keys). If
// the current iterator is at the first pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::prev()
{
    if (root == nullptr || root == nil)
    {
        throw std::logic_error("Dictionary is empty");
    }
    if (current == nil)
    {
        throw std::logic_error("Dictionary: prev(): current undefined");
    }
    if (current->left != nil)
    {
        // If current node has a left child, find the rightmost node in its left
        // subtree
        current = findMax(current->left);
    }
    else
    {
        // Move up the tree until we find a node whose right child is an ancestor of
        // current
        Node *parent = current->parent;
        while (parent != nil && current == parent->left)
        {
            current = parent;
            parent = parent->parent;
        }
        current = parent; // Move to the previous node
    }
}

// Other Functions ---------------------------------------------------------

// to_string()
// Returns a string representation of this Dictionary. Consecutive (key, value)
// pairs are separated by a newline "\n" character, and the items key and value
// are separated by the sequence space-colon-space " : ". The pairs are arranged
// in order, as defined by the order operator <.
std::string Dictionary::to_string() const
{
    std::string str;
    inOrderString(str, root);
    return str;
}

// pre_string()
// Returns a string consisting of all keys in this Dictionary. Consecutive
// keys are separated by newline "\n" characters. The key order is given
// by a pre-order tree walk.
std::string Dictionary::pre_string() const
{
    std::string s;
    preOrderString(s, root);
    // Remove the last newline character if it exists
    return s;
}

bool Dictionary::equals(const Dictionary& D) const {
  if (num_pairs != D.num_pairs)
    return false;
  for (Node* node = root; node != nil; node = findNext(node)){
    Node* otherNode = D.search(root, node->key);
    if (otherNode == nil || node->val != otherNode->val)
      return false;
  }
  return true;
}
// Overloaded Operators ----------------------------------------------------

// operator<<()
// Inserts string representation of Dictionary D into stream, as defined by
// member function to_string().
std::ostream &operator<<(std::ostream &stream, Dictionary &D)
{
    stream << D.to_string(); // Insert the string representation of Dictionary D
                             // into the output stream
    return stream;
}

// operator==()
// Returns true if and only if Dictionary A equals Dictionary B, as defined
// by member function equals().
bool operator==(const Dictionary &A, const Dictionary &B)
{
    return A.equals(B); // Call the equals member function of Dictionary to check
                        // if A equals B
}

// operator=()
// Overwrites the state of this Dictionary with state of D, and returns a
// reference to this Dictionary.
Dictionary &Dictionary::operator=(const Dictionary &D)
{
    // turn the following into printf

    if (this != &D)
    {
        clear();
        // Perform a deep copy of the Dictionary D
        if (D.root != D.nil)
        {
            root = preOrderCopy(D.root);
            root->color = BLACK;
            root->parent = nil;
        }
    }
    return *this;
}
