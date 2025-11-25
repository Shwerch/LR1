#pragma once

struct Base {
    virtual ~Base() = default;
};

struct Helper {
    virtual ~Helper() = default;

    virtual void print(const Base& data) = 0;
    virtual void save(const char* filename, const Base& data) = 0;
    virtual void load(const char* filename, Base* data) = 0;
};