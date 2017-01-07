#pragma once

#include <cstdint>
#include <cstddef>

namespace UEFI
{
	/// UEFI uses a standard CCITT32 CRC algorithm with a seed polynomial value of 0x04C11DB7 for its CRC calculations.
	using CRC32 = std::uint32_t;

	// The following functions are defined in the CRC32.inl file. Include it in your sources.

	struct Table;

	/// Verifies an UEFI table's integrity.
	/// @param table The table to check.
	/// @return True if the table's specified CRC value matches the table's specified CRC.
	bool doesCRC32Match(Table& table) noexcept;

	/// Calculates the CRC32 of an UEFI table.
	/// @param table The table to calculate.
	/// @return The CRC of the table.
	CRC32 calculateCRC32(Table& table) noexcept;

	/// Algorithm to calculate CCITT32 for a UEFI structure.
	/// @param data Pointer to the start of the structure.
	/// @param size The size in bytes of the structure.
	/// @return The calculated CRC32.
	CRC32 calculateCRC32(const void* data, std::size_t size) noexcept;
}
