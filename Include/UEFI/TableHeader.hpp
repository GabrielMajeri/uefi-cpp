#pragma once

#include "CRC32.hpp"
#include "Signature.hpp"
#include "Revision.hpp"

namespace UEFI
{
	struct TableHeader
	{
		/// A 64-bit signature that identifies the type of table that follows.
		Signature signature;

		/// The revision of the EFI Specification to which this table conforms.
		Revision revision;

		/// The size, in bytes, of the entire table including this structure.
		std::uint32_t size;

		/// The 32-bit CRC for the entire table.
		/// This value is computed by setting this field to 0, and computing the 32-bit CRC for the whole table.
		CRC32 crc32;

        /// Reserved field that must be set to 0.
		std::uint32_t reserved;
	};
}
