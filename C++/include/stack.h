#pragma once

#include <cstddef>

struct StackNode {
    int value;
    StackNode* next;
};

struct Stack {
    StackNode* top;
    size_t size;
    
    void init();
    void push(int value);
    int pop();
    int peek() const;
    void print() const;
    void save(const char* filename) const;
    void load(const char* filename);
    void free();
};