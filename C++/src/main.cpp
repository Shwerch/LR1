#include "array.h"
#include "linked_list.h"
#include "doubly_linked_list.h"
#include "stack.h"
#include "queue.h"
#include "full_binary_tree.h"

int main(/*int argc, char* argv[]*/) {
    auto fbt = FullBinaryTree<uint64_t>();
    for (int i = 0; i < 20; i++) {
        fbt.insert(i);
    }
    FullBinaryTreeHelper<uint64_t> helper;
    helper.save(".txt", fbt);
    FullBinaryTree<uint64_t> fbt2;
    helper.load(".txt", &fbt2);
    helper.print(fbt2);
    return 0;
}
