#pragma once

#include <cstdint>

#include <EFI/Status.hpp>
#include <EFI/FileIO/FileProtocol.hpp>
#include <EFI/GUID.hpp>

namespace EFI
{
	struct SimpleFileSystemProtocol
	{
		static constexpr GUID GUID{ 0x0964e5b22, 0x6459, 0x11d2, { 0x8e, 0x39, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b } };

		std::uint64_t revision;
		Status(*openVolume)(SimpleFileSystemProtocol*, FileProtocol** root);
	};
}