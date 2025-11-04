#pragma once

#include <cstddef>

struct DoubleNode {
    int value;
    DoubleNode* next;
    DoubleNode* prev;
};

struct DoublyList {
    DoubleNode* head;
    DoubleNode* tail;
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