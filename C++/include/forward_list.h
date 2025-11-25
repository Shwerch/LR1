#pragma once

#include <cstddef>

struct ForwardNode {
    int value;
    ForwardNode* next;
};

struct ForwardList {
    ForwardNode* head;
    ForwardNode* tail;
    size_t size;

    void init();
    void push_front(int value);
    void push_back(int value);
    void insert_prev(int target, int value);
    void insert_at(int target, int value);
    void insert_next(int target, int value);
    void del_first();
    void del_last();
    void del_prev(int target);
    void del_at(int target);
    void del_next(int target);
    int get(int value) const;
    void print() const;
    void save(const char* filename) const;
    void load(const char* filename);
    void free();
};