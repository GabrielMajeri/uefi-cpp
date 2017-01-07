#pragma once

#include <cstdint>

namespace UEFI
{
	/// Generates bit operators for a given enum.
	/// @hideinitializer
	#define UEFI_BIT_FLAGS(E) \
	inline constexpr auto operator|(E lhs, E rhs) \
	{ \
		return static_cast<E>(static_cast<std::uint64_t>(lhs) | static_cast<std::uint64_t>(rhs));\
	} \
	inline auto operator|=(E& lhs, E rhs) \
	{ \
		reinterpret_cast<std::uint64_t&>(lhs) |= static_cast<std::uint64_t>(rhs);\
		return lhs; \
	} \
	inline constexpr auto operator&(E lhs, E rhs) \
	{ \
		return static_cast<E>(static_cast<std::uint64_t>(lhs) & static_cast<std::uint64_t>(rhs));\
	} \
	inline auto operator&=(E& lhs, E rhs) \
	{ \
		reinterpret_cast<std::uint64_t&>(lhs) &= static_cast<std::uint64_t>(rhs);\
		return lhs; \
	} \
	inline constexpr auto operator~(E lhs) \
	{ \
		return static_cast<E>(~static_cast<std::uint64_t>(lhs));\
	}
}
