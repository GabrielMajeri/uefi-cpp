#pragma once

#include <EFI/TextIO/SimpleTextOutputProtocol.hpp>

namespace EFI
{
	class Console
	{
	public:
		Console(SimpleTextOutputProtocol* prot)
			: cout{ prot }
		{
		}

		Console(const Console&) = delete;
		Console& operator=(const Console&) = delete;

		void reset()
		{
			cout->reset(cout, false);
		}

		Console& printNewLine()
		{
			return printString(u"\xD\xA");
		}

		Console& printChar16(char16_t ch)
		{
			return printString(&ch);
		}

		Console& printString(const char16_t* rhs)
		{
			cout->outputString(cout, rhs);
			
			return *this;
		}

		Console& printUInt(std::uint64_t n)
		{
			if (n == 0) 
			{
				char16_t tmp = u'0';
				printString(&tmp);
				return *this;
			}

			auto copy = n, inv = 0ull;

			while (copy)
			{
				inv = (inv * 10) + (copy % 10);
				copy /= 10;
			}

			while (inv)
			{
				char16_t tmp = (u'0' + inv % 10);
				printString(&tmp);
				inv /= 10;
			}

			return *this;
		}

		void setCursorPosition(std::uint64_t x, std::uint64_t y)
		{
			cout->setCursorPosition(cout, y, x);
		}

	private:
		SimpleTextOutputProtocol* cout;
	};
}
