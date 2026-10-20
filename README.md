# Binary Tree Representation and Operations

A C++17 lab assignment demonstrating how to build and examine a binary tree from a string, perform traversals, validate the tree string, calculate height and node depths, and construct a Binary Search Tree (BST).

## Given Tree

a(b(d,e),c(,f(g,)))

## Implemented Operations

1. Parse the string and build a binary tree using nodes and pointers.
2. Generate preorder traversal recursively.
3. Generate inorder traversal iteratively using a stack.
4. Generate postorder traversal iteratively using a stack.
5. Validate the tree string without building the tree.
6. Calculate the tree height and display each node's depth.
7. Build a BST from integers and display its inorder traversal.

## Expected Results

| Operation | Result |
|---|---|
| Preorder | abdecfg |
| Inorder | dbeacgf |
| Postorder | debgfca |
| Tree height | 4 levels (3 edges) |
| BST inorder | 20 30 40 50 60 70 80 |

The root node has depth 0.

## Requirements

- C++17 compatible compiler
- g++

## Compile and Run

g++ -std=c++17 -Wall -Wextra -o task1_binary_tree task1_binary_tree.cpp

./task1_binary_tree
