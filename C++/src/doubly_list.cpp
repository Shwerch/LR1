#include "doubly_list.h"

#include <iostream>
#include <fstream>
#include <cstring>

void DoublyList::init() {
    head = nullptr;
    tail = nullptr;
    size = 0;
}

void DoublyList::push(int value) {
    DoubleNode* node = new DoubleNode{value, nullptr, tail};
    
    if (tail) {
        tail->next = node;
    } else {
        head = node;
    }
    
    tail = node;
    size++;
}

void DoublyList::del(size_t index) {
    if (index >= size) return;
    
    DoubleNode* current = head;
    for (size_t i = 0; i < index; i++) {
        current = current->next;
    }
    
    if (current->prev) {
        current->prev->next = current->next;
    } else {
        head = current->next;
    }
    
    if (current->next) {
        current->next->prev = current->prev;
    } else {
        tail = current->prev;
    }
    
    delete current;
    size--;
}

int DoublyList::get(size_t index) const {
    if (index >= size) return -1;
    DoubleNode* current = head;
    for (size_t i = 0; i < index; i++) {
        current = current->next;
    }
    return current->value;
}

void DoublyList::print() const {
    std::cout << "DoublyList (size=" << size << "): ";
    DoubleNode* current = head;
    while (current) {
        std::cout << current->value << " ";
        current = current->next;
    }
    std::cout << std::endl;
}

void DoublyList::save(const char* filename) const {
    std::ofstream file(filename);
    file << "DOUBLY\n" << size << "\n";
    DoubleNode* current = head;
    while (current) {
        file << current->value << "\n";
        current = current->next;
    }
}

void DoublyList::load(const char* filename) {
    std::ifstream file(filename);
    if (!file) return;
    
    char type[20];
    file >> type;
    if (strcmp(type, "DOUBLY") != 0) return;
    
    size_t sz;
    file >> sz;
    for (size_t i = 0; i < sz; i++) {
        int value;
        file >> value;
        push(value);
    }
}

void DoublyList::free() {
    while (head) {
        DoubleNode* temp = head;
        head = head->next;
        delete temp;
    }
    tail = nullptr;
    size = 0;
}