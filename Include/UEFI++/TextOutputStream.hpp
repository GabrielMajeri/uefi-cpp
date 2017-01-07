#pragma once

#include <UEFI/ConsoleColor.hpp>
#include <UEFI/SimpleTextOutputProtocol.hpp>

namespace UEFI
{
	/// For UEFI newlines are in Carriage Return + Line Feed (Windows) format.
	constexpr auto newLine = u"\r\n";

	using TextColor = SimpleTextOutputProtocol::Attribute;

	/// Note: this "default color" isn't specified in the standard, but OVMF and mTextOutputStreamt computers use this as the default.
	constexpr TextColor defaultColor = { ForegroundColor::LightGray, BackgroundColor::Black };

	struct TextOutputStream
	{
		// Since static constructors require runtime support, it's better for users to just call initialize().
		[[gnu::ms_abi]]
		void initialize();

		[[gnu::ms_abi]]
		void setOutput(SimpleTextOutputProtocol& txOut);

		[[gnu::ms_abi]]
		void reset(bool extendedVerification);

		[[gnu::ms_abi]]
		void clear();

		[[gnu::ms_abi]]
		void setNumberBase(std::uint8_t b);

		SimpleTextOutputProtocol* out;

		bool boolAlpha;
		std::uint8_t base;

		char _padding[6];
	};

	[[gnu::ms_abi]]
	TextOutputStream& operator<<(TextOutputStream& to, const char16_t* msg);

	[[gnu::ms_abi]]
	TextOutputStream& operator<<(TextOutputStream& to, char16_t* msg);

	/// Prints a number in the specified base to `stream`.
	/// Base should be above 2, and no bigger than 36 (otherwise it would start running out of letters).
	[[gnu::ms_abi]]
	void printNumber(TextOutputStream& stream, std::uint64_t number);

	[[gnu::ms_abi]]
	TextOutputStream& operator<<(TextOutputStream& to, TextColor color);

	[[gnu::ms_abi]]
	TextOutputStream& operator<<(TextOutputStream& os, bool value);

	[[gnu::ms_abi]]
	TextOutputStream& operator<<(TextOutputStream& to, std::uint64_t n);

	[[gnu::ms_abi]]
	inline TextOutputStream& operator<<(TextOutputStream& to, std::uint16_t n)
	{
		return to << static_cast<std::uint64_t>(n);
	}

	[[gnu::ms_abi]]
	TextOutputStream& operator<<(TextOutputStream& to, Status status);

	[[gnu::ms_abi]]
	TextOutputStream& operator<<(TextOutputStream& to, const unsigned char* msg);

	[[gnu::ms_abi]]
	TextOutputStream& operator<<(TextOutputStream& to, unsigned char* msg);

	[[gnu::ms_abi]]
	TextOutputStream& operator<<(TextOutputStream& to, const char* msg);

	[[gnu::ms_abi]]
	TextOutputStream& operator<<(TextOutputStream& to, char* msg);
}
