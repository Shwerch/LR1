#pragma once

#include <cstddef>

struct Tree {
    int* data;
    size_t size;
    size_t capacity;

    void init();
    void resize();
    void insert(int value);
    void del(int value);
    bool get(int value) const;
    void print() const;
    void save(const char* filename) const;
    void load(const char* filename);
    void free();
private:
    int index_of(int value) const;
    int height() const;
};