#include "tree.h"

#include <iostream>
#include <fstream>
#include <cstring>

void Tree::init() {
    capacity = 16;
    size = 0;
    data = new int[capacity];
}

void Tree::resize() {
    size_t newcap = capacity ? capacity * 2 : 16;
    int* nd = new int[newcap];
    for (size_t i = 0; i < size; ++i) nd[i] = data[i];
    delete[] data;
    data = nd;
    capacity = newcap;
}

void Tree::insert(int value) {
    if (size >= capacity) resize();
    data[size++] = value;
}

int Tree::index_of(int value) const {
    for (size_t i = 0; i < size; ++i) if (data[i] == value) return static_cast<int>(i);
    return -1;
}

void Tree::del(int value) {
    int idx = index_of(value);
    if (idx < 0) return;
    if (size == 0) return;
    data[idx] = data[size - 1];
    --size;
}

bool Tree::get(int value) const {
    return index_of(value) >= 0;
}

int Tree::height() const {
    if (size == 0) return 0;
    int h = 0;
    size_t nodes = 1;
    while (nodes <= size) { ++h; nodes <<= 1; }
    return h;
}

void Tree::print() const {
    std::cout << "Tree (size=" << size << "):\n";
    if (size == 0) {
        std::cout << "Empty tree\n";
        return;
    }

    int h = height();
    int maxNodes = (1 << h) - 1;
    if (maxNodes < 1) maxNodes = 1;

    char** slots = new char*[maxNodes];
    for (int i = 0; i < maxNodes; ++i) slots[i] = nullptr;

    int maxLen = 1;
    for (size_t i = 0; i < size; ++i) {
        char tmp[32];
        int len = std::snprintf(tmp, sizeof(tmp), "%d", data[i]);
        if (len > maxLen) maxLen = len;
        if (static_cast<int>(i) < maxNodes) {
            slots[i] = new char[len + 1];
            std::memcpy(slots[i], tmp, len + 1);
        }
    }

    int cellWidth = maxLen + 2;
    if (cellWidth < 1) cellWidth = 1;

    for (int level = 0; level < h; ++level) {
        int nodesThisLevel = 1 << level;
        int firstIndex = (1 << level) - 1;

        int segment = 1 << (h - level);
        int segmentWidth = segment * cellWidth;

        int leading = segmentWidth / 2 - (cellWidth / 2);
        if (leading < 0) leading = 0;
        int between = segmentWidth - cellWidth;
        if (between < 0) between = 0;

        for (int i = 0; i < leading; ++i) std::cout << ' ';

        for (int n = 0; n < nodesThisLevel; ++n) {
            int idx = firstIndex + n;
            const char* s = nullptr;
            if (idx < maxNodes && slots[idx]) s = slots[idx];

            int slen = 0;
            if (s) {
                const char* p = s;
                while (*p) { ++slen; ++p; }
            }

            int padTotal = cellWidth - slen;
            if (padTotal < 0) padTotal = 0;
            int padLeft = padTotal / 2;
            int padRight = padTotal - padLeft;

            for (int i = 0; i < padLeft; ++i) std::cout << ' ';
            if (s) std::cout << s; else {
                for (int i = 0; i < slen; ++i) std::cout << ' ';
            }
            for (int i = 0; i < padRight; ++i) std::cout << ' ';

            if (n < nodesThisLevel - 1) {
                for (int i = 0; i < between; ++i) std::cout << ' ';
            }
        }
        std::cout << '\n';
    }

    for (int i = 0; i < maxNodes; ++i) {
        if (slots[i]) delete[] slots[i];
    }
    delete[] slots;
}


void Tree::save(const char* filename) const {
    std::ofstream file(filename);
    file << "TREE\n" << size << "\n";
    for (size_t i = 0; i < size; ++i) file << data[i] << "\n";
}

void Tree::load(const char* filename) {
    std::ifstream file(filename);
    if (!file) return;
    char type[20];
    file >> type;
    if (std::strcmp(type, "TREE") != 0) return;
    size_t sz;
    file >> sz;
    for (size_t i = 0; i < sz; ++i) {
        int v;
        file >> v;
        insert(v);
    }
}

void Tree::free() {
    delete[] data;
    data = nullptr;
    size = 0;
    capacity = 0;
}