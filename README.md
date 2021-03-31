# bijective-numeration

The implementation of https://en.wikipedia.org/wiki/Bijective_numeration.

## Examples

```
#include "BijectiveNumeration.h"

{
    const BijectiveNumeration<std::uint64_t, 10> bn(DigitSet::Base36);
    
    const std::string_view sourceString("ABC123");

    const auto number = bn.encode(sourceString);

    const auto decodedString = bn.decode(number);
}

{
    const BijectiveNumeration<__uint128_t, 10> bn(DigitSet::Base36);

    const std::string_view sourceString("ABC123");

    const auto number = bn.encode(sourceString);

    const auto decodedString = bn.decode(number);
}
```
