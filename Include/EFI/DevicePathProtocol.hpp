#pragma once

#include <cstdint>

namespace EFI
{
	struct DevicePathProtocol
	{
		enum Type : std::uint8_t
		{
			HardwareDevicePath = 1,
			ACPIDevicePath = 2,
			MessagingDevicePath = 3,
			MediaDevicePath = 4,
			BIOSBootSpecificationDevicePath = 5,
			EndOfHardwareDevicePath = 127
		};

		std::uint8_t type;
		std::uint8_t subType;
		std::uint8_t length[2];
	};
}