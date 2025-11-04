#include "forward_list.h"

#include <iostream>
#include <fstream>
#include <cstring>

void ForwardList::init() {
    head = nullptr;
    tail = nullptr;
    size = 0;
}

void ForwardList::push_front(int value) {
    ForwardNode* node = new ForwardNode;
    node->value = value;
    node->next = head;
    head = node;
    if (!tail) tail = node;
    ++size;
}

void ForwardList::push_back(int value) {
    ForwardNode* node = new ForwardNode;
    node->value = value;
    node->next = nullptr;
    if (!tail) { head = tail = node; } else { tail->next = node; tail = node; }
    ++size;
}

void ForwardList::insert_prev(int target, int value) {
    if (!head) { push_back(value); return; }
    if (head->value == target) { push_front(value); return; }
    ForwardNode* prev = head;
    ForwardNode* cur = head->next;
    while (cur) {
        if (cur->value == target) {
            ForwardNode* node = new ForwardNode;
            node->value = value;
            node->next = cur;
            prev->next = node;
            ++size;
            return;
        }
        prev = cur;
        cur = cur->next;
    }
    push_back(value);
}

void ForwardList::insert_next(int target, int value) {
    ForwardNode* cur = head;
    while (cur) {
        if (cur->value == target) {
            ForwardNode* node = new ForwardNode;
            node->value = value;
            node->next = cur->next;
            cur->next = node;
            if (!node->next) tail = node;
            ++size;
            return;
        }
        cur = cur->next;
    }
    push_back(value);
}

void ForwardList::del_first() {
    if (!head) return;
    ForwardNode* t = head;
    head = head->next;
    if (!head) tail = nullptr;
    delete t;
    --size;
}

void ForwardList::del_last() {
    if (!head) return;
    if (head == tail) { delete head; head = tail = nullptr; size = 0; return; }
    ForwardNode* cur = head;
    while (cur->next != tail) cur = cur->next;
    delete tail;
    tail = cur;
    tail->next = nullptr;
    --size;
}

void ForwardList::del_prev(int target) {
    if (!head || head->value == target) return;
    if (head->next && head->next->value == target) { del_first(); return; }
    ForwardNode* prev = head;
    ForwardNode* cur = head->next;
    while (cur) {
        if (cur->value == target) {
            ForwardNode* to = prev;
            if (to == head && head->value == target) return;
            if (to == head) {
                del_first();
                return;
            }
        }
        prev = cur;
        cur = cur->next;
    }
    prev = head;
    cur = head->next;
    while (cur) {
        if (cur->value == target) {
            ForwardNode* toDelete = prev;
            if (toDelete == head) {
                del_first();
            } else {
                ForwardNode* p = head;
                while (p->next != toDelete) p = p->next;
                p->next = toDelete->next;
                if (!p->next) tail = p;
                delete toDelete;
                --size;
            }
            return;
        }
        prev = cur;
        cur = cur->next;
    }
}

void ForwardList::del_at(int target) {
    if (!head) return;
    if (head->value == target) { del_first(); return; }
    ForwardNode* prev = head;
    ForwardNode* cur = head->next;
    while (cur) {
        if (cur->value == target) {
            prev->next = cur->next;
            if (!prev->next) tail = prev;
            delete cur;
            --size;
            return;
        }
        prev = cur;
        cur = cur->next;
    }
}

void ForwardList::del_next(int target) {
    ForwardNode* cur = head;
    while (cur) {
        if (cur->value == target) {
            ForwardNode* targetNode = cur->next;
            if (!targetNode) return;
            cur->next = targetNode->next;
            if (!cur->next) tail = cur;
            delete targetNode;
            --size;
            return;
        }
        cur = cur->next;
    }
}

int ForwardList::get(int value) const {
    ForwardNode* cur = head;
    while (cur) {
        if (cur->value == value) return 1;
        cur = cur->next;
    }
    return 0;
}

void ForwardList::print() const {
    std::cout << "ForwardList (size=" << size << "):";
    ForwardNode* cur = head;
    while (cur) {
        std::cout << " " << cur->value;
        cur = cur->next;
    }
    std::cout << std::endl;
}

void ForwardList::save(const char* filename) const {
    std::ofstream file(filename);
    file << "FORWARD\n" << size << "\n";
    ForwardNode* cur = head;
    while (cur) {
        file << cur->value << "\n";
        cur = cur->next;
    }
}

void ForwardList::load(const char* filename) {
    std::ifstream file(filename);
    if (!file) return;
    char type[20];
    file >> type;
    if (std::strcmp(type, "FORWARD") != 0) return;
    size_t sz;
    file >> sz;
    int* values = new int[sz];
    for (size_t i = 0; i < sz; ++i) file >> values[i];
    for (size_t i = 0; i < sz; ++i) push_back(values[i]);
    delete[] values;
}

void ForwardList::free() {
    while (head) {
        ForwardNode* t = head;
        head = head->next;
        delete t;
    }
    tail = nullptr;
    size = 0;
}