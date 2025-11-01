#pragma once

#include <cstddef>

struct QueueNode {
    int value;
    QueueNode* next;
};

struct Queue {
    QueueNode* front;
    QueueNode* rear;
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