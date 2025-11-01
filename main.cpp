#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>

struct Array {
    int* data;
    size_t size;
    size_t capacity;
};

struct StackNode {
    int value;
    StackNode* next;
};

struct Stack {
    StackNode* top;
    size_t size;
};

struct ForwardNode {
    int value;
    ForwardNode* next;
};

struct ForwardList {
    ForwardNode* head;
    size_t size;
};

struct DoubleNode {
    int value;
    DoubleNode* next;
    DoubleNode* prev;
};

struct DoublyList {
    DoubleNode* head;
    DoubleNode* tail;
    size_t size;
};

struct QueueNode {
    int value;
    QueueNode* next;
};

struct Queue {
    QueueNode* front;
    QueueNode* rear;
    size_t size;
};

struct TreeNode {
    int value;
    TreeNode* left;
    TreeNode* right;
};

struct Tree {
    TreeNode* root;
    size_t size;
};

void arrayInit(Array& arr) {
    arr.capacity = 10;
    arr.size = 0;
    arr.data = new int[arr.capacity];
}

void arrayResize(Array& arr) {
    arr.capacity *= 2;
    int* newData = new int[arr.capacity];
    for (size_t i = 0; i < arr.size; i++) {
        newData[i] = arr.data[i];
    }
    delete[] arr.data;
    arr.data = newData;
}

void arrayPush(Array& arr, int value) {
    if (arr.size >= arr.capacity) {
        arrayResize(arr);
    }
    arr.data[arr.size++] = value;
}

void arrayDel(Array& arr, size_t index) {
    if (index >= arr.size) return;
    for (size_t i = index; i < arr.size - 1; i++) {
        arr.data[i] = arr.data[i + 1];
    }
    arr.size--;
}

int arrayGet(const Array& arr, size_t index) {
    if (index >= arr.size) return -1;
    return arr.data[index];
}

void arrayFree(Array& arr) {
    delete[] arr.data;
    arr.data = nullptr;
    arr.size = 0;
    arr.capacity = 0;
}

void stackInit(Stack& s) {
    s.top = nullptr;
    s.size = 0;
}

void stackPush(Stack& s, int value) {
    StackNode* node = new StackNode{value, s.top};
    s.top = node;
    s.size++;
}

int stackPop(Stack& s) {
    if (!s.top) return -1;
    StackNode* temp = s.top;
    int value = temp->value;
    s.top = s.top->next;
    delete temp;
    s.size--;
    return value;
}

int stackPeek(const Stack& s) {
    if (!s.top) return -1;
    return s.top->value;
}

void stackFree(Stack& s) {
    while (s.top) {
        StackNode* temp = s.top;
        s.top = s.top->next;
        delete temp;
    }
    s.size = 0;
}

void forwardListInit(ForwardList& list) {
    list.head = nullptr;
    list.size = 0;
}

void forwardListPush(ForwardList& list, int value) {
    ForwardNode* node = new ForwardNode{value, list.head};
    list.head = node;
    list.size++;
}

void forwardListDel(ForwardList& list, size_t index) {
    if (index >= list.size || !list.head) return;

    if (index == 0) {
        ForwardNode* temp = list.head;
        list.head = list.head->next;
        delete temp;
        list.size--;
        return;
    }

    ForwardNode* current = list.head;
    for (size_t i = 0; i < index - 1; i++) {
        current = current->next;
    }

    ForwardNode* temp = current->next;
    current->next = temp->next;
    delete temp;
    list.size--;
}

int forwardListGet(const ForwardList& list, size_t index) {
    if (index >= list.size) return -1;
    ForwardNode* current = list.head;
    for (size_t i = 0; i < index; i++) {
        current = current->next;
    }
    return current->value;
}

void forwardListFree(ForwardList& list) {
    while (list.head) {
        ForwardNode* temp = list.head;
        list.head = list.head->next;
        delete temp;
    }
    list.size = 0;
}

void doublyListInit(DoublyList& list) {
    list.head = nullptr;
    list.tail = nullptr;
    list.size = 0;
}

void doublyListPush(DoublyList& list, int value) {
    DoubleNode* node = new DoubleNode{value, nullptr, list.tail};

    if (list.tail) {
        list.tail->next = node;
    } else {
        list.head = node;
    }

    list.tail = node;
    list.size++;
}

