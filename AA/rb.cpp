#include <iostream>
using namespace std;

// Enum to represent node colors
enum Color { RED, BLACK };

// Node structure
struct Node {
    int data;
    Color color;  // Red or Black
    Node *left, *right, *parent;  // Pointers to left, right child and parent

    // Constructor for Node
    Node(int data) {
        this->data = data;
        left = right = parent = nullptr;
        this->color = RED;  // New nodes are always inserted as Red
    }
};

// Red-Black Tree class
class RedBlackTree {
private:
    Node* root;  // Root of the tree

    // Left rotation
    void rotateLeft(Node *&root, Node *&pt) {
        Node *pt_right = pt->right;

        // Perform the rotation
        pt->right = pt_right->left;

        if (pt->right != nullptr)
            pt->right->parent = pt;

        pt_right->parent = pt->parent;

        if (pt->parent == nullptr)
            root = pt_right;
        else if (pt == pt->parent->left)
            pt->parent->left = pt_right;
        else
            pt->parent->right = pt_right;

        pt_right->left = pt;
        pt->parent = pt_right;
    }

    // Right rotation
    void rotateRight(Node *&root, Node *&pt) {
        Node *pt_left = pt->left;

        // Perform the rotation
        pt->left = pt_left->right;

        if (pt->left != nullptr)
            pt->left->parent = pt;

        pt_left->parent = pt->parent;

        if (pt->parent == nullptr)
            root = pt_left;
        else if (pt == pt->parent->left)
            pt->parent->left = pt_left;
        else
            pt->parent->right = pt_left;

        pt_left->right = pt;
        pt->parent = pt_left;
    }

    // Fix the Red-Black Tree after insertion to maintain balance
    void fixInsertion(Node *&root, Node *&pt) {
        Node *parent_pt = nullptr;
        Node *grand_parent_pt = nullptr;

        // Fix violation of Red-Black properties
        while ((pt != root) && (pt->color != BLACK) && (pt->parent->color == RED)) {
            parent_pt = pt->parent;
            grand_parent_pt = pt->parent->parent;

            // Case A: Parent is left child of grandparent
            if (parent_pt == grand_parent_pt->left) {
                Node *uncle_pt = grand_parent_pt->right;

                // Case 1: Uncle is RED, recolor
                if (uncle_pt != nullptr && uncle_pt->color == RED) {
                    grand_parent_pt->color = RED;
                    parent_pt->color = BLACK;
                    uncle_pt->color = BLACK;
                    pt = grand_parent_pt;
                } else {
                    // Case 2: pt is right child, rotate left
                    if (pt == parent_pt->right) {
                        rotateLeft(root, parent_pt);
                        pt = parent_pt;
                        parent_pt = pt->parent;
                    }

                    // Case 3: pt is left child, rotate right
                    rotateRight(root, grand_parent_pt);
                    swap(parent_pt->color, grand_parent_pt->color);
                    pt = parent_pt;
                }
            }
            // Case B: Parent is right child of grandparent
            else {
                Node *uncle_pt = grand_parent_pt->left;

                // Case 1: Uncle is RED, recolor
                if ((uncle_pt != nullptr) && (uncle_pt->color == RED)) {
                    grand_parent_pt->color = RED;
                    parent_pt->color = BLACK;
                    uncle_pt->color = BLACK;
                    pt = grand_parent_pt;
                } else {
                    // Case 2: pt is left child, rotate right
                    if (pt == parent_pt->left) {
                        rotateRight(root, parent_pt);
                        pt = parent_pt;
                        parent_pt = pt->parent;
                    }

                    // Case 3: pt is right child, rotate left
                    rotateLeft(root, grand_parent_pt);
                    swap(parent_pt->color, grand_parent_pt->color);
                    pt = parent_pt;
                }
            }
        }

        // Root should always be BLACK
        root->color = BLACK;
    }

