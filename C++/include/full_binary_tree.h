#pragma once

#include "base.h"
#include "array.h"
#include "queue.h"

#include <iostream>
#include <fstream>
#include <cstring>

template<typename T>
struct FNode {
    T data;
    FNode* left;
    FNode* right;

    explicit FNode(const T& value) : data(value), left(nullptr), right(nullptr) {}
};

template<typename T>
struct FullBinaryTree final : Base {
private:
    FNode<T>* root_;

    void copy_tree(FNode<T>*& dest, FNode<T>* src) {
        if (!src) {
            dest = nullptr;
            return;
        }
        dest = new FNode<T>(src->data);
        copy_tree(dest->left, src->left);
        copy_tree(dest->right, src->right);
    }

    void delete_tree(FNode<T>* node) {
        if (!node) return;
        delete_tree(node->left);
        delete_tree(node->right);
        delete node;
    }

    bool is_full_binary_tree(FNode<T>* node) const {
        if (!node) return true;

        // Если у узла есть только один потомок - это не полное бинарное дерево
        if ((node->left && !node->right) || (!node->left && node->right)) {
            return false;
        }

        // Если это листовой узел
        if (!node->left && !node->right) {
            return true;
        }

        // Рекурсивно проверяем оба поддерева
        return is_full_binary_tree(node->left) && is_full_binary_tree(node->right);
    }

    size_t count_nodes(FNode<T>* node) const {
        if (!node) return 0;
        return 1 + count_nodes(node->left) + count_nodes(node->right);
    }

public:
    FullBinaryTree() : root_(nullptr) {}

    ~FullBinaryTree() override {
        delete_tree(root_);
    }

    FullBinaryTree(const FullBinaryTree& other) : Base(other) {
        copy_tree(root_, other.root_);
    }

    FullBinaryTree(FullBinaryTree&& other) noexcept : Base(std::move(other)), root_(other.root_) {
        other.root_ = nullptr;
    }

    // Вставка элемента с сохранением свойства Full Binary Tree
    void insert(const T& value) {
        if (!root_) {
            root_ = new FNode<T>(value);
            return;
        }

        Queue<FNode<T>*> q;
        q.enqueue(root_);

        while (!q.is_empty()) {
            FNode<T>* current = q.front();
            q.dequeue();

            // Если у узла нет детей, добавляем оба
            if (!current->left && !current->right) {
                current->left = new FNode<T>(value);
                return;
            }

            // Если у узла есть оба ребенка, добавляем их в очередь
            if (current->left && current->right) {
                q.enqueue(current->left);
                q.enqueue(current->right);
                continue;
            }

            // Если есть только левый ребенок, добавляем правый
            if (current->left && !current->right) {
                current->right = new FNode<T>(value);
                return;
            }
        }
    }

    // Удаление последнего узла (чтобы сохранить свойство Full Binary Tree)
    bool remove_last() {
        if (!root_) return false;

        if (!root_->left && !root_->right) {
            delete root_;
            root_ = nullptr;
            return true;
        }

        Queue<FNode<T>*> q;
        q.enqueue(root_);
        FNode<T>* parent = nullptr;
        FNode<T>* last = nullptr;

        while (!q.is_empty()) {
            FNode<T>* current = q.front();
            q.dequeue();

            if (current->left) {
                parent = current;
                last = current->left;
                q.enqueue(current->left);
            }
            if (current->right) {
                parent = current;
                last = current->right;
                q.enqueue(current->right);
            }
        }

        if (parent && last) {
            if (parent->right == last) {
                delete parent->right;
                parent->right = nullptr;
            } else {
                delete parent->left;
                parent->left = nullptr;
            }
            return true;
        }

        return false;
    }

    bool is_full() const {
        return is_full_binary_tree(root_);
    }

    size_t size() const {
        return count_nodes(root_);
    }

    bool empty() const {
        return root_ == nullptr;
    }

    void clear() {
        delete_tree(root_);
        root_ = nullptr;
    }

    FNode<T>* get_root() const {
        return root_;
    }

    void set_root(FNode<T>* new_root) {
        root_ = new_root;
    }
};

template<typename T>
struct FullBinaryTreeHelper final : Helper {
private:
    static FullBinaryTree<T>* cast(Base* b) {
        auto* ptr = dynamic_cast<FullBinaryTree<T>*>(b);
        if (!ptr) {
            throw std::runtime_error("Invalid Base type for FullBinaryTreeHelper");
        }
        return ptr;
    }

