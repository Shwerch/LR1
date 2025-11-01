#pragma once

#include <iosfwd>

struct TreeNode {
    int value;
    TreeNode* left;
    TreeNode* right;
};

struct Tree {
    TreeNode* root;
    size_t size;
    
    void init();
    void insert(int value);
    void del(int value);
    bool get(int value) const;
    void print() const;
    void save(const char* filename) const;
    void load(const char* filename);
    void free();
    
private:
    TreeNode* insertHelper(TreeNode* node, int value);
    TreeNode* deleteHelper(TreeNode* node, int value, bool& deleted);
    TreeNode* findMin(TreeNode* node);
    bool searchHelper(TreeNode* node, int value) const;
    void freeHelper(TreeNode* node);
    void saveHelper(std::ofstream& file, TreeNode* node) const;
    int getHeight(TreeNode* node) const;
    void printLevel(TreeNode* node, int level, int indent, int spacing) const;
};