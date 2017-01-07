#pragma once

namespace UEFI
{
	/// Classes that inherit from this will not be copyable.
	class NonCopyable
	{
		NonCopyable(NonCopyable&) = delete;
		NonCopyable& operator=(NonCopyable&) = delete;
	};
}
