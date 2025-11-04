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

    if (std::strcmp(command, "PRINT") && argc >= 4 && !contains_only_digits(argv[3])) {
        std::cerr << "Argument contains a non-number character" << std::endl;
        return 1;
    }

    if (command[0] == 'M') {
        Array arr;
        arr.init();
        arr.load(filename);

        if (std::strcmp(command, "MPUSH") == 0 && argc >= 4) {
            arr.push(atoi(argv[3]));
            arr.save(filename);
        } else if (std::strcmp(command, "MDEL") == 0 && argc >= 4) {
            arr.del(atoi(argv[3]));
            arr.save(filename);
        } else if (std::strcmp(command, "MGET") == 0 && argc >= 4) {
            std::cout << arr.get(atoi(argv[3])) << std::endl;
        } else if (std::strcmp(command, "PRINT") == 0) {
            arr.print();
        }

        arr.free();
    } else if (command[0] == 'S') {
        Stack s;
        s.init();
        s.load(filename);

        if (std::strcmp(command, "SPUSH") == 0 && argc >= 4) {
            s.push(atoi(argv[3]));
            s.save(filename);
        } else if (std::strcmp(command, "SPOP") == 0) {
            int value = s.pop();
            std::cout << value << std::endl;
            s.save(filename);
        } else if (std::strcmp(command, "SPEEK") == 0) {
            std::cout << s.peek() << std::endl;
        } else if (std::strcmp(command, "PRINT") == 0) {
            s.print();
        }

        s.free();
    } else if (command[0] == 'F') {
        ForwardList list;
        list.init();
        list.load(filename);

        if (std::strcmp(command, "FPUSH_FRONT") == 0 && argc >= 4) {
            list.push_front(atoi(argv[3]));
            list.save(filename);
        } else if (std::strcmp(command, "FPUSH_BACK") == 0 && argc >= 4) {
            list.push_back(atoi(argv[3]));
            list.save(filename);
        } else if (std::strcmp(command, "FDEL_FIRST") == 0) {
            list.del_first();
            list.save(filename);
        } else if (std::strcmp(command, "FDEL_LAST") == 0) {
            list.del_last();
            list.save(filename);
        } else if (std::strcmp(command, "FDEL_PREV") == 0 && argc >= 4) {
            list.del_prev(atoi(argv[3]));
            list.save(filename);
        } else if (std::strcmp(command, "FDEL_AT") == 0 && argc >= 4) {
            list.del_at(atoi(argv[3]));
            list.save(filename);
        } else if (std::strcmp(command, "FDEL_NEXT") == 0 && argc >= 4) {
            list.del_next(atoi(argv[3]));
            list.save(filename);
        } else if (std::strcmp(command, "FINSERT_PREV") == 0 && argc >= 5) {
            list.insert_prev(atoi(argv[3]), atoi(argv[4]));
            list.save(filename);
        } else if (std::strcmp(command, "FINSERT_NEXT") == 0 && argc >= 5) {
            list.insert_next(atoi(argv[3]), atoi(argv[4]));
            list.save(filename);
        } else if (std::strcmp(command, "FGET") == 0 && argc >= 4) {
            std::cout << list.get(atoi(argv[3])) << std::endl;
        } else if (std::strcmp(command, "PRINT") == 0) {
            list.print();
        }

        list.free();
    } else if (command[0] == 'L') {
        DoublyList list;
        list.init();
        list.load(filename);

        if (std::strcmp(command, "LPUSH_BACK") == 0 && argc >= 4) {
            list.push_back(atoi(argv[3]));
            list.save(filename);
        } else if (std::strcmp(command, "LPUSH_FRONT") == 0 && argc >= 4) {
            list.push_front(atoi(argv[3]));
            list.save(filename);
        } else if (std::strcmp(command, "LDEL_FIRST") == 0) {
            list.del_first();
            list.save(filename);
        } else if (std::strcmp(command, "LDEL_LAST") == 0) {
            list.del_last();
            list.save(filename);
        } else if (std::strcmp(command, "LDEL_PREV") == 0 && argc >= 4) {
            list.del_prev(atoi(argv[3]));
            list.save(filename);
        } else if (std::strcmp(command, "LDEL_AT") == 0 && argc >= 4) {
            list.del_at(atoi(argv[3]));
            list.save(filename);
        } else if (std::strcmp(command, "LDEL_NEXT") == 0 && argc >= 4) {
            list.del_next(atoi(argv[3]));
            list.save(filename);
        } else if (std::strcmp(command, "LINSERT_PREV") == 0 && argc >= 5) {
            list.insert_prev(atoi(argv[3]), atoi(argv[4]));
            list.save(filename);
        } else if (std::strcmp(command, "LINSERT_NEXT") == 0 && argc >= 5) {
            list.insert_next(atoi(argv[3]), atoi(argv[4]));
            list.save(filename);
        } else if (std::strcmp(command, "LGET") == 0 && argc >= 4) {
            std::cout << list.get(atoi(argv[3])) << std::endl;
        } else if (std::strcmp(command, "PRINT") == 0) {
            list.print();
        }

        list.free();
    } else if (command[0] == 'Q') {
        Queue q;
        q.init();
        q.load(filename);

        if (std::strcmp(command, "QPUSH") == 0 && argc >= 4) {
            q.push(atoi(argv[3]));
            q.save(filename);
        } else if (std::strcmp(command, "QPOP") == 0) {
            int value = q.pop();
            std::cout << value << std::endl;
            q.save(filename);
        } else if (std::strcmp(command, "QPEEK") == 0) {
            std::cout << q.peek() << std::endl;
        } else if (std::strcmp(command, "PRINT") == 0) {
            q.print();
        }

        q.free();
    } else if (command[0] == 'T') {
        Tree t;
        t.init();
        t.load(filename);

        if (std::strcmp(command, "TINSERT") == 0 && argc >= 4) {
            t.insert(atoi(argv[3]));
            t.save(filename);
        } else if (std::strcmp(command, "TDEL") == 0 && argc >= 4) {
            t.del(atoi(argv[3]));
            t.save(filename);
        } else if (std::strcmp(command, "TGET") == 0 && argc >= 4) {
            std::cout << (t.get(atoi(argv[3])) ? "Found" : "Not found") << std::endl;
        } else if (std::strcmp(command, "PRINT") == 0) {
            t.print();
        }

        t.free();
    } else if (std::strcmp(command, "PRINT") == 0) {
        std::ifstream file(filename);
        if (file) {
            char type[20];
            file >> type;
            file.close();

            if (std::strcmp(type, "ARRAY") == 0) {
                Array arr;
                arr.init();
                arr.load(filename);
                arr.print();
                arr.free();
            } else if (std::strcmp(type, "STACK") == 0) {
                Stack s;
                s.init();
                s.load(filename);
                s.print();
                s.free();
            } else if (std::strcmp(type, "FORWARD") == 0) {
                ForwardList list;
                list.init();
                list.load(filename);
                list.print();
                list.free();
            } else if (std::strcmp(type, "DOUBLY") == 0) {
                DoublyList list;
                list.init();
                list.load(filename);
                list.print();
                list.free();
            } else if (std::strcmp(type, "QUEUE") == 0) {
                Queue q;
                q.init();
                q.load(filename);
                q.print();
                q.free();
            } else if (std::strcmp(type, "TREE") == 0) {
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
