#pragma once

#include <cstdint>

namespace EFI
{
	struct TableHeader
	{
		/// Unique signature to identify the table.
		std::uint64_t signature;

		/// The revision of the booting UEFI specification.
		struct { std::uint16_t minor, major; } revision;

		/// The size of the table + header, in bytes.
		std::uint32_t headerSize;

		/// CRC32 of the entire table, with this field set to 0.
		/// Type: CCITT32 CRC algorithm with the seed 0x04c11db7.
		std::uint32_t crc32;

		/// Reserved by the specification. Must be 0.
		std::uint32_t _reserved;
	};
}