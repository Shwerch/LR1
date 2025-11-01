#include "../forward_list.h"

#include <iostream>
#include <fstream>
#include <cstring>

void ForwardList::init() {
    head = nullptr;
    size = 0;
}

void ForwardList::push(int value) {
    ForwardNode* node = new ForwardNode{value, head};
    head = node;
    size++;
}

void ForwardList::del(size_t index) {
    if (index >= size || !head) return;
    
    if (index == 0) {
        ForwardNode* temp = head;
        head = head->next;
        delete temp;
        size--;
        return;
    }
    
    ForwardNode* current = head;
    for (size_t i = 0; i < index - 1; i++) {
        current = current->next;
    }
    
    ForwardNode* temp = current->next;
    current->next = temp->next;
    delete temp;
    size--;
}

int ForwardList::get(size_t index) const {
    if (index >= size) return -1;
    ForwardNode* current = head;
    for (size_t i = 0; i < index; i++) {
        current = current->next;
    }
    return current->value;
}

void ForwardList::print() const {
    std::cout << "ForwardList (size=" << size << "): ";
    ForwardNode* current = head;
    while (current) {
        std::cout << current->value << " ";
        current = current->next;
    }
    std::cout << std::endl;
}

void ForwardList::save(const char* filename) const {
    std::ofstream file(filename);
    file << "FORWARD\n" << size << "\n";
    ForwardNode* current = head;
    while (current) {
        file << current->value << "\n";
        current = current->next;
    }
}

void ForwardList::load(const char* filename) {
    std::ifstream file(filename);
    if (!file) return;
    
    char type[20];
    file >> type;
    if (strcmp(type, "FORWARD") != 0) return;
    
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

void ForwardList::free() {
    while (head) {
        ForwardNode* temp = head;
        head = head->next;
        delete temp;
    }
    size = 0;
}