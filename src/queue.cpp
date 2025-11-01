#include "../queue.h"

#include <iostream>
#include <fstream>
#include <cstring>

void Queue::init() {
    front = nullptr;
    rear = nullptr;
    size = 0;
}

void Queue::push(int value) {
    QueueNode* node = new QueueNode{value, nullptr};
    
    if (rear) {
        rear->next = node;
    } else {
        front = node;
    }
    
    rear = node;
    size++;
}

int Queue::pop() {
    if (!front) return -1;
    
    QueueNode* temp = front;
    int value = temp->value;
    front = front->next;
    
    if (!front) {
        rear = nullptr;
    }
    
    delete temp;
    size--;
    return value;
}

int Queue::peek() const {
    if (!front) return -1;
    return front->value;
}

void Queue::print() const {
    std::cout << "Queue (size=" << size << "): ";
    QueueNode* current = front;
    while (current) {
        std::cout << current->value << " ";
        current = current->next;
    }
    std::cout << std::endl;
}

void Queue::save(const char* filename) const {
    std::ofstream file(filename);
    file << "QUEUE\n" << size << "\n";
    QueueNode* current = front;
    while (current) {
        file << current->value << "\n";
        current = current->next;
    }
}

void Queue::load(const char* filename) {
    std::ifstream file(filename);
    if (!file) return;
    
    char type[20];
    file >> type;
    if (strcmp(type, "QUEUE") != 0) return;
    
    size_t sz;
    file >> sz;
    for (size_t i = 0; i < sz; i++) {
        int value;
        file >> value;
        push(value);
    }
}

void Queue::free() {
    while (front) {
        QueueNode* temp = front;
        front = front->next;
        delete temp;
    }
    rear = nullptr;
    size = 0;
}