//
// Copyright © 2021 Maxim Morozov. All rights reserved.
//
// Created by Maxim Morozov on 31/03/2021.
//
// bijective-numeration
//
// DigitSet.h
//
// The digit sets' constants.
//
#pragma once

#include <string_view>

namespace DigitSet {
    const std::string_view Base10 = "0123456789";
    const std::string_view Base26 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const std::string_view Base36 = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
}
