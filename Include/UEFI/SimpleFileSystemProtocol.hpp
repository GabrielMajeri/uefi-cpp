#pragma once

#include "FileProtocol.hpp"

namespace UEFI
{
	/// The firmware automatically creates handles for any block device that supports the following file system formats:
	/// - FAT12
	/// - FAT16
	/// - FAT32
	class SimpleFileSystemProtocol : private NonCopyable
	{
	public:
		static constexpr GUID guid = {0x0964e5b22,0x6459,0x11d2,{0x8e,0x39,0x00,0xa0,0xc9,0x69,0x72,0x3b}};

		std::uint64_t revision;

		Status openVolume(FileProtocol*& root)
		{
			return (this->*_openVolume)(root);
		}

	private:
		using _sfsp = SimpleFileSystemProtocol;
		decltype(&_sfsp::openVolume) _openVolume;
	};
}
