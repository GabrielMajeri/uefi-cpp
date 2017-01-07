#pragma once

#include <cstddef>

namespace UEFI
{
	/// Task Priority Level.
	/// By raising the task priority level to higher levels some notifications are masked until the task priority level is restored.
	/// Device drivers will typically use Callback or Notify for their notification functions.
	/// Good coding practice dictates that all code should execute at its lowest possible TPL level.
	enum class TPL : std::size_t
	{
		/// Application is where all normal execution occurs.
		Application = 4,
		/// Typically used for application level notification functions.
		Callback = 8,
		/// Synchronous blocking I/O functions execute at Notify.
		Notify = 16,

		/// Do not use, intended only for the firmware.
		HighLevel = 31
	};
}
