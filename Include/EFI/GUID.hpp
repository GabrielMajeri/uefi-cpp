#pragma once

#include <cstdint>

namespace EFI
{
	struct GUID
	{
		std::uint32_t data1;
		std::uint16_t data2, data3;
		std::uint8_t data4[8];
	};
}