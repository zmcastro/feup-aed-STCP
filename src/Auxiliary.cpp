//
// Created by zemar on 28/01/2022.
//

#include <iostream>
#include <limits>

#include "../headers/Auxiliary.h"

void cleanScreen() {
    std::cout << std::string(10, '\n');
}

bool inpCheck(int& x) {
    int n;
    if (std::cin >> n && std::cin.peek() == '\n') {
        x = n;
        std::cin.ignore(10000, '\n');
        return true;
    }

    else if (std::cin.fail() && std::cin.eof()){
        exit(0);
    }
    else {
        std::cin.ignore(10000, '\n');
        std::cin.clear();
        return false;
    }
}

