#pragma once

#include "Detail/BitFlags.hpp"

namespace UEFI
{
	/// Attributes of the memory region that describe the bit mask of capabilities for that memory region.
	enum class MemoryAttribute : std::uint64_t
	{
		/// @defgroup Cacheability attributes
		/// @{
		Uncacheable = 0x1,
		WriteCombining = 0x2,
		/// Writes that hit in the cache will also be written to main memory.
		WriteThrough = 0x4,
		/// Reads and writes that hit in the cache do not propagate to main memory.
		/// Dirty data is written back to main memory when a new cache line is allocated.
		WriteBack = 0x8,
		/// Not cacheable, exported, and supports the "fetch and add" semaphore mechanism.
		UncacheableExported = 0x10,
		/// @}

		/// @defgroup Physical memory protection attributes
		/// @{
		/// This is typically used as a cacheability attribute today.
		/// The memory region supports being configured as cacheable with a "write protected" policy.
		/// Reads come from cache lines when possible, and read misses cause cache fills.
		/// Writes are propagated to the system bus and cause corresponding cache lines on all processors on the bus to be invalidated.
		WriteProtected = 0x1000,
		/// Read-protected by system hardware.
		ReadProtected = 0x2000,
		/// Protected by system hardware from executing code.
		ExecuteProtected = 0x4000,
		/// @}

		/// @defgroup Runtime memory attributes
		/// @{
		/// The memory region refers to persistent memory.
		NonVolatile = 0x8000,
		/// The memory region needs to be given a virtual mapping by the operating system when setVirtualAddressMap() is called.
		/// @see setVirtualAddressMap()
		Runtime = 0x8000000000000000,
		/// @}

		/// @defgroup Reliability attributes
		/// @{
		/// The memory region provides higher reliability relative to other memory in the system.
		/// If all memory has the same reliability, then this bit is not used.
		MoreReliable = 0x10000
		/// @}
	};

	UEFI_BIT_FLAGS(MemoryAttribute);
}
