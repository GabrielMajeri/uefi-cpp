#pragma once

#include <cstdint>
#include <EFI/Status.hpp>

namespace EFI
{
	struct FileProtocol
	{
		std::uint64_t revision;
		
		// These functions have "File" appended to them because "delete" conflicted with the delete operator.
		
		Status(*openFile)(FileProtocol*, FileProtocol** newHandle, char16_t* fileName, std::uint64_t openMode, std::uint64_t attributes);
		void(*closeFile)();
		void(*deleteFile)();
		void(*readFile)();
		void* writeFile;
		
		void* getPosition;
		void* setPosition;
		
		void* getInfo;
		void* setInfo;
		
		void* flush;
		
		// These were added by revision 2:
		
		void* openEx;
		void* readEx;
		void* writeEx;
		void* flushEx;
	};
}
