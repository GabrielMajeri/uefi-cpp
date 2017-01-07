#pragma once

namespace UEFI
{
	struct MemoryMap
	{
		/// The size in bytes.
		std::size_t size;

		/// Size in bytes of each descriptor.
		/// The firmware is allowed to have extra information at the end of the descriptor,
		/// but it's backwards compatible.
		std::size_t sizeOfEntry;

		/// The current key. This is used by the firmware to determine if the map is current or not.
		/// Use this when calling exitBootServices().
		std::size_t currentKey;

		/// Pointer to an array of memory descriptors.
		/// Note: use operator[] to access these. They might not have the size of the structure.
		BootServices::MemoryDescriptor* descriptors;

		/// Number of descriptors in the array.
		std::size_t getNumberOfEntries() const noexcept
		{
			return size / sizeOfEntry;
		}

		/// Accesses a memory region in the map.
		/// @param i The index of the region.
		/// @return The descriptor at that point.
		const BootServices::MemoryDescriptor& operator[](std::size_t i) const noexcept
		{
			return *reinterpret_cast<const BootServices::MemoryDescriptor*>(reinterpret_cast<const std::uint8_t*>(descriptors) + (i * sizeOfEntry));
		}
	};

	/// This function will retrieve the memory map. It determines how much memory is needed,
	/// asks UEFI to allocate a buffer,
	/// @param bootServices The boot services table.
	/// @return The memory map at the current time.
	/// @return The map will have size 0 if it fails.
	MemoryMap getMemoryMap(BootServices& bootServices);
}
