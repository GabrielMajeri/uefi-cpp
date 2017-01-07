#pragma once

#include <utility>

namespace UEFI
{
	void TextOutputStream::initialize()
	{
		boolAlpha = true;
		base = 10;
	}

	void TextOutputStream::setOutput(SimpleTextOutputProtocol& txOut)
	{
		out = &txOut;
	}

	void TextOutputStream::reset(bool extendedVerification)
	{
		out->reset(extendedVerification);
	}

	void TextOutputStream::clear()
	{
		out->clearScreen();
	}

	void TextOutputStream::setNumberBase(std::uint8_t b)
	{
		base = b;
	}


	TextOutputStream& operator<<(TextOutputStream& to, const char16_t* msg)
	{
		to.out->outputString(msg);
		return to;
	}

	TextOutputStream& operator<<(TextOutputStream& to, char16_t* msg)
	{
		return to << static_cast<const char16_t*>(msg);
	}

	void printNumber(TextOutputStream& stream, std::uint64_t number)
	{
		auto base = stream.base;

		if (base < 2 || base > 36)
			return;

		// A 64 bit number can be up to 2^64, which means up to log2(2^64) = 64 digits in base 2.
		// In bigger bases then it is smaller.
		static char16_t buf[65];

		// Add some prefixes for various bases.
		switch (base)
		{
		case 2:
			stream << u"0b";
			break;

		case 8:
			stream << u"0";
			break;

		case 16:
			stream << u"0x";
			break;

		default:
			break;
		}

		int k = 0;

		if(number == 0)
		{
			buf[0] = '0';
			k = 1;
		}

		while (number)
		{
			std::uint8_t value = (number % base);

			// If it's a digit.
			if (value <= 9)
				buf[k++] = '0' + value;
			// Loop around to letters.
			else
				buf[k++] = 'A' + (value - 10);

			// Remove a digit.
			number /= base;
		}

		// TODO: is there no better solution than reversing?
		for (int i = 0; i < k / 2; ++i)
			std::swap(buf[i], buf[k - i - 1]);

		// Add a null terminator.
		buf[k] = 0;

		stream << buf;
	}

	TextOutputStream& operator<<(TextOutputStream& to, TextColor color)
	{
		to.out->setAttribute(color);
		return to;
	}

	TextOutputStream& operator<<(TextOutputStream& os, bool value)
	{
		if (os.boolAlpha)
			return os << (value ? u"true" : u"false");
		else
			return os << (value ? u"1" : u"0");
	}

	TextOutputStream& operator<<(TextOutputStream& to, std::uint64_t n)
	{
		printNumber(to, n);
		return to;
	}

	TextOutputStream& operator<<(TextOutputStream& to, Status status)
	{
		std::uint64_t code = static_cast<std::uint64_t>(status);

		// Clear the high bit.
		code &= ~(1ull << 63);

		auto copy = to.base;

		to.setNumberBase(10);
		to << code;
		to.setNumberBase(copy);

		return to;
	}

	TextOutputStream& operator<<(TextOutputStream& to, const unsigned char* msg)
	{
		// TODO: bounds checking for buffer
		static char16_t buffer[512];

		auto ptr = buffer;

        while (*msg != 0)
            *ptr++ = *msg++;

		*ptr = 0;

		return to << buffer;
	}

	TextOutputStream& operator<<(TextOutputStream& to, unsigned char* msg)
	{
		return to << static_cast<const unsigned char*>(msg);
	}

	TextOutputStream& operator<<(TextOutputStream& to, const char* msg)
	{
		return to << reinterpret_cast<const unsigned char*>(msg);
	}

	TextOutputStream& operator<<(TextOutputStream& to, char* msg)
	{
		return to << reinterpret_cast<const unsigned char*>(msg);
	}
}
