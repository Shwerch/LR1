#pragma once

#include "array.h"

template<typename T>
struct Stack final : Base {
private:
    Array<T> data_;

public:
    Stack() = default;

    ~Stack() override = default;

    Stack(const Stack& other) : Base(other), data_(other.data_) {}

    Stack(Stack&& other) noexcept : Base(std::move(other)), data_(std::move(other.data_)) {}

    void push(const T& value) {
        data_.push_back(value);
    }

    void pop() {
        if (is_empty()) {
            throw std::runtime_error("Cannot pop from empty stack");
        }
        data_.pop_back();
    }

    T& top() {
        if (is_empty()) {
            throw std::runtime_error("Cannot get top of empty stack");
        }
        return data_.get(data_.size() - 1);
    }

    const T& top() const {
        if (is_empty()) {
            throw std::runtime_error("Cannot get top of empty stack");
        }
        return data_.get(data_.size() - 1);
    }

    bool is_empty() const {
        return data_.size() == 0;
    }

    size_t size() const {
        return data_.size();
    }

    Array<T>& get_data() { return data_; }
    const Array<T>& get_data() const { return data_; }
};

template<typename T>
struct StackHelper final : Helper {
private:
    static Stack<T>* cast(Base* b) {
        auto* ptr = dynamic_cast<Stack<T>*>(b);
        if (!ptr) {
            throw std::runtime_error("Invalid Base type for StackHelper");
        }
        return ptr;
    }

    static const Stack<T>* cast(const Base& b) {
        auto* ptr = dynamic_cast<const Stack<T>*>(&b);
        if (!ptr) {
            throw std::runtime_error("Invalid Base type for StackHelper");
        }
        return ptr;
    }

public:
    void print(const Base& data) override {
        const Stack<T>* stack = cast(data);

        std::cout << "STACK (size = " << stack->size() << "):";
        const Array<T>& arr = stack->get_data();
        for (size_t i = 0; i < stack->size(); i++) {
            std::cout << " " << arr.get(i);
        }
        std::cout << " <- top" << std::endl;
    }

    void save(const char* filename, const Base& data) override {
        const Stack<T>* stack = cast(data);

        std::ofstream out(filename);
        if (!out.is_open()) {
            throw std::runtime_error("Failed to open file for saving");
        }

        out << "STACK" << std::endl;
        out << stack->size() << std::endl;
        const Array<T>& arr = stack->get_data();
        for (size_t i = 0; i < stack->size(); i++) {
            out << arr.get(i) << std::endl;
        }
        out.close();
    }

    void load(const char* filename, Base* data) override {
        Stack<T>* stack = cast(data);

        std::ifstream in(filename);
        if (!in.is_open()) {
            throw std::runtime_error("Failed to open file for loading");
        }

        char header[64];
        in.getline(header, 64);
        if ((in.fail() && !in.eof()) || std::strcmp(header, "STACK") != 0) {
            throw std::runtime_error("Invalid file format");
        }

        size_t n;
        if (!(in >> n)) {
            throw std::runtime_error("File ended prematurely or invalid data format during size read");
        }

        Array<T>& arr = stack->get_data();
        arr.set_size(n);

        for (size_t i = 0; i < n; i++) {
            T value;
            if (!(in >> value)) {
                throw std::runtime_error("File ended prematurely or invalid data format during element read");
            }
            arr.get_data()[i] = value;
        }
    }
};