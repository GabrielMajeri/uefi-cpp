#pragma once

#include <cstddef>
#include "NonCopyable.hpp"
#include "GUID.hpp"

#include "Detail/BitFlags.hpp"

namespace UEFI
{
	template <std::size_t labelSize = 128>
	struct FileSystemInfo
	{
		static constexpr GUID guid = {0x09576e93,0x6d3f,0x11d2,{0x8e,0x39,0x00,0xa0,0xc9,0x69,0x72,0x3b}};

		std::uint64_t size;
        bool readOnly;
        std::uint64_t volumeSize, freeSpace;
        std::uint32_t blockSize;

        /// This field might not be large enough. Try with different sizes.
        char16_t volumeLabel[labelSize];
	};

	template <std::size_t labelSize = 128>
	struct FileSystemVolumeLabel
	{
		static constexpr GUID guid = {0xdb47d7d3,0xfe81,0x11d3,{0x9a,0x35,0x00,0x90,0x27,0x3f,0xC1,0x4d}};

		char16_t volumeLabel[labelSize];
	};

	enum class OpenMode : std::uint64_t
	{
		Create = 0x8000000000000000,
		Read = 1,
		Write = 2
	};

	UEFI_BIT_FLAGS(OpenMode);

	enum class FileAttributes : std::uint64_t
	{
		None = 0,
		ReadOnly = 1,
		Hidden = 2,
		System = 4,
		Reserved = 8,
		Directory = 0x10,
		Archive = 0x20,
		ValidAttr = 0x37
	};

	UEFI_BIT_FLAGS(FileAttributes);

	/// Provides file based access to supported file systems.
	class FileProtocol : private NonCopyable
	{
	public:
		std::uint64_t revision;


		/// @return Success The file was opened.
		/// @return NotFound The specified file could not be found on the device.
		/// @return NoMedia The device has no medium.
		/// @return MediaChanged The device has a different medium in it or the medium is no longer supported.
		/// @return DeviceError The device reported an error.
		/// @return VolumeCorrupted The file system structures are corrupted.
		/// @return WriteProtected An attempt was made to create a file, or open a file for write when the media is write-protected.
		/// @return AccessDenied The service denied access to the file.
		/// @return OutOfResources Not enough resources were available to open the file.
		/// @return VolumeFull The volume is full.
		Status open(FileProtocol*& newHandle, const char16_t* fileName, OpenMode openMode, FileAttributes attributes)
		{
            return (this->*_open)(newHandle, fileName, openMode, attributes);
		}

		Status close()
		{
			return (this->*_close)();
		}

		// EFI_FILE_DELETE Delete;

		Status read(std::size_t& bufferSize, void* buffer)
		{
			return (this->*_read)(bufferSize, buffer);
		}

		Status write(std::size_t& bufferSize, const void* buffer)
		{
			return (this->*_write)(bufferSize, buffer);
		}

		Status getPosition(std::uint64_t& position)
		{
			return (this->*_getPosition)(position);
		}

		Status setPosition(std::uint64_t position)
		{
			return (this->*_setPosition)(position);
		}

		Status getInfo(const GUID& infoType, std::size_t& bufferSize, void* buffer)
		{
			return (this->*_getInfo)(infoType, bufferSize, buffer);
		}

		// EFI_FILE_SET_INFO SetInfo;
		// EFI_FILE_FLUSH Flush;

	private:
		using _fp = FileProtocol;

		decltype(&_fp::open) _open;
		decltype(&_fp::close) _close;

		[[maybe_unused]] void* buf1[1];

		decltype(&_fp::read) _read;
		decltype(&_fp::write) _write;

		decltype(&_fp::getPosition) _getPosition;
		decltype(&_fp::setPosition) _setPosition;

		decltype(&_fp::getInfo) _getInfo;
	};

	class FileProtocol2 : public FileProtocol
	{
	public:
		// EFI_FILE_OPEN_EX OpenEx;
		// EFI_FILE_READ_EX ReadEx;
		// EFI_FILE_WRITE_EX WriteEx;
		// EFI_FILE_FLUSH_EX FlushEx;

	private:
	};
}
