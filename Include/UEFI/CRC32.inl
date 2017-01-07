#pragma once

namespace UEFI
{
	bool doesCRC32Match(Table& table) noexcept
	{
        return table.header.crc32 == calculateCRC32(table);
	}

    CRC32 calculateCRC32(Table& table) noexcept
	{
		// CRC must be set to 0 before calculating.
		const auto copyCRC = table.header.crc32;

		table.header.crc32 = 0;

		const auto result = calculateCRC32(&table, table.header.size);

		// Reset the original CRC.
		table.header.crc32 = copyCRC;

		return result;
    }

	// Original: http://stackoverflow.com/a/26051190
	// Adapted the original to C++ and turned table generator into a constexpr function.
	CRC32 calculateCRC32(const void* data, std::size_t size) noexcept
	{
		constexpr static struct CRC32Table
		{
			std::uint32_t data[256] { };

			constexpr CRC32Table()
			{
				// 0xEDB88320 is 0x04C11DB7 but with changed endianess.
				constexpr std::uint32_t polynomial = 0xEDB88320;

				for(std::uint32_t i = 0; i < 256; ++i)
				{
					std::uint32_t remainder = i;

					for (std::uint32_t bit = 8; bit > 0; --bit)
						if (remainder & 1)
							remainder = (remainder >> 1) ^ polynomial;
						else
							remainder = (remainder >> 1);

					data[i] = remainder;
				}
			}

			std::uint32_t operator[](std::uint8_t i) const
			{
				return data[i];
			}

		} crcTable;

		CRC32 crc = 0xFF'FF'FF'FF;

		// Pointer to go through the data.
		auto ptr = reinterpret_cast<const std::uint8_t*>(data);

		for(std::size_t i = 0; i < size; ++i, ++ptr)
			crc = crcTable[*ptr ^ (crc & 0xFF)] ^ (crc >> 8);

		return ~crc;
	}
}