    static const FullBinaryTree<T>* cast(const Base& b) {
        auto* ptr = dynamic_cast<const FullBinaryTree<T>*>(&b);
        if (!ptr) {
            throw std::runtime_error("Invalid Base type for FullBinaryTreeHelper");
        }
        return ptr;
    }

    int get_height(FNode<T>* node) const {
        if (!node) return 0;
        int left_h = get_height(node->left);
        int right_h = get_height(node->right);
        return 1 + (left_h > right_h ? left_h : right_h);
    }

    int get_max_width(FNode<T>* node) const {
        if (!node) return 1;

        int count = 0;
        T temp = node->data;
        if (temp == 0) return 1;
        if (temp < 0) {
            count = 1;
            temp = -temp;
        }
        while (temp > 0) {
            count++;
            temp /= 10;
        }
        return count > 0 ? count : 1;
    }

    void get_all_widths(FNode<T>* node, int& max_w) const {
        if (!node) return;
        int w = get_max_width(node);
        if (w > max_w) max_w = w;
        get_all_widths(node->left, max_w);
        get_all_widths(node->right, max_w);
    }

    void print_level(FNode<T>* node, int level, int spaces, int width) const {
        if (level == 0) {
            if (node) {
                int val_width = get_max_width(node);
                int padding = (width - val_width) / 2;
                for (int i = 0; i < spaces + padding; i++) std::cout << " ";
                std::cout << node->data;
                for (int i = 0; i < spaces + (width - val_width - padding); i++) std::cout << " ";
            } else {
                for (int i = 0; i < spaces + width + spaces; i++) std::cout << " ";
            }
        } else {
            print_level(node ? node->left : nullptr, level - 1, spaces, width);
            print_level(node ? node->right : nullptr, level - 1, spaces, width);
        }
    }

    void serialize(FNode<T>* node, std::ofstream& out) const {
        if (!node) {
            out << "# ";
            return;
        }
        out << node->data << " ";
        serialize(node->left, out);
        serialize(node->right, out);
    }

    FNode<T>* deserialize(std::ifstream& in) const {
        char marker[2];
        if (!(in >> marker)) {
            return nullptr;
        }

        if (marker[0] == '#') {
            return nullptr;
        }

        // Считываем значение
        in.seekg(-static_cast<int>(strlen(marker) + 1), std::ios::cur);

        T value;
        if (!(in >> value)) {
            throw std::runtime_error("Failed to read node value");
        }

        FNode<T>* node = new FNode<T>(value);
        node->left = deserialize(in);
        node->right = deserialize(in);

        return node;
    }

public:
    void print(const Base& data) override {
        const FullBinaryTree<T>* tree = cast(data);

        std::cout << "FULL BINARY TREE (size = " << tree->size() << "):" << std::endl;
        if (tree->empty()) {
            std::cout << "(empty)" << std::endl;
        } else {
            FNode<T>* root = tree->get_root();
            int height = get_height(root);
            int max_width = 0;
            get_all_widths(root, max_width);

            for (int i = 0; i < height; i++) {
                int level_nodes = 1;
                for (int j = 0; j < i; j++) level_nodes *= 2;

                int spaces = max_width;
                for (int j = i; j < height - 1; j++) spaces = spaces * 2 + max_width;

                print_level(root, i, spaces, max_width);
                std::cout << std::endl;
            }
        }
        std::cout << "Is Full: " << (tree->is_full() ? "Yes" : "No") << std::endl;
    }

    void save(const char* filename, const Base& data) override {
        const FullBinaryTree<T>* tree = cast(data);

        std::ofstream out(filename);
        if (!out.is_open()) {
            throw std::runtime_error("Failed to open file for saving");
        }

        out << "FULL_BINARY_TREE" << std::endl;
        out << tree->size() << std::endl;
        serialize(tree->get_root(), out);
        out << std::endl;
        out.close();
    }

    void load(const char* filename, Base* data) override {
        FullBinaryTree<T>* tree = cast(data);

        std::ifstream in(filename);
        if (!in.is_open()) {
            throw std::runtime_error("Failed to open file for loading");
        }

        char header[64];
        in.getline(header, 64);
        if ((in.fail() && !in.eof()) || std::strcmp(header, "FULL_BINARY_TREE") != 0) {
            throw std::runtime_error("Invalid file format");
        }

        size_t n;
        if (!(in >> n)) {
            throw std::runtime_error("File ended prematurely or invalid data format during size read");
        }

        tree->clear();
        FNode<T>* new_root = deserialize(in);
        tree->set_root(new_root);

        in.close();
    }
};