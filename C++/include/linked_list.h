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

    // Конструктор копирования
    LinkedList(const LinkedList& other) : Base(other) {

    }

    // Оператор присваивания копированием
    LinkedList& operator=(const LinkedList& other) {
        return *this;
    }

    // Конструктор перемещения
    LinkedList(LinkedList&& other) noexcept {

    }

    // Оператор присваивания перемещением
    LinkedList& operator=(LinkedList&& other) noexcept {
        return *this;
    }

    void push_before(const T& value, const T& new_value) {
        if (head_ == nullptr) {
            throw std::runtime_error("Cannot push before empty list");
        }
        Node<T>* prev_node = nullptr;
        Node<T>* current_node = head_;
        while (current_node->value != value) {
            if (current_node->next == nullptr) {
                throw std::runtime_error("Element not found");
            }
            prev_node = current_node;
            current_node = current_node->next;
        }

        Node<T>* new_node = new Node(new_value);
        if (prev_node == nullptr) {
            head_ = new_node;
            head_->next = current_node;
        } else {
            prev_node->next = new_node;
            new_node->next = current_node;
        }
    }

    void push_after(const T& value, const T& new_value) {
        if (head_ == nullptr) {
            throw std::runtime_error("Cannot push before empty list");
        }
        Node<T>* current_node = head_;
        while (current_node->value != value) {
            if (current_node->next == nullptr) {
                throw std::runtime_error("Element not found");
            }
            current_node = current_node->next;
        }

        Node<T>* new_node = new Node(new_value);
        if (current_node->next != nullptr) {
            new_node->next = current_node->next;
        }
        current_node->next = new_node;
    }

    void push_head(const T& new_value) {
        Node<T>* new_node = new Node(new_value);
        if (head_ != nullptr) {
            new_node->next = head_;
        }
        head_ = new_node;
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
    }

    T& get_head() const {
        if (head_ == nullptr) {
            throw std::runtime_error("Cannot get head from empty list");
        }
        return head_->value;
    }

    T& get_tail() const {
        if (head_ == nullptr) {
            throw std::runtime_error("Cannot get tail from empty list");
        }
        Node<T>* current_node = head_;
        while (current_node->next != nullptr) {
            current_node = current_node->next;
        }
        return current_node->value;
    }

    void remove(const T& value) {
        if (head_ == nullptr) {
            throw std::runtime_error("Cannot push before empty list");
        }
        Node<T>* prev_node = nullptr;
        Node<T>* current_node = head_;
        while (current_node->value != value) {
            if (current_node->next == nullptr) {
                throw std::runtime_error("Element not found");
            }
            prev_node = current_node;
            current_node = current_node->next;
        }
        if (prev_node == nullptr) {
            Node<T>* node_to_delete = head_;
            head_ = head_->next;
            delete node_to_delete;
        } else {
            prev_node->next = current_node->next;
            delete current_node;
        }
    }

    void remove_before(const T& value) {
        if (head_ == nullptr || head_->next == nullptr) {
            throw std::runtime_error("Cannot remove before the head");
        }
        Node<T>* prev_prev_node = nullptr;
        Node<T>* prev_node = head_;
        Node<T>* current_node = head_->next;
        if (prev_node->value == value) {
            throw std::runtime_error("Cannot remove before the head");
        }
        while (current_node->value != value) {
            if (current_node->next == nullptr) {
                throw std::runtime_error("Element with given value not found");
            }
            prev_prev_node = prev_node;
            prev_node = current_node;
            current_node = current_node->next;
        }
        if (prev_prev_node == nullptr) {
            head_ = current_node;
        } else {
            prev_prev_node->next = current_node;
        }
        delete prev_node;
    }

    bool contains(const T& value) {
        if (head_ == nullptr) {
            throw std::runtime_error("Cannot push before empty list");
        }
        Node<T>* current_node = head_;
        while (current_node->value != value) {
            if (current_node->next == nullptr) {
                return false;
            }
            current_node = current_node->next;
        }
        return true;
    }

};

template<typename T>
struct ArrayHelper final : Helper {

    static Array<T>* cast(Base* b) {
        auto* ptr = dynamic_cast<Array<T>*>(b);
        if (!ptr) {
            throw std::runtime_error("Invalid Base type for ArrayHelper");
        }
        return ptr;
    }

    static const Array<T>* cast(const Base& b) {
        auto* ptr = dynamic_cast<const Array<T>*>(&b);
        if (!ptr) {
            throw std::runtime_error("Invalid Base type for ArrayHelper");
        }
        return ptr;
    }

    void print(const Base& data) override {
        const Array<T>* arr = cast(data);

        std::cout << "ARRAY (size = " << arr->size() << "):";
        for (size_t i = 0; i < arr->size(); i++) {
            std::cout << " " << (*arr).get(i);
        }
        std::cout << std::endl;
    }

    void save(const char* filename, const Base& data) override {
        const Array<T>* arr = cast(data);

        std::ofstream out(filename);
        if (!out.is_open()) {
            throw std::runtime_error("Failed to open file for saving");
        }

        out << "ARRAY" << std::endl;
        out << arr->size() << std::endl;
        for (size_t i = 0; i < arr->size(); i++) {
            out << (*arr).get(i) << std::endl;
        }
        out.close();
    }

    void load(const char* filename, Base* data) override {
        Array<T>* arr = cast(data);

        std::ifstream in(filename);
        if (!in.is_open()) {
            throw std::runtime_error("Failed to open file for loading");
        }

        char header[64];
        in.getline(header, 64);
        if ((in.fail() && !in.eof()) || std::strcmp(header, "ARRAY") != 0 ) {
            throw std::runtime_error("Invalid file format");
        }

        size_t n;
        if (!(in >> n)) {
            throw std::runtime_error("File ended prematurely or invalid data format during size read");
        }

        arr->set_size(n);

        for (size_t i = 0; i < n; i++) {
            T value;
            if (!(in >> value)) {
                throw std::runtime_error("File ended prematurely or invalid data format during element read");
            }
            arr->get_data()[i] = value;
        }
    }
};