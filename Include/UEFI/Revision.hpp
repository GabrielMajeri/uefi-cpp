#pragma once

namespace UEFI
{
	/// This structures describes a revision of some structure or software.
	/// For UEFI tables, the revision corresponds to the specification's version.
	struct Revision
	{
		std::uint16_t minor;
		std::uint16_t major;
	};
}
