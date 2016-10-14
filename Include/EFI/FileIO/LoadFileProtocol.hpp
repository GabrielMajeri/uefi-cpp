#pragma once

#include <EFI/Status.hpp>
#include <EFI/DevicePathProtocol.hpp>

namespace EFI
{
	struct LoadFileProtocol
	{
		Status(*loadFile)(LoadFileProtocol*, DevicePathProtocol* filePath, bool bootPolicy, std::uint64_t* bufferSize, void* buffer);
	};
}