#include "array.h"
#include "linked_list.h"

int main(/*int argc, char* argv[]*/) {
    auto list = LinkedList<uint64_t>();
    list.push_tail(12);
    list.push_tail(13);
    list.push_after(12, 222);
    auto helper = LinkedListHelper<uint64_t>();
    helper.save("pizdec.txt", list);
    auto list2 = LinkedList<uint64_t>();
    helper.load("pizdec.txt", &list2);
    helper.print(list2);
    return 0;
}
