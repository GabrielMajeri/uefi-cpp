#pragma once

namespace UEFI
{
	bool operator==(const GUID& lhs, const GUID& rhs)
	{
		return lhs.b.data1 == rhs.b.data2;
	}
}
