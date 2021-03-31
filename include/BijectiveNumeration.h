//
// Copyright © 2021 Maxim Morozov. All rights reserved.
//
// Created by Maxim Morozov on 31/03/2021.
//
// bijective-numeration
//
// BijectiveNumeration.h
//
// The implementation of https://en.wikipedia.org/wiki/Bijective_numeration.
//
#pragma once

#include <type_traits>
#include <string_view>
#include <string>
#include <array>
#include <sstream>
#include <iostream>
#include <utility>
#include <cstddef>

template<typename T, std::size_t M>
class BijectiveNumeration {
public:
    static_assert(std::is_unsigned<T>::value);

    using number_t = T;
    static constexpr std::size_t STRING_MAX_LENGTH = M;
    using base_powers_t = std::array<number_t, STRING_MAX_LENGTH>;

    enum class Status {
        Ok,
        StringIsTooLong,
        OutOfDigitSet
    };

    BijectiveNumeration() = delete;

    BijectiveNumeration(const std::string_view digitSet_) noexcept :
        digitSet(digitSet_),
        base(digitSet.length()),
        basePowers(computeBasePowers()) {
    }

    ~BijectiveNumeration() = default;

    std::string description() const {
        std::ostringstream stream;
        stream
            << "BijectiveNumeration: sizeof(number_t)=" << sizeof(number_t)
            << ", stringMaxLength=" << STRING_MAX_LENGTH
            << ", base=" << base
            << ", digitSet=" << digitSet;
        
        return stream.str();
    }

    Status encode(const std::string_view string, number_t& result) const noexcept {
        if (string.length() > STRING_MAX_LENGTH) {
            return Status::StringIsTooLong;
        }

        result = 0;

        std::size_t digitPosition = 0;

        for (auto digitCharacter = string.crbegin(), end = string.crend(); digitCharacter != end; ++digitCharacter, ++digitPosition) {
            const auto digitCharacterPosition = digitSet.find(*digitCharacter);
            if (digitCharacterPosition == std::string_view::npos) {
                return Status::OutOfDigitSet;
            }

            const auto digitOrdinal = digitCharacterPosition + 1;

            result += digitOrdinal * basePowers[digitPosition];
        }

        return Status::Ok;
    }

    Status decode(const number_t number, std::string& result) const noexcept {
        std::string reverseResult;
        reverseResult.reserve(STRING_MAX_LENGTH);

        auto qn_1 = number;
        
        while (qn_1 != 0) {
            const auto qn = ceilDiv(qn_1, base) - 1;

            const auto digitOrdinal = qn_1 - qn * base;
            
            const auto digitCharacterPosition = static_cast<std::size_t>(digitOrdinal - 1);
            if (digitCharacterPosition >= digitSet.size()) {
                return Status::OutOfDigitSet;
            }

            reverseResult += digitSet[digitCharacterPosition];

            qn_1 = qn;
        }

        result.assign(reverseResult.rbegin(), reverseResult.rend());

        return Status::Ok;
    }

private:
    base_powers_t computeBasePowers() const noexcept {
        base_powers_t result{0};

        for (std::size_t exponent = 0; exponent < result.size(); ++exponent) {
            result[exponent] = power(base, exponent);
        }

        return result;
    }

    static number_t power(number_t base, std::size_t exponent) noexcept {
        number_t result = 1;

        while (exponent > 0) {
            if (exponent & 1) {
                result *= base;
            }

            exponent >>= 1;
            if (exponent > 0) {
                base *= base;
            }
        }

        return result;
    }

    static number_t ceilDiv(const number_t x, const std::size_t y) noexcept {
        // The not optimized implementation:
        // return static_cast<number_t>(std::ceil(x / static_cast<double>(y)));

        // The optimized implementation:
        // https://stackoverflow.com/questions/2745074/fast-ceiling-of-an-integer-division-in-c-c
        return 1 + ((x - 1) / y);
    }

private:
    const std::string_view digitSet;
    const std::size_t base;
    const base_powers_t basePowers;
};
