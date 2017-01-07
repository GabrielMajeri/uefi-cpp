#pragma once

#include <cstdint>
#include <cstddef>

#include "SignedTable.hpp"
#include "Handle.hpp"
#include "RuntimeServices.hpp"
#include "BootServices.hpp"
#include "ConfigurationTable.hpp"

namespace UEFI
{
	class SimpleTextInputProtocol;
	class SimpleTextOutputProtocol;

	/// The UEFI System Table contains pointers to the runtime and boot services tables.
	/// After a call to ExitBootServices(), only the header, firmware, firmware, runtimeServices, numberOfTableEntries, and configurationTable are still vaild.
	struct SystemTable : public SignedTable<0x5453595320494249>
	{
		/// Information about the UEFI firmware.
		struct
		{
			/// A null-terminated string with the name of the vendor of the firmware.
			const char16_t* vendor;
			/// The version of the firmware.
			Revision revision;
		} firmware;

		Handle consoleInHandle;
		SimpleTextInputProtocol* conIn;

		Handle consoleOutHandle;
		SimpleTextOutputProtocol* conOut;

		Handle standardErrorHandle;
		SimpleTextOutputProtocol* stdErr;

		RuntimeServices* runtimeServices;
		BootServices* bootServices;

		std::size_t numberOfTableEntries;
		ConfigurationTable* configurationTable;
	};
}
