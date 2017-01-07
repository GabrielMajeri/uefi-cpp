#pragma once

#include <cstdint>

namespace UEFI
{
	/// 64-bit value to identify tables.
	struct Signature
	{
        constexpr Signature(std::uint64_t signature)
			: value{ signature }
        {
        }

        constexpr operator std::uint64_t() const
        {
            return value;
        }

        std::uint64_t value;
	};

	constexpr bool operator==(Signature lhs, Signature rhs)
	{
		return lhs.value == rhs.value;
	}

}
