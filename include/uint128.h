//
// Copyright © 2021 Maxim Morozov. All rights reserved.
//
// Created by Maxim Morozov on 31/03/2021.
//
// bijective-numeration
//
// uint128.h
//
// The support of 128 bit unsigned integer type.
//
#pragma once

#include <iostream>
#include <iomanip>
#include <limits>
#include <cstddef>

using uint128_t = __uint128_t;

std::ostream& operator<<(std::ostream& stream, const uint128_t ui128) {
    if (ui128 <= std::numeric_limits<std::uint64_t>::max()) {
        stream << static_cast<std::uint64_t>(ui128);
    } else {
        //                      UINT64_MAX = 18446744073709551615ULL
        static constexpr std::uint64_t P10 = 10000000000000000000ULL; // 19 zeroes
        static constexpr int           E10 = 19;

        const uint128_t     leading  = ui128 / P10;
        const std::uint64_t trailing = ui128 % P10;

        operator<<(stream, leading);

        const auto flags(stream.flags()); // store the flags

        stream << std::setfill('0') << std::setw(E10) << trailing;

        stream.setf(flags); // restore the flags
    }

    return stream;
}
