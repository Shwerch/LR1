#include "stack.h"

#include <iostream>
#include <fstream>
#include <cstring>

void Stack::init() {
    top = nullptr;
    size = 0;
}

void Stack::push(int value) {
    StackNode* node = new StackNode{value, top};
    top = node;
    size++;
}

int Stack::pop() {
    if (!top) return -1;
    StackNode* temp = top;
    int value = temp->value;
    top = top->next;
    delete temp;
    size--;
    return value;
}

int Stack::peek() const {
    if (!top) return -1;
    return top->value;
}

void Stack::print() const {
    std::cout << "Stack (size=" << size << "): ";
    StackNode* current = top;
    while (current) {
        std::cout << current->value << " ";
        current = current->next;
    }
    std::cout << std::endl;
}

void Stack::save(const char* filename) const {
    std::ofstream file(filename);
    file << "STACK\n" << size << "\n";
    StackNode* current = top;
    while (current) {
        file << current->value << "\n";
        current = current->next;
    }
}

void Stack::load(const char* filename) {
    std::ifstream file(filename);
    if (!file) return;
    
    char type[20];
    file >> type;
    if (strcmp(type, "STACK") != 0) return;
    
    size_t sz;
    file >> sz;
    int* values = new int[sz];
    for (size_t i = 0; i < sz; i++) {
        file >> values[i];
    }
    for (int i = sz - 1; i >= 0; i--) {
        push(values[i]);
    }
    delete[] values;
}

void Stack::free() {
    while (top) {
        StackNode* temp = top;
        top = top->next;
        delete temp;
    }
    size = 0;
}