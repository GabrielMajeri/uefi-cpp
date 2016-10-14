#pragma once

#include <EFI/Status.hpp>
#include <EFI/GUID.hpp>
#include <EFI/Event.hpp>

namespace EFI
{
	struct SimpleTextOutputProtocol
	{
		static constexpr GUID GUID{ 0x387477c2, 0x69c7, 0x11d2, {0x8e,0x39,0x00,0xa0,0xc9,0x69,0x72,0x3b} };

		Status(*reset)(SimpleTextOutputProtocol*, bool allowExtendedVerification);

		Status(*outputString)(SimpleTextOutputProtocol*, const char16_t* string);

		Status(*testString)(SimpleTextOutputProtocol*, const char16_t* string);

		Status(*queryMode)(SimpleTextOutputProtocol*, std::uint64_t modeNumber, std::uint64_t* columns, std::uint64_t* rows);
		Status(*setMode)(SimpleTextOutputProtocol*, std::uint64_t modeNumber);

		Status(*setAttribute)(SimpleTextOutputProtocol*, std::uint64_t attribute);
		Status(*clearScreen)(SimpleTextOutputProtocol*);

		Status(*setCursorPosition)(SimpleTextOutputProtocol*, std::uint64_t column, std::uint64_t row);

		Status(*enableCursor)(SimpleTextOutputProtocol*, bool visible);

		struct Mode
		{
			std::int32_t maxMode;

			std::int32_t mode;
			std::int32_t attribute;

			struct CursorPosition { std::int32_t column, row; } cursor;

			bool cursorVisibile;

		} * mode;
	};

	struct SimplePointerProtocol
	{
		static constexpr GUID GUID{ 0x31878c87, 0xb75, 0x11d5, { 0x9a, 0x4f, 0x00, 0x90, 0x27, 0x3f, 0xc1, 0x4d } };
		Status(*reset)(SimplePointerProtocol*, bool allowExtendedVerification);

		struct SimplePointerState
		{
			struct { std::int32_t x, y, z; } movement;
			bool leftButtonDown, rightButtonDown;
		};

		Status(*getState)(SimplePointerProtocol*, SimplePointerState* state);
		Event waitForInput;

		struct SimplePointerMode
		{
			struct { std::uint64_t x, y, z; } resolution;

			bool hasLeftButton, hasRightButton;
		} * mode;
	};
}