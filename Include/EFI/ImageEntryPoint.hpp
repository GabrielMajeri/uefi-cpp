#pragma once

#include <EFI/Status.hpp>
#include <EFI/Handle.hpp>
#include <EFI/SystemTable.hpp>

#include <type_traits>

namespace EFI
{	
	using ImageEntryPoint = Status(*)(Handle, SystemTable*);

	template <typename Func>
	constexpr bool isEntryPoint = std::is_same_v<ImageEntryPoint, Func>;
}