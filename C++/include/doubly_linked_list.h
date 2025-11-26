#pragma once

#include "base.h"

#include <iostream>
#include <fstream>
#include <cstring>

template<typename T>
struct DNode {
    T value;
    DNode* next;
    DNode* prev;
    explicit DNode(const T& value) : value(value), next(nullptr), prev(nullptr) {}
};

template<typename T>
struct DoublyLinkedList final : Base {
private:
    DNode<T>* head_ = nullptr;
    DNode<T>* tail_ = nullptr;
    size_t size_ = 0;

public:
    DoublyLinkedList() = default;

    ~DoublyLinkedList() override {
        DNode<T>* current = head_;
        while (current != nullptr) {
            DNode<T>* next_node = current->next;
            delete current;
            current = next_node;
        }
    }

    DoublyLinkedList(const DoublyLinkedList& other) : Base(other) {
        if (other.head_ == nullptr) {
            return;
        }

        head_ = new DNode<T>(other.head_->value);
        DNode<T>* current_new = head_;
        DNode<T>* current_old = other.head_->next;

        while (current_old != nullptr) {
            current_new->next = new DNode<T>(current_old->value);
            current_new->next->prev = current_new;
            current_new = current_new->next;
            current_old = current_old->next;
        }

        tail_ = current_new;
        size_ = other.size_;
    }

    DoublyLinkedList(DoublyLinkedList&& other) noexcept
            : Base(std::move(other)), head_(other.head_), tail_(other.tail_), size_(other.size_)
    {
        other.head_ = nullptr;
        other.tail_ = nullptr;
        other.size_ = 0;
    }

    size_t size() const {
        return size_;
    }

    void push_before(const T& value, const T& new_value) {
        DNode<T>* current_node = head_;
        while (current_node != nullptr && current_node->value != value) {
            current_node = current_node->next;
        }
        if (current_node == nullptr) {
            throw std::runtime_error("Element not found");
        }
        DNode<T>* new_node = new DNode<T>(new_value);
        new_node->next = current_node;
        new_node->prev = current_node->prev;
        
        if (current_node->prev != nullptr) {
            current_node->prev->next = new_node;
        } else {
            head_ = new_node;
        }
        current_node->prev = new_node;
        ++size_;
    }

    void push_after(const T& value, const T& new_value) {
        DNode<T>* current_node = head_;
        while (current_node != nullptr && current_node->value != value) {
            current_node = current_node->next;
        }
        if (current_node == nullptr) {
            throw std::runtime_error("Element not found");
        }
        DNode<T>* new_node = new DNode<T>(new_value);
        new_node->prev = current_node;
        new_node->next = current_node->next;
        
        if (current_node->next != nullptr) {
            current_node->next->prev = new_node;
        } else {
            tail_ = new_node;
        }
        current_node->next = new_node;
        ++size_;
    }

    void push_head(const T& new_value) {
        DNode<T>* new_node = new DNode<T>(new_value);
        if (size_ == 0) {
            head_ = tail_ = new_node;
        } else {
            new_node->next = head_;
            head_->prev = new_node;
            head_ = new_node;
        }
        ++size_;
    }

    void push_tail(const T& new_value) {
        DNode<T>* new_node = new DNode<T>(new_value);
        if (size_ == 0) {
            head_ = tail_ = new_node;
        } else {
            new_node->prev = tail_;
            tail_->next = new_node;
            tail_ = new_node;
        }
        ++size_;
    }

    const DNode<T>* get_head() const {
        if (size_ == 0) {
            throw std::runtime_error("Cannot get head from empty list");
        }
        return head_;
    }

    const DNode<T>* get_tail() const {
        if (size_ == 0) {
            throw std::runtime_error("Cannot get tail from empty list");
        }
        return tail_;
    }

    void remove(const T& value) {
        DNode<T>* current_node = head_;
        while (current_node != nullptr && current_node->value != value) {
            current_node = current_node->next;
        }
        if (current_node == nullptr) {
            throw std::runtime_error("Element not found");
        }
        
        if (current_node->prev != nullptr) {
            current_node->prev->next = current_node->next;
        } else {
            head_ = current_node->next;
        }
        
        if (current_node->next != nullptr) {
            current_node->next->prev = current_node->prev;
        } else {
            tail_ = current_node->prev;
        }
        
        delete current_node;
        --size_;
    }

