//
// Created by mroch on 28/01/2022.
//
void cleanScreen()
{
    std::cout << std::string(10, '\n');
}
bool inpCheck(int& x)
{
    int n;

    if (cin >> n && cin.peek() == '\n') {
        x = n;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return true;
    }

    else if (cin.fail() && cin.eof()){
        exit(0);
    }
    else {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cin.clear();
        return false;
    }
}

