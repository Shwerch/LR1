#pragma once

#include "base.h"

#include <iostream>
#include <fstream>
#include <cstring>

template<typename T>
struct Array final : Base {
private:
    T* buffer = nullptr;
    size_t sz = 0;
    size_t cap = 0;

public:
    Array() = default;

    explicit Array(size_t initial_capacity) {
        if (initial_capacity > 0) {
            cap = initial_capacity * 2;
            sz = initial_capacity;
            buffer = new T[cap];
        } else {
            cap = 0;
            sz = 0;
            buffer = nullptr;
        }
    }

    ~Array() override {
        delete[] buffer;
    }

    const T& operator[](size_t index) const {
        if (index >= sz) {
            throw std::out_of_range("Index out of range");
        }
        return buffer[index];
    }

    T& operator[](size_t index) {
        if (index >= sz) {
            throw std::out_of_range("Index out of range");
        }
        return buffer[index];
    }

    size_t size() const {
        return sz;
    }

    size_t capacity() const {
        return cap;
    }

    void push_back(const T& value) {
        if (sz >= cap) {
            size_t new_cap = (cap == 0) ? 1 : cap * 2;
            T* new_buf = new T[new_cap];

            for (size_t i = 0; i < sz; i++)
                std::move(buffer, buffer + sz, new_buf);

            delete[] buffer;
            buffer = new_buf;
            cap = new_cap;
        }
        buffer[sz++] = value;
    }

    void pop_back() {
        if (sz == 0) {
            throw std::runtime_error("Cannot pop_back from empty array");
        }
        sz--;
    }

    T* data_ptr() { return buffer; }
    const T* data_ptr() const { return buffer; }

    void set_size(size_t new_size) {
        if (new_size > cap) {
            T* new_buf = new T[new_size];
            for (size_t i = 0; i < sz; i++)
                new_buf[i] = buffer[i];
            delete[] buffer;
            buffer = new_buf;
            cap = new_size;
        }
        sz = new_size;
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
            std::cout << " " << (*arr)[i];
        }
        std::cout << std::endl;
    }

    void save(const char* filename, const Base& data) override {
        const Array<T>* arr = cast(data);

        std::ofstream out(filename);
        if (!out.is_open()) {
            throw std::runtime_error("Failed to open file for saving");
        }

        out << "ARRAY\n";
        out << arr->size() << "\n";
        for (size_t i = 0; i < arr->size(); i++) {
            out << (*arr)[i] << "\n";
        }
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
        in >> n;

        arr->set_size(n);

        for (size_t i = 0; i < n; i++) {
            T value;
            in >> value;
            arr->data_ptr()[i] = value;
        }
    }
};