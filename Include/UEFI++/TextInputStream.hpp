#pragma once

#include <UEFI/SimpleTextInputProtocol.hpp>

namespace UEFI
{
	struct TextInputStream
	{
		using Key = SimpleTextInputProtocol::Key;

		void setInput(SimpleTextInputProtocol& txIn);

		Key readKeySync();

		SimpleTextInputProtocol* in;
	};
}
