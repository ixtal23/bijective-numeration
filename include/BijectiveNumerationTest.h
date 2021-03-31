//
// Copyright © 2021 Maxim Morozov. All rights reserved.
//
// Created by Maxim Morozov on 31/03/2021.
//
// bijective-numeration
//
// BijectiveNumerationTest.h
//
// The tests of BijectiveNumeration class.
//
#pragma once

#include "BijectiveNumeration.h"
#include "DigitSet.h"
#include "uint128.h"

#include <stdexcept>

void testFailed(const std::string_view message) {
    std::cout << "ERROR: " << message << std::endl;
    throw std::runtime_error("Test failed!");
}

template<typename number_t, std::size_t stringMaxLength>
void testBijectiveNumeration(const std::string_view& digitSet, const std::string_view string) {
    using bn_t = BijectiveNumeration<number_t, stringMaxLength>;

    const bn_t bn(digitSet);

    std::cout << std::endl << "Test " << bn.description() << std::endl;

    std::cout << "initial string: size=" << string.size() << ", content='" << string << "'" <<std::endl;

    number_t number = 0;
    auto status = bn.encode(string, number);

    std::cout << "encoded number: " << number << ", status=" << static_cast<int>(status) << std::endl;

    if (status != bn_t::Status::Ok) {
        testFailed("Failed to encode: status is not ok");
        return;
    }

    std::string decodedString;
    status = bn.decode(number, decodedString);

    std::cout << "decoded string: size=" << decodedString.size() << ", content='" << decodedString << "', status=" << static_cast<int>(status) << std::endl;

    if (status != bn_t::Status::Ok) {
        testFailed("Failed to decode: status is not ok");
        return;
    }

    if (decodedString.compare(string) != 0) {
        testFailed("Failed to decode: source and decoded strings mismatch");
        return;
    }
}

template<typename number_t, std::size_t stringMaxLength>
void testBijectiveNumeration(const std::string_view& digitSet) {
    // The test case of the empty string..
    testBijectiveNumeration<number_t, stringMaxLength>(digitSet, "");

    // The test case of each character of a digit set.
    for (std::size_t i = 0; i < digitSet.size(); ++i) {
        std::string string1(1, digitSet[i]);
        std::string string2(stringMaxLength, digitSet[i]);

        testBijectiveNumeration<number_t, stringMaxLength>(digitSet, string1);
        testBijectiveNumeration<number_t, stringMaxLength>(digitSet, string2);
    }
}

void testBijectiveNumeration() {
    std::cout << std::endl << "Test Bijective Numeration" << std::endl;

    testBijectiveNumeration<std::uint64_t, 10>(DigitSet::Base10);
    testBijectiveNumeration<std::uint64_t, 10>(DigitSet::Base26);
    testBijectiveNumeration<std::uint64_t, 10>(DigitSet::Base36);

    testBijectiveNumeration<uint128_t, 10>(DigitSet::Base10);
    testBijectiveNumeration<uint128_t, 10>(DigitSet::Base26);
    testBijectiveNumeration<uint128_t, 10>(DigitSet::Base36);

    std::cout << std::endl;
}
