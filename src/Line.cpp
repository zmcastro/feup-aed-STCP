//
// Created by zemar on 29/01/2022.
//

#include "Line.h"

Line::Line(const std::string &code, const std::string &name,  const std::vector<std::string> &stopCodes0, const std::vector<std::string> &stopCodes1, const bool &lineState) : code(code), name(name), stopCodes0(stopCodes0), stopCodes1(stopCodes1), lineState(lineState) { }