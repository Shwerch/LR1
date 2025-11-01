#pragma once

#include <cstddef>

struct ForwardNode {
    int value;
    ForwardNode* next;
};

struct ForwardList {
    ForwardNode* head;
    size_t size;
    
    void init();
    void push(int value);
    void del(size_t index);
    int get(size_t index) const;
    void print() const;
    void save(const char* filename) const;
    void load(const char* filename);
    void free();
};