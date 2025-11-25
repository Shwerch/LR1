#include "array.h"

int main(/*int argc, char* argv[]*/) {
    Array<uint64_t> lol = Array<uint64_t>(1);
    lol.push_back(12);
    lol.push_back(24);
    ArrayHelper<uint64_t> lol2;
    lol2.save("pizdec.txt", lol);

    Array<uint64_t> lol1;
    lol2.load("pizdec.txt", &lol1);

    lol2.print(lol1);
    return 0;
}
