#include <algorithm>
#include <cctype>
#include <iostream>
#include <stack>
#include <string>

using namespace std;

struct Node {
    char data;
    Node* left;
    Node* right;

    Node(char value) : data(value), left(nullptr), right(nullptr) {}
};

// String ko validate karta hai; yahan koi tree node nahi banta.
bool validateSubtree(const string& text, size_t& pos) {
    if (pos >= text.size() ||
        text[pos] == '(' || text[pos] == ')' || text[pos] == ',' ||
        isspace(static_cast<unsigned char>(text[pos]))) {
        return false;
    }

    ++pos; // node label

    if (pos < text.size() && text[pos] == '(') {
        ++pos; // '('

        // Comma se pehle left child ho sakta hai.
        if (pos < text.size() && text[pos] != ',') {
            if (!validateSubtree(text, pos)) {
                return false;
            }
        }

        if (pos >= text.size() || text[pos] != ',') {
            return false;
        }
        ++pos; // ','

        // Closing parenthesis se pehle right child ho sakta hai.
        if (pos < text.size() && text[pos] != ')') {
            if (!validateSubtree(text, pos)) {
                return false;
            }
        }

        if (pos >= text.size() || text[pos] != ')') {
            return false;
        }
        ++pos; // ')'
    }

    return true;
}

bool isValidTreeString(const string& text) {
    if (text.empty()) {
        return false;
    }

    size_t pos = 0;
    return validateSubtree(text, pos) && pos == text.size();
}

// Valid string se nodes aur child pointers ke zariye tree banata hai.
Node* parseSubtree(const string& text, size_t& pos) {
    Node* node = new Node(text[pos]);
    ++pos;

    if (pos < text.size() && text[pos] == '(') {
        ++pos; // '('

        if (text[pos] != ',') {
            node->left = parseSubtree(text, pos);
        }

        ++pos; // ','

        if (text[pos] != ')') {
            node->right = parseSubtree(text, pos);
        }

        ++pos; // ')'
    }

    return node;
}

Node* buildTree(const string& text) {
    if (!isValidTreeString(text)) {
        return nullptr;
    }

    size_t pos = 0;
    return parseSubtree(text, pos);
}

void displayNodes(const Node* node, const string& position) {
    if (node == nullptr) {
        return;
    }

    cout << position << " = " << node->data
         << " | left: " << (node->left ? node->left->data : '-')
         << " | right: " << (node->right ? node->right->data : '-')
         << '\n';

    displayNodes(node->left, position + ".L");
    displayNodes(node->right, position + ".R");
}

// Recursive preorder: Root, Left, Right.
void preorderRecursive(const Node* node, string& result) {
    if (node == nullptr) {
        return;
    }

    result += node->data;
    preorderRecursive(node->left, result);
    preorderRecursive(node->right, result);
}

// Iterative inorder using a stack: Left, Root, Right.
string inorderIterative(const Node* root) {
    stack<const Node*> nodes;
    const Node* current = root;
    string result;

    while (current != nullptr || !nodes.empty()) {
        while (current != nullptr) {
            nodes.push(current);
            current = current->left;
        }

        current = nodes.top();
        nodes.pop();

        result += current->data;
        current = current->right;
    }

    return result;
}

// Iterative postorder using a stack: Left, Right, Root.
string postorderIterative(const Node* root) {
    stack<const Node*> nodes;
    const Node* current = root;
    const Node* lastVisited = nullptr;
    string result;

    while (current != nullptr || !nodes.empty()) {
        if (current != nullptr) {
            nodes.push(current);
            current = current->left;
        } else {
            const Node* topNode = nodes.top();

            if (topNode->right != nullptr && lastVisited != topNode->right) {
                current = topNode->right;
            } else {
                result += topNode->data;
                lastVisited = topNode;
                nodes.pop();
            }
        }
    }

    return result;
}

