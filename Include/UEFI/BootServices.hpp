#pragma once

#include "SignedTable.hpp"
#include "Status.hpp"
#include "GUID.hpp"
#include "Handle.hpp"
#include "Detail/BitFlags.hpp"

#include "TaskPriorityLevel.hpp"
#include "MemoryAttribute.hpp"
#include "MemoryType.hpp"

namespace UEFI
{
	class BootServices : public SignedTable<0x56524553544f4f42>
	{
	public:
		/// @defgroup Task Priority Services
		/// @{
		/// Raises a task’s priority level and returns its previous level.
		/// @param newTpl The new level to raise to.
		/// @return The old level.
		TPL raiseTPL(TPL newTpl)
		{
			return _raiseTpl(newTpl);
		}

		void restoreTPL(TPL oldTpl)
		{
			_restoreTpl(oldTpl);
		}
		/// @}


		// Memory Services

		enum class AllocateType
		{
			/// Any available range of pages that satisfies the request.
			AnyPages,
			/// Any available range of pages whose uppermost address is less than or equal to the address pointed to by the input.
			MaxAddress,
			/// Allocate pages at the address pointed to by the input.
			Address,

			MaxAllocateType
		};

		using PhysicalAddress = std::uint64_t;
		using VirtualAddress = std::uint64_t;

		/// Allocates memory pages from the system.
		/// @return Success The requested pages were allocated.
		/// @return OutOfResources The pages could not be allocated.
		/// @return InvalidParameter Type is not a valid enum value.
		/// @return InvalidParameter MemoryType is in the range MaxMemoryType ... 0x6FFFFFFF.
		/// @return InvalidParameter MemoryType is PersistentMemory.
		/// @return NotFound The requested pages could not be found
		Status allocatePages(AllocateType type, MemoryType memType, std::size_t pages, PhysicalAddress& memory)
		{
			return _allocatePages(type, memType, pages, memory);
		}

		Status freePages(PhysicalAddress memory, std::size_t pages)
		{
			return _freePages(memory, pages);
		}

		/// Describes a region of memory.
		/// Note: firmware is free to have memory descriptors of different sizes. This structure can and will have extra
		/// variables at the end. Therefore, you should remember to check and use descriptorSize.
		struct MemoryDescriptor
		{
			MemoryType type; // 4

			/// BUG: I added this after seeing it in the EDK source, it seems to be necessary.
			std::uint32_t pad; // 4

			PhysicalAddress physicalStart; // 8
			VirtualAddress virtualStart; // 8

			std::uint64_t numberOfPages; // 8
			MemoryAttribute attribute; // 8
		};

		static_assert(sizeof(MemoryDescriptor) == 40);

		/// Returns the current memory map.
		/// @param[in,out] mapSize The size, in bytes, of the memoryMap buffer.
		/// On output, it is the size of the buffer returned by the firmware if the buffer was large enough,
		/// or the size of the buffer needed to contain the map if the buffer was too small.
		/// @param[in,out] memoryMap An array of MemoryDescriptors in which the firmware places the current memory map.
		/// @param[out] mapKey The location in which firmware returns the key for the current memory map.
		/// @param[out] descriptorSize The size, in bytes, of a MemoryDescriptor.
		/// @param[out] descriptorVersion The version number associated with the MemoryDescriptor.
		/// @return Success The memory map was returned in the buffer.
		/// @return BufferTooSmall The buffer was too small. The current buffer size needed to hold the memory map is returned in mapSize.
		/// @return InvalidParameter The buffer is nullptr.
		Status getMemoryMap(std::size_t& mapSize, MemoryDescriptor* memoryMap, std::size_t& mapKey, std::size_t& descriptorSize, std::uint32_t& descriptorVersion)
		{
			return _getMemoryMap(mapSize, memoryMap, mapKey, descriptorSize, descriptorVersion);
		}

		Status allocatePool(MemoryType poolType, std::size_t size, void** buffer)
		{
			return _allocatePool(poolType, size, buffer);
		}

		/// Returns pool memory to the system.
		Status freePool(void* buffer)
		{
			return _freePool(buffer);
		}

		//
		// Event & Timer Services
		//
		// EFI_CREATE_EVENT CreateEvent;
		// EFI_SET_TIMER SetTimer;
		// EFI_WAIT_FOR_EVENT WaitForEvent;
		// EFI_SIGNAL_EVENT SignalEvent;
		// EFI_CLOSE_EVENT CloseEvent;
		// EFI_CHECK_EVENT CheckEvent;

		//
		// Protocol Handler Services
		//
		// EFI_INSTALL_PROTOCOL_INTERFACE InstallProtocolInterface;
		// EFI_REINSTALL_PROTOCOL_INTERFACE ReinstallProtocolInterface;
		// EFI_UNINSTALL_PROTOCOL_INTERFACE UninstallProtocolInterface;

		/// Queries a handle to determine if it supports a specified protocol.
		/// @param[out] interface Pointer to the interface, or nullptr if handle does not support the interface.
		//[[deprecated("As of UEFI 1.10 you should use openProtocol()")]]
		Status handleProtocol(Handle handle, const GUID& protocol, void** interface)
		{
			return _handleProtocol(handle, protocol, interface);
		}

