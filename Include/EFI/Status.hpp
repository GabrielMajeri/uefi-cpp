#pragma once

#include <cstdint>

namespace EFI
{
	namespace Detail
	{
		// Error codes are normal values with the most significant bit set.
		constexpr std::int64_t makeErrorCode(std::int64_t code)
		{
			return code | (1ll << 63ll);
		}
	}

	enum class Status
		: std::int64_t
	{
		/// Success values (high bit clear).
		/// The operation succedded.
		Success = 0,

		/// Warning codes (high bit clear).
		WarningUnknownGlyph = 1,
		WarningDeleteFailure = 2,
		WarningWriteFailure = 3,
		WarningBufferTooSmall = 4,
		WarningStaleData = 5,
		WarningFileSystem = 6,

		/// Error values (high bit set, negative).
		LoadError = Detail::makeErrorCode(1),
		InvalidParameter = Detail::makeErrorCode(2),
		Unsupported = Detail::makeErrorCode(3),
		BadBufferSize = Detail::makeErrorCode(4),
		BufferTooSmall = Detail::makeErrorCode(5),
		NotReady = Detail::makeErrorCode(6),
		DeviceError = Detail::makeErrorCode(7),
		WriteProtected = Detail::makeErrorCode(8),
		
		// TODO: add all the error codes.
		
		CRCError = Detail::makeErrorCode(27),
		HTTPError = Detail::makeErrorCode(35)
	};
	
	/// Checks if a status code represents a success code.
	constexpr bool isSuccess(Status statusCode)
	{
		return statusCode == Status::Success;
	}
	
	/// Check if a status code represents a warning.
	constexpr bool isWarning(Status statusCode)
	{
		// Warnings have the high bit clear, they are positive integers.
		return static_cast<std::int64_t>(statusCode) > 0;
	}
	
	/// Checks if a status code represents an error.
	constexpr bool isError(Status statusCode)
	{
		// Error codes have the high bit set, they are viewed as negative integers.
		return static_cast<std::int64_t>(statusCode) < 0;
	}
	
}
