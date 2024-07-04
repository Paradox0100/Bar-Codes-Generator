#include "code39.h"
#include <iostream>
#include <string>
#include "code39.h"

int main(int argc, char* argv[]) {
    if (argc > 2) {
        std::string input = "1412510038";
        Code39Standard(argv[1], argv[2]);
    } else {
        std::cerr << "Invalid command line arguments\n";
    }
    return 0;
}