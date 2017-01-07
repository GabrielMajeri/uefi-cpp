#pragma once

#include <cstdint>

#include "NonCopyable.hpp"
#include "GUID.hpp"
#include "Status.hpp"

namespace UEFI
{
	class SimpleTextInputProtocol : private NonCopyable
	{
	public:
		static constexpr GUID guid = {0x387477c1,0x69c7,0x11d2, {0x8e,0x39,0x00,0xa0,0xc9,0x69,0x72,0x3b}};


		struct Key
		{
			std::uint16_t scanCode;

			/// The character that represents this key.
			/// 0 if not a printable character.
			char16_t unicodeChar;
		};

		/// Resets the input device hardware.
		/// Clears the contents of any input queues and puts the input stream in a known empty state.
		/// @param extendedVerification If true the driver may perform a more exhaustive verification of the device.
		/// @return Success: The device was reset.
		/// @return DeviceError: The device is not functioning correctly and could not be reset.
		[[gnu::ms_abi]]
		Status reset(bool extendedVerification)
		{
			return (this->*_reset)(extendedVerification);
		}

		/// Reads a keystroke from the input queue, if any.
		/// @param[out] key The structure to read keystroke data into.
		/// @return Sucess: The keystroke information was returned.
		/// @return NotReady: There was no keystroke data available.
		/// @return DeviceError: The keystroke information was not returned due to hardware errors.
		[[gnu::ms_abi]]
		Status readKeyStroke(Key& key)
		{
			return (this->*_readKeyStroke)(key);
		}

	private:
		using _sti = SimpleTextInputProtocol;
		decltype(&_sti::reset) _reset;
		decltype(&_sti::readKeyStroke) _readKeyStroke;
	};
}
