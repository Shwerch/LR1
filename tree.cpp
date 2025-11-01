#include "tree.h"

#include <iostream>
#include <fstream>
#include <cstring>

void Tree::init() {
    root = nullptr;
    size = 0;
}

TreeNode* Tree::insertHelper(TreeNode* node, int value) {
    if (!node) {
        return new TreeNode{value, nullptr, nullptr};
    }
    
    if (value < node->value) {
        node->left = insertHelper(node->left, value);
    } else if (value > node->value) {
        node->right = insertHelper(node->right, value);
    }
    
    return node;
}

void Tree::insert(int value) {
    root = insertHelper(root, value);
    size++;
}

TreeNode* Tree::findMin(TreeNode* node) {
    while (node->left) {
        node = node->left;
    }
    return node;
}

TreeNode* Tree::deleteHelper(TreeNode* node, int value, bool& deleted) {
    if (!node) return nullptr;
    
    if (value < node->value) {
        node->left = deleteHelper(node->left, value, deleted);
    } else if (value > node->value) {
        node->right = deleteHelper(node->right, value, deleted);
    } else {
        deleted = true;
        
        if (!node->left && !node->right) {
            delete node;
            return nullptr;
        } else if (!node->left) {
            TreeNode* temp = node->right;
            delete node;
            return temp;
        } else if (!node->right) {
            TreeNode* temp = node->left;
            delete node;
            return temp;
        } else {
            TreeNode* temp = findMin(node->right);
            node->value = temp->value;
            node->right = deleteHelper(node->right, temp->value, deleted);
            deleted = false;
        }
    }
    
    return node;
}

void Tree::del(int value) {
    bool deleted = false;
    root = deleteHelper(root, value, deleted);
    if (deleted) size--;
}

bool Tree::searchHelper(TreeNode* node, int value) const {
    if (!node) return false;
    if (node->value == value) return true;
    if (value < node->value) return searchHelper(node->left, value);
    return searchHelper(node->right, value);
}

bool Tree::get(int value) const {
    return searchHelper(root, value);
}

void Tree::freeHelper(TreeNode* node) {
    if (!node) return;
    freeHelper(node->left);
    freeHelper(node->right);
    delete node;
}

void Tree::free() {
    freeHelper(root);
    root = nullptr;
    size = 0;
}

int Tree::getHeight(TreeNode* node) const {
    if (!node) return 0;
    int leftHeight = getHeight(node->left);
    int rightHeight = getHeight(node->right);
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

void Tree::printLevel(TreeNode* node, int level, int indent, int spacing) const {
    if (level == 1) {
        for (int i = 0; i < indent; i++) std::cout << " ";
        if (node) {
            std::cout << node->value;
        } else {
            std::cout << " ";
        }
        for (int i = 0; i < spacing; i++) std::cout << " ";
    } else if (level > 1) {
        printLevel(node ? node->left : nullptr, level - 1, indent, spacing);
        printLevel(node ? node->right : nullptr, level - 1, indent, spacing);
    }
}

void Tree::print() const {
    std::cout << "Tree (size=" << size << "):\n";
    if (!root) {
        std::cout << "Empty tree\n";
        return;
    }
    
    int height = getHeight(root);
    int maxWidth = (1 << height) - 1;
    
    for (int level = 1; level <= height; level++) {
        int numNodes = 1 << (level - 1);
        int spacing = (maxWidth / numNodes) - 1;
        int indent = (maxWidth - (numNodes + (numNodes - 1) * spacing)) / 2;
        
        printLevel(root, level, indent, spacing);
        std::cout << "\n";
    }
}

void Tree::saveHelper(std::ofstream& file, TreeNode* node) const {
    if (!node) return;
    file << node->value << "\n";
    saveHelper(file, node->left);
    saveHelper(file, node->right);
}

void Tree::save(const char* filename) const {
    std::ofstream file(filename);
    file << "TREE\n" << size << "\n";
    saveHelper(file, root);
}

void Tree::load(const char* filename) {
    std::ifstream file(filename);
    if (!file) return;
    
    char type[20];
    file >> type;
    if (strcmp(type, "TREE") != 0) return;
    
    size_t sz;
    file >> sz;
    for (size_t i = 0; i < sz; i++) {
        int value;
        file >> value;
        insert(value);
    }
}