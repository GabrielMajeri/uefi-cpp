# UEFI++
## An object-oriented wrapper for UEFI

**Note**: **I am no longer maintaining this project, instead
  I am working on [an equivalent library][wrap] for the [Rust][rust] programming language.**

[wrap]: https://github.com/GabrielMajeri/uefi-rs
[rust]: https://www.rust-lang.org/en-US/

This project is a C++ wrapper for the UEFI specification, intended for people who write UEFI applications (OS loaders, shells, etc.)

This wrapper supports both 32 and 64 bit UEFI architectures.

The project is composed of two parts:
- The headers in the `UEFI` folder, which contain the base structures from the UEFI specification.
- The headers in the `UEFI++` folder, which contain some classes to make UEFI easier to use.

**The current version is based on Version 2.6 of the UEFI specification, available [here](http://www.uefi.org/specifications).**

# Example
Here's some code that uses the old, C-style API of the specification:

```c
systemTable->ConOut->OutputString(systemTable->ConOut, L"Hello UEFI!");
```

Here's some code that uses the new C++ API:

```c++
systemTable.consoleOut.outputString(u"Hello UEFI!");
```

And here's one that's even more modern:

```c++
// Set the stream's output.
out.setOutput(*systemTable.consoleOut);

out << "Hello UEFI!";
```

Performance difference? Zero. Zero cost abstractions make this possible.

# Features
- Uses modern C++14 features (constexpr, static_assert, strongly typed enums).
- Mainly intended for UEFI applications, not tested for UEFI drivers.
- Relies on some C/C++ headers, but does not require a hosted standard library.

# Required software
* C++14 compatible compiler (Clang, GCC).
* A C++14 standard library (including the C headers). This wrapper only uses non-hosted functions from the standard lib, therefore it doesn't require a runtime. Some of the required headers:
  - `<cstdint>`: for cross-architecture integer types.
  - `<cstddef>`: for size_t.
  - `<type_traits>`: for some template metaprogramming and static assertions.
  - `<utility>`: for some utility functions (e.g. std::swap()).

* *(Optional)* QEmu with OVMF to be able to test UEFI apps in a virtual machine.
* *(Optional)* Doxygen to generate documentation.

# License
The files included in this repository are licensed under the
[Mozilla Public License, Version 2.0](https://www.mozilla.org/en-US/MPL/2.0/).

This means you are free to use the header files, even in a proprietary program,
as long as they are unmodified. You must open source any modifications to the
headers you use.

See the license for more information.

# Contributions
Anyone is welcome to contribute to this project. 

Please try to adhere to modern C++ coding style & guidelines and avoid C-style hacks. Use the **Issues** tab to submit bugs or feature requests, or submit improved code as **Pull requests**.
