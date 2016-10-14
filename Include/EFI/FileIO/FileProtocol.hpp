#pragma once

namespace EFI
{
	struct FileProtocol
	{
		std::uint64_t revision;
		void* openFile;
		void* closeFile;
		void* deleteFile;
		void(*readFile)();
		void* writeFile;

	};
}