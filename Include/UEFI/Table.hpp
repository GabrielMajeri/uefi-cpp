#pragma once

#include "TableHeader.hpp"

namespace UEFI
{
	/// An UEFI table. It's recommended to inherit from this class if you plan to create your own table.
	struct Table
	{
		TableHeader header;
	};
}
