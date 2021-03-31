//
// Copyright © 2021 Maxim Morozov. All rights reserved.
//
// Created by Maxim Morozov on 31/03/2021.
//
// bijective-numeration
//
// main.cpp
//

#include "BijectiveNumerationTest.h"

int main(int /*argc*/, const char* /*argv*/[]) {
    try {
        testBijectiveNumeration();
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
