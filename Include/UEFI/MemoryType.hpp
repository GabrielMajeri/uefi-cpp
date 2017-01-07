#pragma once

#include <cstdint>

namespace UEFI
{
	/// The type of memory to allocate.
	/// Normal allocations (that is, allocations by any UEFI application) are of type LoaderData.
	/// Values in the range 0x70000000..0x7FFFFFFF are reserved for OEM use.
	/// Values in the range 0x80000000..0xFFFFFFFF are reserved for use by UEFI OS loaders.
	enum class MemoryType : std::uint32_t
	{
		/// Memory reserved by the firmware / hardware, such as by SMM or ACPI.
		/// Not usable by applications or drivers.
		ReservedMemory = 0,

		/// The code portions of a loaded UEFI application.
		LoaderCode = 1,
		/// The data portions of a loaded UEFI application and the default data allocation type
		/// used by a UEFI application to allocate pool memory.
		LoaderData = 2,

		/// @defgroup Boot services memory
		/// After calling exitBootServices(), this memory is free to use.
		/// @{
		/// The code portions of a loaded UEFI Boot Service Driver.
		BootServicesCode = 3,
		///The data portions of a loaded UEFI Boot Service Driver, and the default data allocation type
		/// used by a UEFI Boot Service Driver to allocate pool memory.
		BootServicesData = 4,
		/// @}

		/// The code portions of a loaded UEFI Runtime Driver.
		RuntimeServicesCode = 5,
		/// The data portions of a loaded UEFI Runtime Driver and the default data allocation type used by a UEFI Runtime Driver to allocate pool memory.
		RuntimeServicesData = 6,

		/// Free (unallocated) memory.
		ConventionalMemory = 7,
		/// Memory in which errors have been detected.
		UnusableMemory = 8,

		/// Memory that holds the ACPI tables.
		ACPIReclaimMemory = 9,
		/// Address space reserved for use by the firmware.
		ACPIMemoryNVS = 10,

		/// Used by system firmware to request that a memory-mapped IO region be mapped by the OS to a virtual address,
		/// so it can be accessed by EFI runtime services.
		MemoryMappedIO = 11,
		/// System memory-mapped IO region that is used to translate memory cycles to IO cycles by the processor.
		MemoryMappedIOPortSpace = 12,

		/// Address space reserved by the firmware for code that is part of the processor.
		PalCode = 13,

		/// A memory region that operates as ConventionalMemory.
		/// However, it happens to also support byte-addressable non-volatility.
		PersistentMemory = 14,

		MaxMemoryType = 15
	};

	/// Checks if the given memory type is OEM allocated memory.
	/// @param type The given type to check.
	/// @return Whether the given type is OEM-reserved or not.
	constexpr bool isMemoryTypeOEM(MemoryType type) noexcept
	{
		auto value = static_cast<std::uint32_t>(type);
		return (0x70000000 <= value) && (value <= 0x7FFFFFFF);
	}
}