    void remove_before(const T& value) {
        if (size_ < 2 || head_->value == value) {
            throw std::runtime_error("Cannot remove element before list head or list is too small");
        }
        DNode<T>* current_node = head_;
        while (current_node != nullptr && current_node->value != value) {
            current_node = current_node->next;
        }
        if (current_node == nullptr) {
            throw std::runtime_error("Element with given value not found");
        }
        
        DNode<T>* node_to_delete = current_node->prev;
        if (node_to_delete->prev != nullptr) {
            node_to_delete->prev->next = current_node;
        } else {
            head_ = current_node;
        }
        current_node->prev = node_to_delete->prev;
        
        delete node_to_delete;
        --size_;
    }

    void remove_after(const T& value) {
        if (size_ < 2) {
            throw std::runtime_error("List is too small");
        }
        DNode<T>* current_node = head_;
        while (current_node != nullptr && current_node->value != value) {
            current_node = current_node->next;
        }
        if (current_node == nullptr) {
            throw std::runtime_error("Element with given value not found");
        }
        if (current_node->next == nullptr) {
            throw std::runtime_error("No node to delete");
        }
        
        DNode<T>* node_to_delete = current_node->next;
        current_node->next = node_to_delete->next;
        if (node_to_delete->next != nullptr) {
            node_to_delete->next->prev = current_node;
        } else {
            tail_ = current_node;
        }
        
        delete node_to_delete;
        --size_;
    }

    void remove_head() {
        if (size_ == 0) {
            throw std::runtime_error("List is too small");
        }
        DNode<T>* node_to_delete = head_;
        head_ = head_->next;
        if (head_ != nullptr) {
            head_->prev = nullptr;
        } else {
            tail_ = nullptr;
        }
        delete node_to_delete;
        --size_;
    }

    void remove_tail() {
        if (size_ == 0) {
            throw std::runtime_error("Cannot get tail from empty list");
        }
        DNode<T>* node_to_delete = tail_;
        tail_ = tail_->prev;
        if (tail_ != nullptr) {
            tail_->next = nullptr;
        } else {
            head_ = nullptr;
        }
        delete node_to_delete;
        --size_;
    }

    bool contains(const T& value) {
        DNode<T>* current_node = head_;
        while (current_node != nullptr) {
            if (current_node->value == value) {
                return true;
            }
            current_node = current_node->next;
        }
        return false;
    }

};

template<typename T>
struct DoublyLinkedListHelper final : Helper {
private:
    static DoublyLinkedList<T>* cast(Base* b) {
        auto* ptr = dynamic_cast<DoublyLinkedList<T>*>(b);
        if (!ptr) {
            throw std::runtime_error("Invalid Base type for DoublyLinkedListHelper");
        }
        return ptr;
    }

    static const DoublyLinkedList<T>* cast(const Base& b) {
        auto* ptr = dynamic_cast<const DoublyLinkedList<T>*>(&b);
        if (!ptr) {
            throw std::runtime_error("Invalid Base type for DoublyLinkedListHelper");
        }
        return ptr;
    }
public:
    void print(const Base& data) override {
        const DoublyLinkedList<T>* list = cast(data);

        std::cout << "DOUBLY_LINKED_LIST (size = " << list->size() << "):";
        for (const DNode<T>* node = list->get_head(); node != nullptr; node = node->next) {
            std::cout << " " << node->value;
        }
        std::cout << std::endl;
    }

    void save(const char* filename, const Base& data) override {
        const DoublyLinkedList<T>* list = cast(data);

        std::ofstream out(filename);
        if (!out.is_open()) {
            throw std::runtime_error("Failed to open file for saving");
        }

        out << "DOUBLY_LINKED_LIST" << std::endl;
        out << list->size() << std::endl;
        for (const DNode<T>* node = list->get_head(); node != nullptr; node = node->next) {
            out << node->value << std::endl;
        }
        out.close();
    }

    void load(const char* filename, Base* data) override {
        DoublyLinkedList<T>* list = cast(data);

        std::ifstream in(filename);
        if (!in.is_open()) {
            throw std::runtime_error("Failed to open file for loading");
        }

        char header[64];
        in.getline(header, 64);
        if ((in.fail() && !in.eof()) || std::strcmp(header, "DOUBLY_LINKED_LIST") != 0 ) {
            throw std::runtime_error("Invalid file format");
        }

        size_t n;
        if (!(in >> n)) {
            throw std::runtime_error("File ended prematurely or invalid data format during size read");
        }

        for (size_t i = 0; i < n; i++) {
            T value;
            if (!(in >> value)) {
                throw std::runtime_error("File ended prematurely or invalid data format during element read");
            }
            list->push_tail(value);
        }
    }
};