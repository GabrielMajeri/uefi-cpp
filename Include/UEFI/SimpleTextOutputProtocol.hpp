#pragma once

#include <cstddef>

#include "NonCopyable.hpp"
#include "GUID.hpp"
#include "Status.hpp"

namespace UEFI
{
	// You can find these in the ConsoleColor header.
	enum class ForegroundColor : std::uint8_t;
	enum class BackgroundColor : std::uint8_t;

	class SimpleTextOutputProtocol : private NonCopyable
	{
	public:
		static constexpr GUID guid = {0x387477c2,0x69c7,0x11d2, {0x8e,0x39,0x00,0xa0,0xc9,0x69,0x72,0x3b}};

		/// Represents the console's current color settings.
		struct Attribute
		{
			ForegroundColor foreground : 4;

			// This should only be 3 bits wide, but we need to ensure the compiler sets the extra bit to 0.
			BackgroundColor background : 4;
		};

		/// Resets the text output device hardware.
		/// The cursor position is set to (0, 0).
		/// The screen is cleared to the default background color for the output device.
		/// @param extendedVerification If set, the device may run exhaustive error checks.
		/// @return Success The text output device was reset.
		/// @return DeviceError The text output device is not functioning correctly and could not be reset.
		[[gnu::ms_abi]]
		Status reset(bool extendedVerification)
		{
			return (this->*_reset)(extendedVerification);
		}

		/// Writes a string to the output device.
		/// @param string The null-terminated string to print.
		/// @return Success The string was output to the device.
		/// @return DeviceError The device reported an error while attempting to output the text.
		/// @return Unsupported The output device’s mode is not currently in a defined text mode.
		/// @return WarnUnknownGlyph This warning code indicates that some of the characters in the string could not be rendered and were skipped.
		[[gnu::ms_abi]]
		Status outputString(const char16_t* string)
		{
			return (this->*_outputString)(string);
		}

		// TODO: document these functions
		[[gnu::ms_abi]]
		Status testString(const char16_t* string)
		{
			return (this->*_testString)(string);
		}

		[[gnu::ms_abi]]
		Status queryMode(std::size_t modeNumber, std::size_t& columns, std::size_t& rows)
		{
            return (this->*_queryMode)(modeNumber, columns, rows);
		}

		/// Sets the output device to a specified mode.
		/// On success the device is in the geometry for the requested mode,
		/// and the device has been cleared to the current background color with the cursor at (0,0).
		/// @return Success The requested text mode was set.
		/// @return DeviceError The device had an error and could not complete the request.
		/// @return Unsupported The mode number was not valid.
		[[gnu::ms_abi]]
		Status setMode(std::size_t modeNumber)
		{
			return (this->*_setMode)(modeNumber);
		}

		/// Sets the background and foreground colors for the OutputString() and ClearScreen() functions.
		/// @param att The attribute to set (foreground and background color).
		/// @return Success The requested attributes were set.
		/// @return DeviceError The device had an error and could not complete the request.
		[[gnu::ms_abi]]
		Status setAttribute(Attribute att)
		{
			return (this->*_setAttribute)(att);
		}

		/// Clears the output device display to the currently selected background color.
		/// @return Success The operation completed successfully.
		/// @return DeviceError The device had an error and could not complete the request.
		/// @return Unsupported The output device is not in a valid text mode.
		[[gnu::ms_abi]]
		Status clearScreen()
		{
			return (this->*_clearScreen)();
		}

	private:
		// Function pointers.
		using _stp = SimpleTextOutputProtocol;
		decltype(&_stp::reset) _reset;
		decltype(&_stp::outputString) _outputString;
		decltype(&_stp::testString) _testString;
		decltype(&_stp::queryMode) _queryMode;
		decltype(&_stp::setMode) _setMode;
		decltype(&_stp::setAttribute) _setAttribute;
		decltype(&_stp::clearScreen) _clearScreen;
	};
}
