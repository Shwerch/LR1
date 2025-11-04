#include "array.h"

#include <iostream>
#include <fstream>
#include <cstring>

void Array::init() {
    capacity = 10;
    size = 0;
    data = new int[capacity];
}

void Array::resize() {
    capacity *= 2;
    int* newData = new int[capacity];
    for (size_t i = 0; i < size; i++) {
        newData[i] = data[i];
    }
    delete[] data;
    data = newData;
}

void Array::push(int value) {
    if (size >= capacity) {
        resize();
    }
    data[size++] = value;
}

void Array::del(size_t index) {
    if (index >= size) return;
    for (size_t i = index; i < size - 1; i++) {
        data[i] = data[i + 1];
    }
    size--;
}

int Array::get(size_t index) const {
    if (index >= size) return -1;
    return data[index];
}

void Array::print() const {
    std::cout << "Array (size=" << size << "): ";
    for (size_t i = 0; i < size; i++) {
        std::cout << data[i] << " ";
    }
    std::cout << std::endl;
}

void Array::save(const char* filename) const {
    std::ofstream file(filename);
    file << "ARRAY\n" << size << "\n";
    for (size_t i = 0; i < size; i++) {
        file << data[i] << "\n";
    }
}

void Array::load(const char* filename) {
    std::ifstream file(filename);
    if (!file) return;
    
    char type[20];
    file >> type;
    if (strcmp(type, "ARRAY") != 0) return;
    
    size_t sz;
    file >> sz;
    for (size_t i = 0; i < sz; i++) {
        int value;
        file >> value;
        push(value);
    }
}

void Array::free() {
    delete[] data;
    data = nullptr;
    size = 0;
    capacity = 0;
}