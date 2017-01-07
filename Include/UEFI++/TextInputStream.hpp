#pragma once

#include <UEFI/SimpleTextInputProtocol.hpp>

namespace UEFI
{
	/// This class provides utility functions from reading and writing to the console.
	struct TextInputStream
	{
		using Key = SimpleTextInputProtocol::Key;

		void setInput(SimpleTextInputProtocol& txIn);

		Key readKeySync();

		SimpleTextInputProtocol* in;
	};
}
