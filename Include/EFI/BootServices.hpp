#pragma once

#include <EFI/TableHeader.hpp>
#include <EFI/Status.hpp>
#include <EFI/Handle.hpp>
#include <EFI/GUID.hpp>
#include <EFI/InterfaceType.hpp>

namespace EFI
{
	struct BootServices
	{
		TableHeader header;
		static constexpr auto signature{ 0x56524553544f4f42ull };

		/// Task priority services.

		enum class TPL : std::uint64_t
		{
			Application = 4,
			Callback = 8,
			Notify = 16,
			HighLevel = 31
		};

		TPL(*raiseTPL)(TPL newTPL);
		void(*restoreTPL)(TPL oldTPL);

		/// Memory services.

		enum class AllocateType
		{
			AllocateAnyPages,
			AllocateMaxAddress,
			AllocateAddress,
			MaxAllocateType
		};

		enum class MemoryType 
		{
			ReservedMemoryType,
			LoaderCode,
			LoaderData,
			BootServicesCode,
			BootServicesData,
			RuntimeServicesCode,
			RuntimeServicesData,
			ConventionalMemory,
			UnusableMemory,
			ACPIReclaimMemory,
			ACPIMemoryNVS,
			MemoryMappedIO,
			MemoryMappedIOPortSpace,
			PALCode,
			PersistentMemory,
			MaxMemoryType
		};
		
		Status(*allocatePages)(AllocateType type, MemoryType memoryType, std::uint64_t pages, std::uintptr_t* memory);
		Status(*freePages)(std::uintptr_t memory, std::uint64_t pages);
		void* getMemoryMap;
		void* allocatePool;
		void* freePool;

		void* createEvent;
		void* setTimer;
		void* waitForEvent;
		void* signalEvent;
		void* closeEvent;
		void* checkEvent;

		void* installProtocolInterface;
		void* reinstallProtocolInterface;
		void* uninstallProtocolInterface;
		void* handleProtocol;

		void* _reserved;

		void* registerProtocolNotify;
		void* locateHandle;
		void* locateDevicePath;
		void* installConfigurationTable;

		/// Image services.
		void* loadImage;
		void* startImage;
		void* exit;
		void* unloadImage;
		Status(*exitBootServices)(Handle imageHandle, std::uint64_t mapKey);

		/// Time services.
		Status(*getNextMonotonicCount)(std::uint64_t* count);
		Status(*stall)(std::uint64_t microseconds);
		Status(*setWatchdogTimer)(std::uint64_t timeout, std::uint64_t watchdogCode, std::uint64_t dataSize, char16_t* watchdogData);

		void* connectController;
		void* disconnectController;

		void* openProtocol;
		void* closeProtocol;

		void* openProtocolInformation;

		/// Library services.
		void* protocolsPerHandle;
		void* locateHandleBuffer;
		void* locateProtocol;

		void* installMultipleProtocolInterfaces;
		void* uninstallMultipleProtocolInterfaces;
		
		/// CRC services.
		Status(*calculateCRC32)(void* data, std::uint64_t dataSize, std::uint32_t* crc32);

		/// Memory services.
		void(*copyMem)(void* destination, void* source, std::uint64_t length);
		void(*setMem)(void* buffer, std::uint64_t size, std::uint8_t value);

		/// Event services.
		void* createEventEx;
	};
}