#include "doubly_list.h"

#include <iostream>
#include <fstream>
#include <cstring>

void DoublyList::init() {
    head = nullptr;
    tail = nullptr;
    size = 0;
}

void DoublyList::push_back(int value) {
    DoubleNode* node = new DoubleNode;
    node->value = value;
    node->next = nullptr;
    node->prev = tail;
    if (tail) tail->next = node; else head = node;
    tail = node;
    ++size;
}

void DoublyList::push_front(int value) {
    DoubleNode* node = new DoubleNode;
    node->value = value;
    node->prev = nullptr;
    node->next = head;
    if (head) head->prev = node; else tail = node;
    head = node;
    ++size;
}

void DoublyList::insert_prev(int target, int value) {
    if (!head) { push_back(value); return; }
    DoubleNode* cur = head;
    while (cur) {
        if (cur->value == target) {
            DoubleNode* node = new DoubleNode;
            node->value = value;
            node->next = cur;
            node->prev = cur->prev;
            if (cur->prev) cur->prev->next = node; else head = node;
            cur->prev = node;
            ++size;
            return;
        }
        cur = cur->next;
    }
    push_back(value);
}

void DoublyList::insert_next(int target, int value) {
    DoubleNode* cur = head;
    while (cur) {
        if (cur->value == target) {
            DoubleNode* node = new DoubleNode;
            node->value = value;
            node->prev = cur;
            node->next = cur->next;
            if (cur->next) cur->next->prev = node; else tail = node;
            cur->next = node;
            ++size;
            return;
        }
        cur = cur->next;
    }
    push_back(value);
}

void DoublyList::del_first() {
    if (!head) return;
    DoubleNode* t = head;
    head = head->next;
    if (head) head->prev = nullptr; else tail = nullptr;
    delete t;
    --size;
}

void DoublyList::del_last() {
    if (!tail) return;
    DoubleNode* t = tail;
    tail = tail->prev;
    if (tail) tail->next = nullptr; else head = nullptr;
    delete t;
    --size;
}

void DoublyList::del_prev(int target) {
    if (!head) return;
    DoubleNode* cur = head;
    while (cur) {
        if (cur->value == target) {
            DoubleNode* targetNode = cur->prev;
            if (!targetNode) return;
            if (targetNode->prev) targetNode->prev->next = targetNode->next; else head = targetNode->next;
            if (targetNode->next) targetNode->next->prev = targetNode->prev; else tail = targetNode->prev;
            delete targetNode;
            --size;
            return;
        }
        cur = cur->next;
    }
}

void DoublyList::del_at(int target) {
    if (!head) return;
    DoubleNode* cur = head;
    while (cur) {
        if (cur->value == target) {
            if (cur->prev) cur->prev->next = cur->next; else head = cur->next;
            if (cur->next) cur->next->prev = cur->prev; else tail = cur->prev;
            delete cur;
            --size;
            return;
        }
        cur = cur->next;
    }
}

void DoublyList::del_next(int target) {
    DoubleNode* cur = head;
    while (cur) {
        if (cur->value == target) {
            DoubleNode* targetNode = cur->next;
            if (!targetNode) return;
            if (targetNode->next) targetNode->next->prev = cur; else tail = cur;
            cur->next = targetNode->next;
            delete targetNode;
            --size;
            return;
        }
        cur = cur->next;
    }
}

int DoublyList::get(int value) const {
    DoubleNode* cur = head;
    while (cur) {
        if (cur->value == value) return 1;
        cur = cur->next;
    }
    return 0;
}

void DoublyList::print() const {
    std::cout << "DoublyList (size=" << size << "):";
    DoubleNode* current = head;
    while (current) {
        std::cout << " " << current->value;
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
    if (std::strcmp(type, "DOUBLY") != 0) return;
    size_t sz;
    file >> sz;
    int* values = new int[sz];
    for (size_t i = 0; i < sz; ++i) file >> values[i];
    for (size_t i = 0; i < sz; ++i) push_back(values[i]);
    delete[] values;
}

void DoublyList::free() {
    while (head) {
        DoubleNode* t = head;
        head = head->next;
        delete t;
    }
    tail = nullptr;
    size = 0;
}