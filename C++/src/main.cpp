#include "array.h"
#include "linked_list.h"
#include "doubly_linked_list.h"

int main(/*int argc, char* argv[]*/) {
    auto list = DoublyLinkedList<uint64_t>();
    list.push_tail(12);
    list.push_tail(13);
    list.push_after(12, 222);
    auto helper = DoublyLinkedListHelper<uint64_t>();
    helper.save("pizdec.txt", list);
    auto list2 = DoublyLinkedList<uint64_t>();
    helper.load("pizdec.txt", &list2);
    helper.print(list2);
    return 0;
}
