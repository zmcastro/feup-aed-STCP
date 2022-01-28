//
// Created by zemar on 28/01/2022.
//


#define INFstream (std::numeric_limits<std::streamsize>::max()/2)

#include <iostream>
#include <limits>

using namespace::std;

void cleanScreen()
{
    std::cout << std::string(10, '\n');
}

bool inpCheck(int& x)
{
    int n;

    if (std::cin >> n && std::cin.peek() == '\n') {
        x = n;
        std::cin.ignore(INFstream, '\n');
        return true;
    }

    else if (std::cin.fail() && std::cin.eof()){
        exit(0);
    }
    else {
        std::cin.ignore(INFstream, '\n');
        cin.clear();
        return false;
    }
}

