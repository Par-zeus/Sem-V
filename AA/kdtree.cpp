#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

const int k = 2; // Number of dimensions (k = 2 for 2D points)

// Structure to represent a Point in k-dimensional space
struct Point {
    vector<int> coords; // Vector to store coordinates

    Point(int x, int y) {
        coords = {x, y};
    }

    int operator[](int idx) const {
        return coords[idx];
    }

    bool operator==(const Point& other) const {
        return coords == other.coords;
    }
};

// Node structure for the K-D Tree
struct Node {
    Point point;     // Point stored at this node
    Node* left;      // Pointer to left subtree
    Node* right;     // Pointer to right subtree

    Node(Point p) : point(p), left(nullptr), right(nullptr) {}
};

// K-D Tree class
class KDTree {
private:
    Node* root;  // Root of the tree

    // Helper function to insert a new point into the K-D Tree
    Node* insertRec(Node* node, Point point, int depth) {
        // Base case: If the tree is empty, return a new node
        if (node == nullptr)
            return new Node(point);

        // Calculate current dimension (cycle through dimensions)
        int current_dim = depth % k;

        // Compare the new point with the current node on current dimension
        if (point[current_dim] < node->point[current_dim])
            node->left = insertRec(node->left, point, depth + 1);
        else
            node->right = insertRec(node->right, point, depth + 1);

        return node;
    }

    // Helper function to search for a point in the K-D Tree
    bool searchRec(Node* node, Point point, int depth) const {
        // Base case: Node is null or point is found
        if (node == nullptr)
            return false;
        if (node->point == point)
            return true;

        // Calculate current dimension
        int current_dim = depth % k;

        // Compare the point with the current node on current dimension
        if (point[current_dim] < node->point[current_dim])
            return searchRec(node->left, point, depth + 1);
        else
            return searchRec(node->right, point, depth + 1);
    }

    // Helper function to find minimum on a particular dimension
    Node* findMinRec(Node* node, int dim, int depth) const {
        if (node == nullptr)
            return nullptr;

        int current_dim = depth % k;

        // If current dimension matches, explore left subtree for min
        if (current_dim == dim) {
            if (node->left == nullptr)
                return node;
            return findMinRec(node->left, dim, depth + 1);
        }

        // Otherwise, find the minimum recursively in both subtrees
        Node* left_min = findMinRec(node->left, dim, depth + 1);
        Node* right_min = findMinRec(node->right, dim, depth + 1);

        // Return the minimum of current node, left_min, and right_min
        Node* min_node = node;
        if (left_min != nullptr && left_min->point[dim] < min_node->point[dim])
            min_node = left_min;
        if (right_min != nullptr && right_min->point[dim] < min_node->point[dim])
            min_node = right_min;

        return min_node;
    }

    // Helper function to delete a point in the K-D Tree
    Node* deleteRec(Node* node, Point point, int depth) {
        if (node == nullptr)
            return nullptr;

        int current_dim = depth % k;

        if (node->point == point) {
            // If the node to be deleted is found
            if (node->right != nullptr) {
                // Find the minimum node in the right subtree in current_dim
                Node* min_node = findMinRec(node->right, current_dim, depth + 1);
                node->point = min_node->point;
                node->right = deleteRec(node->right, min_node->point, depth + 1);
            } else if (node->left != nullptr) {
                // Find the minimum node in the left subtree in current_dim
                Node* min_node = findMinRec(node->left, current_dim, depth + 1);
                node->point = min_node->point;
                node->right = deleteRec(node->left, min_node->point, depth + 1);
                node->left = nullptr;
            } else {
                // If it's a leaf node, simply delete it
                delete node;
                return nullptr;
            }
        } else if (point[current_dim] < node->point[current_dim]) {
            // Recursively delete from left subtree
            node->left = deleteRec(node->left, point, depth + 1);
        } else {
            // Recursively delete from right subtree
            node->right = deleteRec(node->right, point, depth + 1);
        }

        return node;
    }

    // Helper function for in-order traversal
    void inorderRec(Node* node) const {
        if (node != nullptr) {
            inorderRec(node->left);
            cout << "(" << node->point[0] << ", " << node->point[1] << ") ";
            inorderRec(node->right);
        }
    }

public:
    // Constructor to initialize the K-D Tree
    KDTree() : root(nullptr) {}

    // Insert a new point
    void insert(Point point) {
        root = insertRec(root, point, 0);
    }

    // Search for a point in the K-D Tree
    bool search(Point point) const {
        return searchRec(root, point, 0);
    }

    // Find the minimum value on a given dimension
    Point findMin(int dim) const {
        Node* min_node = findMinRec(root, dim, 0);
        if (min_node == nullptr)
            throw runtime_error("Tree is empty!");
        return min_node->point;
    }

    // Delete a point
    void deletePoint(Point point) {
        root = deleteRec(root, point, 0);
    }

    // In-order traversal to print the points
    void inorder() const {
        inorderRec(root);
        cout << endl;
    }
};

// Driver code
int main() {
    KDTree tree;

    tree.insert(Point(3, 6));
    tree.insert(Point(17, 15));
    tree.insert(Point(13, 15));
    tree.insert(Point(6, 12));
    tree.insert(Point(9, 1));
    tree.insert(Point(2, 7));
    tree.insert(Point(10, 19));

    cout << "Inorder traversal of K-D Tree: ";
    tree.inorder();

    // Search for a point
    Point target(10, 19);
    if (tree.search(target))
        cout << "Point (" << target[0] << ", " << target[1] << ") found in tree.\n";
    else
        cout << "Point not found in tree.\n";

    // Find minimum on dimension 0
    Point min_dim0 = tree.findMin(0);
    cout << "Minimum point on dimension 0: (" << min_dim0[0] << ", " << min_dim0[1] << ")\n";

    // Delete a point
    tree.deletePoint(Point(6, 12));
    cout << "Inorder traversal after deleting (6, 12): ";
    tree.inorder();

    return 0;
}