void doublyListDel(DoublyList& list, size_t index) {
    if (index >= list.size) return;

    DoubleNode* current = list.head;
    for (size_t i = 0; i < index; i++) {
        current = current->next;
    }

    if (current->prev) {
        current->prev->next = current->next;
    } else {
        list.head = current->next;
    }

    if (current->next) {
        current->next->prev = current->prev;
    } else {
        list.tail = current->prev;
    }

    delete current;
    list.size--;
}

int doublyListGet(const DoublyList& list, size_t index) {
    if (index >= list.size) return -1;
    DoubleNode* current = list.head;
    for (size_t i = 0; i < index; i++) {
        current = current->next;
    }
    return current->value;
}

void doublyListFree(DoublyList& list) {
    while (list.head) {
        DoubleNode* temp = list.head;
        list.head = list.head->next;
        delete temp;
    }
    list.tail = nullptr;
    list.size = 0;
}

void queueInit(Queue& q) {
    q.front = nullptr;
    q.rear = nullptr;
    q.size = 0;
}

void queuePush(Queue& q, int value) {
    QueueNode* node = new QueueNode{value, nullptr};

    if (q.rear) {
        q.rear->next = node;
    } else {
        q.front = node;
    }

    q.rear = node;
    q.size++;
}

int queuePop(Queue& q) {
    if (!q.front) return -1;

    QueueNode* temp = q.front;
    int value = temp->value;
    q.front = q.front->next;

    if (!q.front) {
        q.rear = nullptr;
    }

    delete temp;
    q.size--;
    return value;
}

int queuePeek(const Queue& q) {
    if (!q.front) return -1;
    return q.front->value;
}

void queueFree(Queue& q) {
    while (q.front) {
        QueueNode* temp = q.front;
        q.front = q.front->next;
        delete temp;
    }
    q.rear = nullptr;
    q.size = 0;
}

void treeInit(Tree& t) {
    t.root = nullptr;
    t.size = 0;
}

TreeNode* treeInsertHelper(TreeNode* node, int value) {
    if (!node) {
        return new TreeNode{value, nullptr, nullptr};
    }

    if (value < node->value) {
        node->left = treeInsertHelper(node->left, value);
    } else if (value > node->value) {
        node->right = treeInsertHelper(node->right, value);
    }

    return node;
}

void treeInsert(Tree& t, int value) {
    t.root = treeInsertHelper(t.root, value);
    t.size++;
}

TreeNode* findMin(TreeNode* node) {
    while (node->left) {
        node = node->left;
    }
    return node;
}

TreeNode* treeDeleteHelper(TreeNode* node, int value, bool& deleted) {
    if (!node) return nullptr;

    if (value < node->value) {
        node->left = treeDeleteHelper(node->left, value, deleted);
    } else if (value > node->value) {
        node->right = treeDeleteHelper(node->right, value, deleted);
    } else {
        deleted = true;

        if (!node->left && !node->right) {
            delete node;
            return nullptr;
        } else if (!node->left) {
            TreeNode* temp = node->right;
            delete node;
            return temp;
        } else if (!node->right) {
            TreeNode* temp = node->left;
            delete node;
            return temp;
        } else {
            TreeNode* temp = findMin(node->right);
            node->value = temp->value;
            node->right = treeDeleteHelper(node->right, temp->value, deleted);
            deleted = false;
        }
    }

    return node;
}

void treeDelete(Tree& t, int value) {
    bool deleted = false;
    t.root = treeDeleteHelper(t.root, value, deleted);
    if (deleted) t.size--;
}

bool treeSearch(TreeNode* node, int value) {
    if (!node) return false;
    if (node->value == value) return true;
    if (value < node->value) return treeSearch(node->left, value);
    return treeSearch(node->right, value);
}

bool treeGet(const Tree& t, int value) {
    return treeSearch(t.root, value);
}

void treeFreeHelper(TreeNode* node) {
    if (!node) return;
    treeFreeHelper(node->left);
    treeFreeHelper(node->right);
    delete node;
}

