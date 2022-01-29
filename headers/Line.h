//
// Created by zemar on 29/01/2022.
//

#ifndef AEDPROJ2_LINE_H
#define AEDPROJ2_LINE_H

#include <vector>
#include <string>

class Line {
private:
    std::string code, name;
    std::vector<std::string> stopCodes0;
    std::vector<std::string> stopCodes1;

    bool lineState; // 0 = linha noturna, 1 = diurna

public:
    Line(const std::string &code, const std::string &name, const std::vector<std::string> &stopCodes0, const std::vector<std::string> &stopCodes1, const bool &lineState);
};


#endif //AEDPROJ2_LINE_H
