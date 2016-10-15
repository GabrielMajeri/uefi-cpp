# C++ UEFI Wrapper
This project is a C++ wrapper for the UEFI specification, intended for people who write UEFI applications (OS loaders, shells, etc.)

This wrapper only supports 64 bit versions of UEFI.

The project is composed of two parts:
- The low-level wrapper, that uses structs and pointers to directly implement the UEFI specification.
- The high-level, object-oriented wrapper, that uses classes to represent various UEFI protocols.

**The current version is based on Version 2.6 of the UEFI specification, available [here](http://www.uefi.org/specifications).**

# Features
- Uses modern C++14 features (constexpr, static_assert, strongly typed enums).
- Mainly intended for UEFI applications, not UEFI drivers or firmwares.
- Relies on some C/C++ headers, but does not require a hosted standard library (obviously).

# Required software
* C++14 compatible compiler (Clang, newer versions of MSVC, GCC).
* A C++14 standard library (including the C headers). This wrapper only uses non-hosted functions from the standard lib, therefore it doesn't require a runtime.

* *(Optional)* QEmu with OVMF to be able to test UEFI apps in a virtual machine.

# License
This wrapper for the UEFI specification is licensed under a permissive MIT license. See [LICENSE](LICENSE) for more information.

# Contributions
Anyone is welcome to contribute to this project. Please try to adhere to modern C++ coding style & guidelines and avoid C-style hacks. Use the **Issues** tab to submit bugs or feature requests, or submit improved code as **Pull requests**.