void treeFree(Tree& t) {
    treeFreeHelper(t.root);
    t.root = nullptr;
    t.size = 0;
}

void printArray(const Array& arr) {
    std::cout << "Array (size=" << arr.size << "): ";
    for (size_t i = 0; i < arr.size; i++) {
        std::cout << arr.data[i] << " ";
    }
    std::cout << std::endl;
}

void printStack(const Stack& s) {
    std::cout << "Stack (size=" << s.size << "): ";
    StackNode* current = s.top;
    while (current) {
        std::cout << current->value << " ";
        current = current->next;
    }
    std::cout << std::endl;
}

void printForwardList(const ForwardList& list) {
    std::cout << "ForwardList (size=" << list.size << "): ";
    ForwardNode* current = list.head;
    while (current) {
        std::cout << current->value << " ";
        current = current->next;
    }
    std::cout << std::endl;
}

void printDoublyList(const DoublyList& list) {
    std::cout << "DoublyList (size=" << list.size << "): ";
    DoubleNode* current = list.head;
    while (current) {
        std::cout << current->value << " ";
        current = current->next;
    }
    std::cout << std::endl;
}

void printQueue(const Queue& q) {
    std::cout << "Queue (size=" << q.size << "): ";
    QueueNode* current = q.front;
    while (current) {
        std::cout << current->value << " ";
        current = current->next;
    }
    std::cout << std::endl;
}

