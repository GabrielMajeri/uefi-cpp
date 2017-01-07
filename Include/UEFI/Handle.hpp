#pragma once

namespace UEFI
{
	/// Represents an opaque handle, usually allocated by the UEFI boot loader.
	using Handle = struct { } *;
}