		// EFI_REGISTER_PROTOCOL_NOTIFY RegisterProtocolNotify;
		// EFI_LOCATE_HANDLE LocateHandle;
		// EFI_LOCATE_DEVICE_PATH LocateDevicePath;
		// EFI_INSTALL_CONFIGURATION_TABLE InstallConfigurationTable;

		//
		// Image Services
		//
		// EFI_IMAGE_LOAD LoadImage;
		// EFI_IMAGE_START StartImage;
		// EFI_EXIT Exit;
		// EFI_IMAGE_UNLOAD UnloadImage;
		/// Terminates all boot services.
		Status exitBootServices(Handle imageHandle, std::size_t mapKey)
		{
			return _exitBootServices(imageHandle, mapKey);
		}

		//
		// Miscellaneous Services
		//
		// EFI_GET_NEXT_MONOTONIC_COUNT GetNextMonotonicCount;
		// EFI_STALL Stall;
		// EFI_SET_WATCHDOG_TIMER SetWatchdogTimer;

		// --> These only exist in UEFI 1.1+

		//
		// DriverSupport Services
		//
		// EFI_CONNECT_CONTROLLER ConnectController;
		// EFI_DISCONNECT_CONTROLLER DisconnectController;

		//
		// Open and Close Protocol Services
		//

		enum class OpenProtocolAttributes
		{
			ByHandleProtocol = 1,
			GetProtocol = 2,
			TestProtocol = 4,
			ByChildController = 8,
			ByDriver = 16,
			Exclusive = 32
		};

		/// Queries a handle to determine if it supports a specified protocol.
		/// If the protocol is supported by the handle, it opens the protocol on behalf of the calling agent.
		Status openProtocol(Handle handle, const GUID& protocolGuid, void** interface, Handle agent, Handle controller, OpenProtocolAttributes attributes)
		{
			return _openProtocol(handle, protocolGuid, interface, agent, controller, attributes);
		}

		// EFI_CLOSE_PROTOCOL CloseProtocol;
		// EFI_OPEN_PROTOCOL_INFORMATION OpenProtocolInformation;

		//
		// Library Services
		//
		// EFI_PROTOCOLS_PER_HANDLE ProtocolsPerHandle;
		enum class LocateSearchType
		{
			AllHandles,
			ByRegisterNotify,
			ByProtocol
		};

		Status locateHandleBuffer(LocateSearchType searchType, const GUID* protocol, const void* searchKey, std::size_t& nrOfHandles, Handle*& buffer)
		{
			return _locateHandleBuffer(searchType, protocol, searchKey, nrOfHandles, buffer);
		}

		// EFI_LOCATE_PROTOCOL LocateProtocol;

		// EFI_INSTALL_MULTIPLE_PROTOCOL_INTERFACES InstallMultipleProtocolInterfaces;
		// EFI_UNINSTALL_MULTIPLE_PROTOCOL_INTERFACES UninstallMultipleProtocolInterfaces;

		//
		// 32-bit CRC Services
		//
		// EFI_CALCULATE_CRC32 CalculateCrc32;

		//
		// Miscellaneous Services

		/// Copies the contents of one buffer to another buffer.
		void copyMem(void* destination, const void* source, std::size_t length)
		{
			return _copyMem(destination, source, length);
		}

		/// Fills a buffer with a specified value.
		/// @param buffer Pointer to the buffer to fill.
		/// @param size Number of bytes in buffer to fill.
		/// @param value Value to fill buffer with.
		void setMem(void* buffer, std::size_t size, std::uint8_t value)
		{
			return _setMem(buffer, size, value);
		}

		// UEFI 2.0+
		// EFI_CREATE_EVENT_EX CreateEventEx;

	private:
		// Function pointers

		TPL (*_raiseTpl)(TPL);
		void (*_restoreTpl)(TPL);


		Status (*_allocatePages)(AllocateType, MemoryType, std::size_t, PhysicalAddress&);
		Status (*_freePages)(PhysicalAddress, std::size_t);

		Status (*_getMemoryMap)(std::size_t&, MemoryDescriptor*, std::size_t&, std::size_t&, std::uint32_t&);

		Status (*_allocatePool)(MemoryType, std::size_t, void**);
		Status (*_freePool)(void*);

		[[maybe_unused]] void* buf2[9];

		Status (*_handleProtocol)(Handle, const GUID&, void**);
		[[maybe_unused]] void* _reserved;

		[[maybe_unused]] void* bufX[8];

		Status (*_exitBootServices)(Handle, std::size_t);

		[[maybe_unused]] void* buf3[5];

		Status (*_openProtocol)(Handle, const GUID&, void**, Handle, Handle, OpenProtocolAttributes);

		[[maybe_unused]] void* buf4[3];

		Status (*_locateHandleBuffer)(LocateSearchType searchType, const GUID* protocol, const void* searchKey, std::size_t& nrOfHandles, Handle*& buffer);

		[[maybe_unused]] void* buf5[4];

		void (*_copyMem)(void*, const void*, std::size_t);
		void (*_setMem)(void*, std::size_t, std::uint8_t);

		[[maybe_unused]] void* buf6[1];
	};

	UEFI_BIT_FLAGS(BootServices::OpenProtocolAttributes);
}
