#pragma once

namespace UEFI
{
	void TextInputStream::setInput(SimpleTextInputProtocol& txIn)
	{
		in = &txIn;
	}

	auto TextInputStream::readKeySync() -> Key
	{
		Key key;

		// TODO: something else than an infinite loop? What if input fails because of device errors?
		while(in->readKeyStroke(key) != Status::Success);

		return key;
	}
}