string addSpaces(const string& sequence) {
    string result;

    for (size_t i = 0; i < sequence.size(); ++i) {
        if (i > 0) {
            result += ' ';
        }
        result += sequence[i];
    }

    return result;
}

// Height is calculated here as the number of levels.
int heightInLevels(const Node* node) {
    if (node == nullptr) {
        return 0;
    }

    return 1 + max(heightInLevels(node->left),
                   heightInLevels(node->right));
}

// Recursively displays each node's depth. The root starts at depth 0.
void displayDepths(const Node* node, int depth) {
    if (node == nullptr) {
        return;
    }

    cout << node->data << " : depth " << depth << '\n';
    displayDepths(node->left, depth + 1);
    displayDepths(node->right, depth + 1);
}

void deleteTree(Node* node) {
    if (node == nullptr) {
        return;
    }

    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

// Integer BST for the sequence in Task 1, part 7.
struct BSTNode {
    int data;
    BSTNode* left;
    BSTNode* right;

    BSTNode(int value) : data(value), left(nullptr), right(nullptr) {}
}

;

BSTNode* insertBST(BSTNode* root, int value) {
    if (root == nullptr) {
        return new BSTNode(value);
    }

    if (value < root->data) {
        root->left = insertBST(root->left, value);
    } else if (value > root->data) {
        root->right = insertBST(root->right, value);
    }

    return root;
}

void inorderBST(const BSTNode* root) {
    if (root == nullptr) {
        return;
    }

    inorderBST(root->left);
    cout << root->data << ' ';
    inorderBST(root->right);
}

void deleteBST(BSTNode* root) {
    if (root == nullptr) {
        return;
    }

    deleteBST(root->left);
    deleteBST(root->right);
    delete root;
}

int main() {
    const string treeString = "a(b(d,e),c(,f(g,)))";

    cout << "1. Build a binary tree from the string\n";
    cout << "Input: " << treeString << '\n';

    Node* root = buildTree(treeString);

    if (root == nullptr) {
        cout << "The tree string is invalid.\n";
        return 1;
    }

    displayNodes(root, "root");

    cout << "\n2. Recursive preorder traversal\n";
    string preorder;
    preorderRecursive(root, preorder);
    cout << "Preorder: " << addSpaces(preorder)
         << " (string: " << preorder << ")\n";

    cout << "\n3. Iterative inorder traversal using a stack\n";
    const string inorder = inorderIterative(root);
    cout << "Inorder: " << addSpaces(inorder)
         << " (string: " << inorder << ")\n";

    cout << "\n4. Iterative postorder traversal using a stack\n";
    const string postorder = postorderIterative(root);
    cout << "Postorder: " << addSpaces(postorder)
         << " (string: " << postorder << ")\n";

    cout << "\n5. Validate strings without building trees\n";
    cout << treeString << " : "
         << (isValidTreeString(treeString) ? "Valid" : "Invalid") << '\n';
    cout << "a(b,,c) : "
         << (isValidTreeString("a(b,,c)") ? "Valid" : "Invalid") << '\n';
    cout << "a(b,c : "
         << (isValidTreeString("a(b,c") ? "Valid" : "Invalid") << '\n';

    cout << "\n6. Height and depth\n";
    const int height = heightInLevels(root);
    cout << "Height: " << height << " levels, or "
         << height - 1 << " edges\n";
    cout << "Node depths (root depth is 0):\n";
    displayDepths(root, 0);

    cout << "\n7. Build a BST from [50, 30, 70, 20, 40, 60, 80]\n";
    const int values[] = {50, 30, 70, 20, 40, 60, 80};
    BSTNode* bstRoot = nullptr;

    for (int value : values) {
        bstRoot = insertBST(bstRoot, value);
    }

    cout << "BST inorder: ";
    inorderBST(bstRoot);
    cout << '\n';

    deleteTree(root);
    deleteBST(bstRoot);
    return 0;
}
