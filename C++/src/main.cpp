#include "array.h"

int main(/*int argc, char* argv[]*/) {
    Array<uint64_t> array1 = Array<uint64_t>(1);
    array1.push_back(12);
    array1.push_back(24);
    ArrayHelper<uint64_t> helper;
    helper.save("pizdec.txt", array1);

    Array<uint64_t> array2;
    helper.load("pizdec.txt", &array2);

    helper.print(array2);

    const auto array3 = array2;
    helper.print(array2);
    helper.print(array3);
    return 0;
}
