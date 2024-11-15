#include <iostream>
using namespace std;

enum Color { RED, BLACK };

struct Node {
    int data;
    Color color;
    Node *left, *right, *parent;

    Node(int data) {
        this->data = data;
        left = right = parent = nullptr;
        this->color = RED;
    }
};

class RedBlackTree {
private:
    Node* root;

    void rotateLeft(Node *&root, Node *&pt) {
        Node *pt_right = pt->right;

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

    void rotateRight(Node *&root, Node *&pt) {
        Node *pt_left = pt->left;

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

    void fixViolation(Node *&root, Node *&pt) {
        Node *parent_pt = nullptr;
        Node *grand_parent_pt = nullptr;

        while ((pt != root) && (pt->color != BLACK) && (pt->parent->color == RED)) {
            parent_pt = pt->parent;
            grand_parent_pt = pt->parent->parent;

            if (parent_pt == grand_parent_pt->left) {
                Node *uncle_pt = grand_parent_pt->right;

                if (uncle_pt != nullptr && uncle_pt->color == RED) {
                    grand_parent_pt->color = RED;
                    parent_pt->color = BLACK;
                    uncle_pt->color = BLACK;
                    pt = grand_parent_pt;
                } else {
                    if (pt == parent_pt->right) {
                        rotateLeft(root, parent_pt);
                        pt = parent_pt;
                        parent_pt = pt->parent;
                    }

                    rotateRight(root, grand_parent_pt);
                    swap(parent_pt->color, grand_parent_pt->color);
                    pt = parent_pt;
                }
            } else {
                Node *uncle_pt = grand_parent_pt->left;

                if ((uncle_pt != nullptr) && (uncle_pt->color == RED)) {
                    grand_parent_pt->color = RED;
                    parent_pt->color = BLACK;
                    uncle_pt->color = BLACK;
                    pt = grand_parent_pt;
                } else {
                    if (pt == parent_pt->left) {
                        rotateRight(root, parent_pt);
                        pt = parent_pt;
                        parent_pt = pt->parent;
                    }

                    rotateLeft(root, grand_parent_pt);
                    swap(parent_pt->color, grand_parent_pt->color);
                    pt = parent_pt;
                }
            }
        }

        root->color = BLACK;
    }

    Node* findNode(Node* root, int data) {
        if (root == nullptr || root->data == data)
            return root;
        
        if (data < root->data)
            return findNode(root->left, data);
        
        return findNode(root->right, data);
    }

    void fixDeleteViolation(Node *&x) {
        Node* sibling;
        
        while (x != root && x->color == BLACK) {
            if (x == x->parent->left) {
                sibling = x->parent->right;
                
                if (sibling == nullptr) break;  // Added null check
                
                if (sibling->color == RED) {
                    sibling->color = BLACK;
                    x->parent->color = RED;
                    rotateLeft(root, x->parent);
                    sibling = x->parent->right;
                }

                if ((sibling->left == nullptr || sibling->left->color == BLACK) && 
                    (sibling->right == nullptr || sibling->right->color == BLACK)) {
                    sibling->color = RED;
                    x = x->parent;
                } else {
                    if (sibling->right == nullptr || sibling->right->color == BLACK) {
                        if (sibling->left != nullptr)
                            sibling->left->color = BLACK;
                        sibling->color = RED;
                        rotateRight(root, sibling);
                        sibling = x->parent->right;
                    }

                    sibling->color = x->parent->color;
                    x->parent->color = BLACK;
                    if (sibling->right != nullptr)
                        sibling->right->color = BLACK;
                    rotateLeft(root, x->parent);
                    x = root;
                }
            } else {
                sibling = x->parent->left;
                
                if (sibling == nullptr) break;  // Added null check
                
                if (sibling->color == RED) {
                    sibling->color = BLACK;
                    x->parent->color = RED;
                    rotateRight(root, x->parent);
                    sibling = x->parent->left;
                }

                if ((sibling->right == nullptr || sibling->right->color == BLACK) && 
                    (sibling->left == nullptr || sibling->left->color == BLACK)) {
                    sibling->color = RED;
                    x = x->parent;
                } else {
                    if (sibling->left == nullptr || sibling->left->color == BLACK) {
                        if (sibling->right != nullptr)
                            sibling->right->color = BLACK;
                        sibling->color = RED;
                        rotateLeft(root, sibling);
                        sibling = x->parent->left;
                    }

                    sibling->color = x->parent->color;
                    x->parent->color = BLACK;
                    if (sibling->left != nullptr)
                        sibling->left->color = BLACK;
                    rotateRight(root, x->parent);
                    x = root;
                }
            }
        }
        x->color = BLACK;
    }

    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current->left != nullptr)
            current = current->left;
        return current;
    }

    void transplant(Node *u, Node *v) {
        if (u->parent == nullptr)
            root = v;
        else if (u == u->parent->left)
            u->parent->left = v;
        else
            u->parent->right = v;
        if (v != nullptr)
            v->parent = u->parent;
    }

    void deleteNodeHelper(Node* node, int key) {
        Node* z = findNode(node, key);
        if (z == nullptr) return;

        Node* y = z;
        Node* x;
        Color y_original_color = y->color;

        if (z->left == nullptr) {
            x = z->right;
            transplant(z, z->right);
        }
        else if (z->right == nullptr) {
            x = z->left;
            transplant(z, z->left);
        }
        else {
            y = minValueNode(z->right);
            y_original_color = y->color;
            x = y->right;

            if (y->parent == z) {
                if (x != nullptr)
                    x->parent = y;
            }
            else {
                transplant(y, y->right);
                y->right = z->right;
                if (y->right != nullptr)
                    y->right->parent = y;
            }

            transplant(z, y);
            y->left = z->left;
            if (y->left != nullptr)
                y->left->parent = y;
            y->color = z->color;
        }

        delete z;
        if (y_original_color == BLACK && x != nullptr) {
            fixDeleteViolation(x);
        }
    }

public:
    RedBlackTree() { root = nullptr; }

    void insert(const int &data) {
        Node *pt = new Node(data);
        root = BSTInsert(root, pt);
        fixViolation(root, pt);
    }

    void deleteNode(int data) {
        deleteNodeHelper(root, data);
    }

    void inorder() { inorderHelper(root); }

private:
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

    void inorderHelper(Node *root) {
        if (root == nullptr)
            return;

        inorderHelper(root->left);
        cout << root->data << " (" << (root->color == RED ? "Red" : "Black") << ")" << endl;
        inorderHelper(root->right);
    }
};

int main() {
    RedBlackTree tree;

    tree.insert(10);
    tree.insert(18);
    tree.insert(7);
    tree.insert(15);
    tree.insert(16);
    tree.insert(30);
    tree.insert(25);
    tree.insert(40);
    tree.insert(60);
    tree.insert(2);
    tree.insert(1);
    tree.insert(70);

    cout << "Inorder traversal of the constructed tree:\n";
    tree.inorder();

    cout << "\nDeleting 18, 15, 25:\n";
    tree.deleteNode(18);
    tree.deleteNode(15);
    tree.deleteNode(25);
    
    cout << "\nInorder traversal after deletion:\n";
    tree.inorder();

    return 0;
}