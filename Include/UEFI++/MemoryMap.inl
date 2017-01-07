#pragma once

namespace UEFI
{
	MemoryMap getMemoryMap(BootServices& bootServices)
	{
		// Get the memory map.
		BootServices::MemoryDescriptor* memoryMap = nullptr;

		std::size_t mapSize = 0, key, descriptorSize;
		std::uint32_t descriptorVersion;

		// Try getting the memory map.
		// No point in checking the status, since we know it will fail, because size is 0.
		bootServices.getMemoryMap(mapSize, memoryMap, key, descriptorSize, descriptorVersion);

		// Allocating from the pool (might) add some extra descriptors.
		// TODO: is this extra enough?
		mapSize += 4 * descriptorSize;

		// Now we know the needed size in mapSize.
		const auto status = bootServices.allocatePool(MemoryType::LoaderData, mapSize, reinterpret_cast<void**>(&memoryMap));

		// This could fail if there's not enough memory left.
		if (status != Status::Success)
			return{ };

		// This cannot fail: we have allocated more than enough memory, and the buffer is not nullptr.
		bootServices.getMemoryMap(mapSize, memoryMap, key, descriptorSize, descriptorVersion);

		return{ mapSize, descriptorSize, key, memoryMap };
	}
}
