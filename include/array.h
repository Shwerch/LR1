#pragma once

#include <cstddef>

struct Array {
    int* data;
    size_t size;
    size_t capacity;
    
    void init();
    void resize();
    void push(int value);
    void del(size_t index);
    int get(size_t index) const;
    void print() const;
    void save(const char* filename) const;
    void load(const char* filename);
    void free();
};