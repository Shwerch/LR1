#pragma once

#include "array.h"

template<typename T>
struct Queue final : Base {
private:
    Array<T> data_;

public:
    Queue() = default;

    ~Queue() override = default;

    Queue(const Queue& other) : Base(other), data_(other.data_) {}

    Queue(Queue&& other) noexcept : Base(std::move(other)), data_(std::move(other.data_)) {}

    void enqueue(const T& value) {
        data_.push_back(value);
    }

    void dequeue() {
        if (is_empty()) {
            throw std::runtime_error("Cannot dequeue from empty queue");
        }
        data_.remove(0);
    }

    T& front() {
        if (is_empty()) {
            throw std::runtime_error("Cannot get front of empty queue");
        }
        return data_.get(0);
    }

    const T& front() const {
        if (is_empty()) {
            throw std::runtime_error("Cannot get front of empty queue");
        }
        return data_.get(0);
    }

    T& back() {
        if (is_empty()) {
            throw std::runtime_error("Cannot get back of empty queue");
        }
        return data_.get(data_.size() - 1);
    }

    const T& back() const {
        if (is_empty()) {
            throw std::runtime_error("Cannot get back of empty queue");
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
struct QueueHelper final : Helper {
private:
    static Queue<T>* cast(Base* b) {
        auto* ptr = dynamic_cast<Queue<T>*>(b);
        if (!ptr) {
            throw std::runtime_error("Invalid Base type for QueueHelper");
        }
        return ptr;
    }

    static const Queue<T>* cast(const Base& b) {
        auto* ptr = dynamic_cast<const Queue<T>*>(&b);
        if (!ptr) {
            throw std::runtime_error("Invalid Base type for QueueHelper");
        }
        return ptr;
    }

public:
    void print(const Base& data) override {
        const Queue<T>* queue = cast(data);

        std::cout << "QUEUE (size = " << queue->size() << "): front ->";
        const Array<T>& arr = queue->get_data();
        for (size_t i = 0; i < queue->size(); i++) {
            std::cout << " " << arr.get(i);
        }
        std::cout << " <- back" << std::endl;
    }

    void save(const char* filename, const Base& data) override {
        const Queue<T>* queue = cast(data);

        std::ofstream out(filename);
        if (!out.is_open()) {
            throw std::runtime_error("Failed to open file for saving");
        }

        out << "QUEUE" << std::endl;
        out << queue->size() << std::endl;
        const Array<T>& arr = queue->get_data();
        for (size_t i = 0; i < queue->size(); i++) {
            out << arr.get(i) << std::endl;
        }
        out.close();
    }

    void load(const char* filename, Base* data) override {
        Queue<T>* queue = cast(data);

        std::ifstream in(filename);
        if (!in.is_open()) {
            throw std::runtime_error("Failed to open file for loading");
        }

        char header[64];
        in.getline(header, 64);
        if ((in.fail() && !in.eof()) || std::strcmp(header, "QUEUE") != 0) {
            throw std::runtime_error("Invalid file format");
        }

        size_t n;
        if (!(in >> n)) {
            throw std::runtime_error("File ended prematurely or invalid data format during size read");
        }

        Array<T>& arr = queue->get_data();
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