    // Fix the tree after deletion to maintain Red-Black properties
    void fixDeletion(Node *&root, Node *&x) {
        while (x != root && x->color == BLACK) {
            if (x == x->parent->left) {
                Node *w = x->parent->right;

                // Case 1: Sibling is RED
                if (w->color == RED) {
                    w->color = BLACK;
                    x->parent->color = RED;
                    rotateLeft(root, x->parent);
                    w = x->parent->right;
                }

                // Case 2: Sibling's children are BLACK
                if (w->left->color == BLACK && w->right->color == BLACK) {
                    w->color = RED;
                    x = x->parent;
                } else {
                    // Case 3: Sibling's right child is BLACK
                    if (w->right->color == BLACK) {
                        w->left->color = BLACK;
                        w->color = RED;
                        rotateRight(root, w);
                        w = x->parent->right;
                    }

                    // Case 4: Sibling's right child is RED
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->right->color = BLACK;
                    rotateLeft(root, x->parent);
                    x = root;
                }
            } else {
                // Symmetric cases when x is right child
                Node *w = x->parent->left;

                if (w->color == RED) {
                    w->color = BLACK;
                    x->parent->color = RED;
                    rotateRight(root, x->parent);
                    w = x->parent->left;
                }

                if (w->right->color == BLACK && w->left->color == BLACK) {
                    w->color = RED;
                    x = x->parent;
                } else {
                    if (w->left->color == BLACK) {
                        w->right->color = BLACK;
                        w->color = RED;
                        rotateLeft(root, w);
                        w = x->parent->left;
                    }

                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->left->color = BLACK;
                    rotateRight(root, x->parent);
                    x = root;
                }
            }
        }

        x->color = BLACK;
    }

    // Transplant nodes during deletion
    void rbTransplant(Node *&u, Node *&v) {
        if (u->parent == nullptr)
            root = v;
        else if (u == u->parent->left)
            u->parent->left = v;
        else
            u->parent->right = v;

        v->parent = u->parent;
    }

    // Helper function for deletion
    void deleteNodeHelper(Node *&root, Node *&z) {
        Node *y = z;
        Node *x;
        Color y_original_color = y->color;

        if (z->left == nullptr) {
            x = z->right;
            rbTransplant(z, z->right);
        } else if (z->right == nullptr) {
            x = z->left;
            rbTransplant(z, z->left);
        } else {
            y = minimum(z->right);
            y_original_color = y->color;
            x = y->right;

            if (y->parent == z)
                x->parent = y;
            else {
                rbTransplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }

            rbTransplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }

        if (y_original_color == BLACK)
            fixDeletion(root, x);
    }

    // Find the node with the minimum value
    Node* minimum(Node* node) {
        while (node->left != nullptr)
            node = node->left;
        return node;
    }

public:
    // Constructor
    RedBlackTree() { root = nullptr; }

    // Insert a new node
    void insert(const int &data) {
        Node *pt = new Node(data);
        root = BSTInsert(root, pt);
        fixInsertion(root, pt);
    }

    // Delete a node
    void deleteNode(int data) {
        Node* z = root;
        if (root == nullptr)
            return;

        // Find the node to delete
        while (z != nullptr) {
            if (z->data == data) {
                deleteNodeHelper(root, z);
                return;
            } else if (z->data < data)
                z = z->right;
            else
                z = z->left;
        }
    }

    // In-order traversal to print node data and color
    void inorder() { inorderHelper(root); }

private:
    // Helper function to insert nodes following the BST property
    Node* BSTInsert(Node* root, Node* pt) {
        if (root == nullptr)
            return pt;

        if (pt->data < root->data) {
            root->left = BSTInsert(root->left, pt);
            root->left->parent = root;
        } else if (pt->data > root->data) {
            root->right = BSTInsert(root->right, pt);
            root->right->parent = root;
        }

        return root;
    }

    // Helper function for in-order traversal
    void inorderHelper(Node* root) {
        if (root == nullptr)
            return;

        inorderHelper(root->left);
        cout << root->data << "(" << (root->color == RED ? "Red" : "Black") << ") ";
        inorderHelper(root->right);
    }
};

// Driver code
int main() {
    RedBlackTree tree;

    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(15);
    tree.insert(25);

    cout << "Inorder traversal of the constructed tree with node colors: ";
    tree.inorder();

    tree.deleteNode(20);
    cout << "\nInorder traversal after deletion of 20: ";
    tree.inorder();

    return 0;
}
