#pragma once

#include "base.h"

#include <iostream>
#include <fstream>
#include <cstring>

template<typename T>
struct Node {
    T value;
    Node* next;
    explicit Node(const T& value) : value(value), next(nullptr) {}
};

template<typename T>
struct LinkedList final : Base {
private:
    Node<T>* head_ = nullptr;
    size_t size_ = 0;

public:
    LinkedList() = default;

    ~LinkedList() override {
        Node<T>* current = head_;
        while (current != nullptr) {
            Node<T>* next_node = current->next;
            delete current;
            current = next_node;
        }
    }

    LinkedList(const LinkedList& other) : Base(other) {
        if (other.head_ == nullptr) {
            return;
        }

        head_ = new Node<T>(other.head_->value);
        Node<T>* current_new = head_;
        Node<T>* current_old = other.head_->next;

        while (current_old != nullptr) {
            current_new->next = new Node<T>(current_old->value);
            current_new = current_new->next;
            current_old = current_old->next;
        }

        size_ = other.size_;
    }

    LinkedList(LinkedList&& other) noexcept
            : Base(std::move(other)), head_(other.head_), size_(other.size_)
    {
        other.head_ = nullptr;
        other.size_ = 0;
    }

    size_t size() const {
        return size_;
    }

    void push_before(const T& value, const T& new_value) {
        Node<T>* prev_node = nullptr;
        Node<T>* current_node = head_;
        while (current_node != nullptr && current_node->value != value) {
            prev_node = current_node;
            current_node = current_node->next;
        }
        if (current_node == nullptr) {
            throw std::runtime_error("Element not found");
        }
        Node<T>* new_node = new Node(new_value);
        if (prev_node == nullptr) {
            new_node->next = head_;
            head_ = new_node;
        } else {
            prev_node->next = new_node;
            new_node->next = current_node;
        }
        ++size_;
    }

    void push_after(const T& value, const T& new_value) {
        Node<T>* current_node = head_;
        while (current_node != nullptr && current_node->value != value) {
            current_node = current_node->next;
        }
        if (current_node == nullptr) {
            throw std::runtime_error("Element not found");
        }
        Node<T>* new_node = new Node(new_value);
        new_node->next = current_node->next;
        current_node->next = new_node;
        ++size_;
    }

    void push_head(const T& new_value) {
        Node<T>* new_node = new Node(new_value);
        if (head_ != nullptr) {
            new_node->next = head_;
        }
        head_ = new_node;
        ++size_;
    }

    void push_tail(const T& new_value) {
        Node<T>* new_node = new Node(new_value);
        if (head_ == nullptr) {
            head_ = new_node;
        } else {
            Node<T>* current_node = head_;
            while (current_node->next != nullptr) {
                current_node = current_node->next;
            }
            current_node->next = new_node;
        }
        ++size_;
    }

    const Node<T>* get_head() const {
        if (size_ == 0) {
            throw std::runtime_error("Cannot get head from empty list");
        }
        return head_;
    }

    const T& get_tail() const {
        if (size_ == 0) {
            throw std::runtime_error("Cannot get tail from empty list");
        }
        Node<T>* current_node = head_;
        while (current_node->next != nullptr) {
            current_node = current_node->next;
        }
        return current_node->value;
    }

    void remove(const T& value) {
        Node<T>* prev_node = nullptr;
        Node<T>* current_node = head_;
        while (current_node != nullptr && current_node->value != value) {
            prev_node = current_node;
            current_node = current_node->next;
        }
        if (current_node == nullptr) {
            throw std::runtime_error("Element not found");
        }
        if (prev_node == nullptr) {
            Node<T>* node_to_delete = head_;
            head_ = head_->next;
            delete node_to_delete;
        } else {
            prev_node->next = current_node->next;
            delete current_node;
        }
        --size_;
    }

    void remove_before(const T& value) {
        if (head_ == nullptr || head_->next == nullptr || head_->value == value) {
            throw std::runtime_error("Cannot remove element before list head or list is too small");
        }
        Node<T>* prev_prev_node = nullptr;
        Node<T>* prev_node = head_;
        Node<T>* current_node = head_->next;
        while (current_node != nullptr && current_node->value != value) {
            prev_prev_node = prev_node;
            prev_node = current_node;
            current_node = current_node->next;
        }
        if (current_node == nullptr) {
            throw std::runtime_error("Element with given value not found");
        }
        if (prev_prev_node == nullptr) {
            head_ = current_node;
        } else {
            prev_prev_node->next = current_node;
        }
        delete prev_node;
        --size_;
    }

    bool contains(const T& value) {
        Node<T>* current_node = head_;
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
struct LinkedListHelper final : Helper {
private:
    static LinkedList<T>* cast(Base* b) {
        auto* ptr = dynamic_cast<LinkedList<T>*>(b);
        if (!ptr) {
            throw std::runtime_error("Invalid Base type for LinkedListHelper");
        }
        return ptr;
    }

    static const LinkedList<T>* cast(const Base& b) {
        auto* ptr = dynamic_cast<const LinkedList<T>*>(&b);
        if (!ptr) {
            throw std::runtime_error("Invalid Base type for LinkedListHelper");
        }
        return ptr;
    }
public:
    void print(const Base& data) override {
        const LinkedList<T>* list = cast(data);

        std::cout << "LINKED_LIST (size = " << list->size() << "):";
        for (const Node<T>* node = list->get_head(); node != nullptr; node = node->next) {
            std::cout << " " << node->value;
        }
        std::cout << std::endl;
    }

    void save(const char* filename, const Base& data) override {
        const LinkedList<T>* list = cast(data);

        std::ofstream out(filename);
        if (!out.is_open()) {
            throw std::runtime_error("Failed to open file for saving");
        }

        out << "LINKED_LIST" << std::endl;
        out << list->size() << std::endl;
        for (const Node<T>* node = list->get_head(); node != nullptr; node = node->next) {
            out << node->value << std::endl;
        }
        out.close();
    }

    void load(const char* filename, Base* data) override {
        LinkedList<T>* list = cast(data);

        std::ifstream in(filename);
        if (!in.is_open()) {
            throw std::runtime_error("Failed to open file for loading");
        }

        char header[64];
        in.getline(header, 64);
        if ((in.fail() && !in.eof()) || std::strcmp(header, "LINKED_LIST") != 0 ) {
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