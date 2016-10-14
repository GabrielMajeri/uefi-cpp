#pragma once

#include <EFI/TableHeader.hpp>
#include <EFI/Handle.hpp>

namespace EFI
{
	struct SimpleTextInputProtocol;
	struct SimpleTextOutputProtocol;

	struct BootServices;
	struct RuntimeServices;
	struct ConfigurationTable;

	struct SystemTable
	{
		TableHeader header;
		static constexpr auto signature{ 0x5453595320494249ull };

		char16_t* firmwareVendor;
		std::uint32_t firmwareRevision;

		Handle conInHandle;
		SimpleTextInputProtocol* conIn;

		Handle conOutHandle;
		SimpleTextOutputProtocol* conOut;
		
		Handle stdErrHandle;
		SimpleTextOutputProtocol* stdErr;

		RuntimeServices* runtimeServices;

		BootServices* bootServices;

		std::uint64_t tableEntries;
		ConfigurationTable* configTable;
	};
}