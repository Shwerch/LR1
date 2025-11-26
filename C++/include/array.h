#pragma once

#include "base.h"

#include <iostream>
#include <fstream>
#include <cstring>

#define CHECK_RANGE(index) if ((index) >= size_) { throw std::out_of_range("Index out of range"); }

template<typename T>
struct Array final : Base {
private:
    T* buffer_ = nullptr;
    size_t size_ = 0;
    size_t capacity_ = 0;

public:
    Array() = default;

    explicit Array(size_t count) : size_(count), capacity_(count * 2) {
        buffer_ = count > 0 ? new T[capacity_] : nullptr;
    }

    ~Array() override {
        delete[] buffer_;
    }

    // Конструктор копирования
    Array(const Array& other) : Base(other) {
        if (other.capacity_ > 0) {
            T* new_buf = new T[other.capacity_];
            for (size_t i = 0; i < other.size_; ++i) {
                new_buf[i] = other.buffer_[i];
            }
            buffer_ = new_buf;
        } else {
            buffer_ = nullptr;
        }
        size_ = other.size_;
        capacity_ = other.capacity_;
    }

    // Оператор присваивания копированием
    Array& operator=(const Array& other) {
        if (this != &other) {
            Array temp(other);
            std::swap(buffer_, temp.buffer_);
            std::swap(size_, temp.size_);
            std::swap(capacity_, temp.capacity_);
        }
        return *this;
    }

    // Конструктор перемещения
    Array(Array&& other) noexcept : Base(std::move(other)),
        buffer_(other.buffer_),
        size_(other.size_),
        capacity_(other.capacity_) {

        other.buffer_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }

    // Оператор присваивания перемещением
    Array& operator=(Array&& other) noexcept {
        if (this != &other) {
            delete[] buffer_;

            buffer_ = other.buffer_;
            size_ = other.size_;
            capacity_ = other.capacity_;

            other.buffer_ = nullptr;
            other.size_ = 0;
            other.capacity_ = 0;
        }
        return *this;
    }

    const T& get(size_t index) const {
        CHECK_RANGE(index)
        return buffer_[index];
    }

    T& get(size_t index) {
        CHECK_RANGE(index)
        return buffer_[index];
    }

    void replace(size_t index, const T& value) {
        CHECK_RANGE(index)
        buffer_[index] = value;
    }

    size_t size() const {
        return size_;
    }

    size_t capacity() const {
        return capacity_;
    }

    void push_back(const T& value) {
        if (size_ >= capacity_) {
            size_t new_cap = capacity_ == 0 ? 2 : capacity_ * 2;
            T* new_buf = new T[new_cap];

            for (size_t i = 0; i < size_; i++) {
                new_buf[i] = buffer_[i];
            }

            delete[] buffer_;
            buffer_ = new_buf;
            capacity_ = new_cap;
        }
        buffer_[size_++] = value;
    }

    void pop_back() {
        if (size_ == 0) {
            throw std::runtime_error("Cannot pop back from empty array");
        }
        --size_;
    }

    void remove(size_t index) {
        CHECK_RANGE(index)
        for (size_t i = index; i < size_ - 1; i++) {
            buffer_[i] = buffer_[i + 1];
        }
        --size_;
    }

    T* get_data() const { return buffer_; }

    void set_size(size_t new_size) {
        if (new_size > capacity_) {
            T* new_buf = new T[new_size];
            for (size_t i = 0; i < size_; i++) {
                new_buf[i] = buffer_[i];
            }
            delete[] buffer_;
            buffer_ = new_buf;
            capacity_ = new_size;
        }
        size_ = new_size;
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