int getTreeHeight(TreeNode* node) {
    if (!node) return 0;
    int leftHeight = getTreeHeight(node->left);
    int rightHeight = getTreeHeight(node->right);
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

void printLevel(TreeNode* node, int level, int indent, int spacing) {
    if (level == 1) {
        for (int i = 0; i < indent; i++) std::cout << " ";
        if (node) {
            std::cout << node->value;
        } else {
            std::cout << " ";
        }
        for (int i = 0; i < spacing; i++) std::cout << " ";
    } else if (level > 1) {
        printLevel(node ? node->left : nullptr, level - 1, indent, spacing);
        printLevel(node ? node->right : nullptr, level - 1, indent, spacing);
    }
}

void printTree(const Tree& t) {
    std::cout << "Tree (size=" << t.size << "):\n";
    if (!t.root) {
        std::cout << "Empty tree\n";
        return;
    }

    int height = getTreeHeight(t.root);
    int maxWidth = (1 << height) - 1;

    for (int level = 1; level <= height; level++) {
        int numNodes = 1 << (level - 1);
        int spacing = (maxWidth / numNodes) - 1;
        int indent = (maxWidth - (numNodes + (numNodes - 1) * spacing)) / 2;

        printLevel(t.root, level, indent, spacing);
        std::cout << "\n";
    }
}

void saveArray(const char* filename, const Array& arr) {
    std::ofstream file(filename);
    file << "ARRAY\n" << arr.size << "\n";
    for (size_t i = 0; i < arr.size; i++) {
        file << arr.data[i] << "\n";
    }
}

void saveStack(const char* filename, const Stack& s) {
    std::ofstream file(filename);
    file << "STACK\n" << s.size << "\n";
    StackNode* current = s.top;
    while (current) {
        file << current->value << "\n";
        current = current->next;
    }
}

void saveForwardList(const char* filename, const ForwardList& list) {
    std::ofstream file(filename);
    file << "FORWARD\n" << list.size << "\n";
    ForwardNode* current = list.head;
    while (current) {
        file << current->value << "\n";
        current = current->next;
    }
}

void saveDoublyList(const char* filename, const DoublyList& list) {
    std::ofstream file(filename);
    file << "DOUBLY\n" << list.size << "\n";
    DoubleNode* current = list.head;
    while (current) {
        file << current->value << "\n";
        current = current->next;
    }
}

void saveQueue(const char* filename, const Queue& q) {
    std::ofstream file(filename);
    file << "QUEUE\n" << q.size << "\n";
    QueueNode* current = q.front;
    while (current) {
        file << current->value << "\n";
        current = current->next;
    }
}

void saveTreeHelper(std::ofstream& file, TreeNode* node) {
    if (!node) return;
    file << node->value << "\n";
    saveTreeHelper(file, node->left);
    saveTreeHelper(file, node->right);
}

void saveTree(const char* filename, const Tree& t) {
    std::ofstream file(filename);
    file << "TREE\n" << t.size << "\n";
    saveTreeHelper(file, t.root);
}

void loadArray(const char* filename, Array& arr) {
    std::ifstream file(filename);
    if (!file) return;

    char type[20];
    file >> type;
    if (strcmp(type, "ARRAY") != 0) return;

    size_t size;
    file >> size;
    for (size_t i = 0; i < size; i++) {
        int value;
        file >> value;
        arrayPush(arr, value);
    }
}

void loadStack(const char* filename, Stack& s) {
    std::ifstream file(filename);
    if (!file) return;

    char type[20];
    file >> type;
    if (strcmp(type, "STACK") != 0) return;

    size_t size;
    file >> size;
    int* values = new int[size];
    for (size_t i = 0; i < size; i++) {
        file >> values[i];
    }
    for (int i = size - 1; i >= 0; i--) {
        stackPush(s, values[i]);
    }
    delete[] values;
}

void loadForwardList(const char* filename, ForwardList& list) {
    std::ifstream file(filename);
    if (!file) return;

    char type[20];
    file >> type;
    if (strcmp(type, "FORWARD") != 0) return;

    size_t size;
    file >> size;
    int* values = new int[size];
    for (size_t i = 0; i < size; i++) {
        file >> values[i];
    }
    for (int i = size - 1; i >= 0; i--) {
        forwardListPush(list, values[i]);
    }
    delete[] values;
}

void loadDoublyList(const char* filename, DoublyList& list) {
    std::ifstream file(filename);
    if (!file) return;

    char type[20];
    file >> type;
    if (strcmp(type, "DOUBLY") != 0) return;

    size_t size;
    file >> size;
    for (size_t i = 0; i < size; i++) {
        int value;
        file >> value;
        doublyListPush(list, value);
    }
}

void loadQueue(const char* filename, Queue& q) {
    std::ifstream file(filename);
    if (!file) return;

    char type[20];
    file >> type;
    if (strcmp(type, "QUEUE") != 0) return;

    size_t size;
    file >> size;
    for (size_t i = 0; i < size; i++) {
        int value;
        file >> value;
        queuePush(q, value);
    }
}

void loadTree(const char* filename, Tree& t) {
    std::ifstream file(filename);
    if (!file) return;

    char type[20];
    file >> type;
    if (strcmp(type, "TREE") != 0) return;

    size_t size;
    file >> size;
    for (size_t i = 0; i < size; i++) {
        int value;
        file >> value;
        treeInsert(t, value);
    }
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cout << "Usage: program <filename> <command> [args...]\n";
        return 1;
    }

    const char* filename = argv[1];
    const char* command = argv[2];

    if (command[0] == 'M') {
        Array arr;
        arrayInit(arr);
        loadArray(filename, arr);

        if (strcmp(command, "MPUSH") == 0 && argc >= 4) {
            arrayPush(arr, atoi(argv[3]));
            saveArray(filename, arr);
        } else if (strcmp(command, "MDEL") == 0 && argc >= 4) {
            arrayDel(arr, atoi(argv[3]));
            saveArray(filename, arr);
        } else if (strcmp(command, "MGET") == 0 && argc >= 4) {
            std::cout << arrayGet(arr, atoi(argv[3])) << std::endl;
        } else if (strcmp(command, "PRINT") == 0) {
            printArray(arr);
        }

        arrayFree(arr);
    } else if (command[0] == 'S') {
        Stack s;
        stackInit(s);
        loadStack(filename, s);

        if (strcmp(command, "SPUSH") == 0 && argc >= 4) {
            stackPush(s, atoi(argv[3]));
            saveStack(filename, s);
        } else if (strcmp(command, "SPOP") == 0) {
            int value = stackPop(s);
            std::cout << value << std::endl;
            saveStack(filename, s);
        } else if (strcmp(command, "SPEEK") == 0) {
            std::cout << stackPeek(s) << std::endl;
        } else if (strcmp(command, "PRINT") == 0) {
            printStack(s);
        }

        stackFree(s);
    } else if (command[0] == 'F') {
        ForwardList list;
        forwardListInit(list);
        loadForwardList(filename, list);

        if (strcmp(command, "FPUSH") == 0 && argc >= 4) {
            forwardListPush(list, atoi(argv[3]));
            saveForwardList(filename, list);
        } else if (strcmp(command, "FDEL") == 0 && argc >= 4) {
            forwardListDel(list, atoi(argv[3]));
            saveForwardList(filename, list);
        } else if (strcmp(command, "FGET") == 0 && argc >= 4) {
            std::cout << forwardListGet(list, atoi(argv[3])) << std::endl;
        } else if (strcmp(command, "PRINT") == 0) {
            printForwardList(list);
        }

        forwardListFree(list);
    } else if (command[0] == 'L') {
        DoublyList list;
        doublyListInit(list);
        loadDoublyList(filename, list);

        if (strcmp(command, "LPUSH") == 0 && argc >= 4) {
            doublyListPush(list, atoi(argv[3]));
            saveDoublyList(filename, list);
        } else if (strcmp(command, "LDEL") == 0 && argc >= 4) {
            doublyListDel(list, atoi(argv[3]));
            saveDoublyList(filename, list);
        } else if (strcmp(command, "LGET") == 0 && argc >= 4) {
            std::cout << doublyListGet(list, atoi(argv[3])) << std::endl;
        } else if (strcmp(command, "PRINT") == 0) {
            printDoublyList(list);
        }

        doublyListFree(list);
    } else if (command[0] == 'Q') {
        Queue q;
        queueInit(q);
        loadQueue(filename, q);

        if (strcmp(command, "QPUSH") == 0 && argc >= 4) {
            queuePush(q, atoi(argv[3]));
            saveQueue(filename, q);
        } else if (strcmp(command, "QPOP") == 0) {
            int value = queuePop(q);
            std::cout << value << std::endl;
            saveQueue(filename, q);
        } else if (strcmp(command, "QPEEK") == 0) {
            std::cout << queuePeek(q) << std::endl;
        } else if (strcmp(command, "PRINT") == 0) {
            printQueue(q);
        }

        queueFree(q);
    } else if (command[0] == 'T') {
        Tree t;
        treeInit(t);
        loadTree(filename, t);

        if (strcmp(command, "TINSERT") == 0 && argc >= 4) {
            treeInsert(t, atoi(argv[3]));
            saveTree(filename, t);
        } else if (strcmp(command, "TDEL") == 0 && argc >= 4) {
            treeDelete(t, atoi(argv[3]));
            saveTree(filename, t);
        } else if (strcmp(command, "TGET") == 0 && argc >= 4) {
            std::cout << (treeGet(t, atoi(argv[3])) ? "Found" : "Not found") << std::endl;
        } else if (strcmp(command, "PRINT") == 0) {
            printTree(t);
        }

        treeFree(t);
    } else if (strcmp(command, "PRINT") == 0) {
        std::ifstream file(filename);
        if (file) {
            char type[20];
            file >> type;
            file.close();

            if (strcmp(type, "ARRAY") == 0) {
                Array arr;
                arrayInit(arr);
                loadArray(filename, arr);
                printArray(arr);
                arrayFree(arr);
            } else if (strcmp(type, "STACK") == 0) {
                Stack s;
                stackInit(s);
                loadStack(filename, s);
                printStack(s);
                stackFree(s);
            } else if (strcmp(type, "FORWARD") == 0) {
                ForwardList list;
                forwardListInit(list);
                loadForwardList(filename, list);
                printForwardList(list);
                forwardListFree(list);
            } else if (strcmp(type, "DOUBLY") == 0) {
                DoublyList list;
                doublyListInit(list);
                loadDoublyList(filename, list);
                printDoublyList(list);
                doublyListFree(list);
            } else if (strcmp(type, "QUEUE") == 0) {
                Queue q;
                queueInit(q);
                loadQueue(filename, q);
                printQueue(q);
                queueFree(q);
            } else if (strcmp(type, "TREE") == 0) {
                Tree t;
                treeInit(t);
                loadTree(filename, t);
                printTree(t);
                treeFree(t);
            }
        }
    }

    return 0;
}