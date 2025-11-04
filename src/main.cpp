#include "array.h"
#include "stack.h"
#include "forward_list.h"
#include "doubly_list.h"
#include "queue.h"
#include "tree.h"

#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>

bool contains_only_digits(const char* value) {
    if (value == nullptr || *value == '\0') {
        return false; 
    }
    for (int i = 0; value[i] != '\0'; ++i) {
        if (!std::isdigit(static_cast<unsigned char>(value[i]))) {
            return false;
        }
    }
    return true;
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: program <filename> <command> [args...]" << std::endl;
        return 1;
    }

    const char* filename = argv[1];
    const char* command = argv[2];
    
    if (std::strcmp(command, "PRINT") && !contains_only_digits(argv[3])) {
        std::cerr << "Argument contains a non-number character" << std::endl;
        return 1;
    }

    if (command[0] == 'M') {
        Array arr;
        arr.init();
        arr.load(filename);

        if (strcmp(command, "MPUSH") == 0 && argc >= 4) {
            arr.push(atoi(argv[3]));
            arr.save(filename);
        } else if (strcmp(command, "MDEL") == 0 && argc >= 4) {
            arr.del(atoi(argv[3]));
            arr.save(filename);
        } else if (strcmp(command, "MGET") == 0 && argc >= 4) {
            std::cout << arr.get(atoi(argv[3])) << std::endl;
        } else if (strcmp(command, "PRINT") == 0) {
            arr.print();
        }

        arr.free();
    } else if (command[0] == 'S') {
        Stack s;
        s.init();
        s.load(filename);

        if (strcmp(command, "SPUSH") == 0 && argc >= 4) {
            s.push(atoi(argv[3]));
            s.save(filename);
        } else if (strcmp(command, "SPOP") == 0) {
            int value = s.pop();
            std::cout << value << std::endl;
            s.save(filename);
        } else if (strcmp(command, "SPEEK") == 0) {
            std::cout << s.peek() << std::endl;
        } else if (strcmp(command, "PRINT") == 0) {
            s.print();
        }

        s.free();
    } else if (command[0] == 'F') {
        ForwardList list;
        list.init();
        list.load(filename);

        if (strcmp(command, "FPUSH") == 0 && argc >= 4) {
            list.push(atoi(argv[3]));
            list.save(filename);
        } else if (strcmp(command, "FDEL") == 0 && argc >= 4) {
            list.del(atoi(argv[3]));
            list.save(filename);
        } else if (strcmp(command, "FGET") == 0 && argc >= 4) {
            std::cout << list.get(atoi(argv[3])) << std::endl;
        } else if (strcmp(command, "PRINT") == 0) {
            list.print();
        }

        list.free();
    } else if (command[0] == 'L') {
        DoublyList list;
        list.init();
        list.load(filename);

        if (strcmp(command, "LPUSH") == 0 && argc >= 4) {
            list.push(atoi(argv[3]));
            list.save(filename);
        } else if (strcmp(command, "LDEL") == 0 && argc >= 4) {
            list.del(atoi(argv[3]));
            list.save(filename);
        } else if (strcmp(command, "LGET") == 0 && argc >= 4) {
            std::cout << list.get(atoi(argv[3])) << std::endl;
        } else if (strcmp(command, "PRINT") == 0) {
            list.print();
        }

        list.free();
    } else if (command[0] == 'Q') {
        Queue q;
        q.init();
        q.load(filename);

        if (strcmp(command, "QPUSH") == 0 && argc >= 4) {
            q.push(atoi(argv[3]));
            q.save(filename);
        } else if (strcmp(command, "QPOP") == 0) {
            int value = q.pop();
            std::cout << value << std::endl;
            q.save(filename);
        } else if (strcmp(command, "QPEEK") == 0) {
            std::cout << q.peek() << std::endl;
        } else if (strcmp(command, "PRINT") == 0) {
            q.print();
        }

        q.free();
    } else if (command[0] == 'T') {
        Tree t;
        t.init();
        t.load(filename);

        if (strcmp(command, "TINSERT") == 0 && argc >= 4) {
            t.insert(atoi(argv[3]));
            t.save(filename);
        } else if (strcmp(command, "TDEL") == 0 && argc >= 4) {
            t.del(atoi(argv[3]));
            t.save(filename);
        } else if (strcmp(command, "TGET") == 0 && argc >= 4) {
            std::cout << (t.get(atoi(argv[3])) ? "Found" : "Not found") << std::endl;
        } else if (strcmp(command, "PRINT") == 0) {
            t.print();
        }

        t.free();
    } else if (strcmp(command, "PRINT") == 0) {
        std::ifstream file(filename);
        if (file) {
            char type[20];
            file >> type;
            file.close();

            if (strcmp(type, "ARRAY") == 0) {
                Array arr;
                arr.init();
                arr.load(filename);
                arr.print();
                arr.free();
            } else if (strcmp(type, "STACK") == 0) {
                Stack s;
                s.init();
                s.load(filename);
                s.print();
                s.free();
            } else if (strcmp(type, "FORWARD") == 0) {
                ForwardList list;
                list.init();
                list.load(filename);
                list.print();
                list.free();
            } else if (strcmp(type, "DOUBLY") == 0) {
                DoublyList list;
                list.init();
                list.load(filename);
                list.print();
                list.free();
            } else if (strcmp(type, "QUEUE") == 0) {
                Queue q;
                q.init();
                q.load(filename);
                q.print();
                q.free();
            } else if (strcmp(type, "TREE") == 0) {
                Tree t;
                t.init();
                t.load(filename);
                t.print();
                t.free();
            }
        }
    }

    return 0;
}