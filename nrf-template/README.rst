nRF Template Code
=================

.. toctree::
    :hidden:

    docs/overview

*nRF Template Code* is a CMake based project template you can use to bootstrap your own nRF project.

Building
--------

Requirements
++++++++++++

- `nRF5 SDK <https://www.nordicsemi.com/Products/Development-software/nRF5-SDK/Download>`__
- `ARM Toolchain 9 2020 Q2 Update <https://developer.arm.com/downloads/-/gnu-rm>`__
- `CMake <https://cmake.org/download/>`__
- Windows:

  - `Cygwin <https://www.cygwin.com>`__ or...
  - `MinGW <https://www.mingw-w64.org>`__

- Linux:

  - Build essentials

Version of the ARM Toolchain should comply with SDK's requirements. So first you download the SDK, and within it you should find a file ``components/toolchain/gcc/Makefile.posix`` and check the toolchain path it defines. By looking at the path you can determine the recommended toolchain version. This file and ``Makefile.windows`` can be modified in case the toolchain lives in another directory.

Configuration
+++++++++++++

The file ``config.json`` contains a basic configuration required for building.

    :gccPath: A full path to ARM GCC executable
    :sdkRoot: A full path nRF SDK directory

Example ``config.json`` for Windows:

.. code-block:: json

    {
      "gccPath": "C:/Program Files (x86)/GNU Arm Embedded Toolchain/9 2020-q2-update/bin/arm-none-eabi-gcc.exe",
      "sdkRoot": "C:/opt/nrf5_sdk_17.1.0_ddde560"
    }

This should be enough for most cases, but I'm encouraging you to check contents of ``CMakeLists.txt`` to verify that compiler definitions are correct, in case you build project for a chip other than nRF52840.

Build and flash
+++++++++++++++

Try building and flashing the project before you apply any changes. This will guarantee that everything is properly set up.

Inside the ``nrf-template`` directory execute the following commands::

    mkdir build
    cd build

And now, it depends on the operating system and software used for building.

Linux
*****

::

    cmake -G "Unix Makefiles" --toolchain toolchain.cmake ..

Windows
*******

When building on Windows and using MinGW for running *make*::

    cmake -G "MinGW Makefiles" --toolchain toolchain.cmake ..

For Cygwin a different generator must be used::

    cmake -G "Unix Makefiles" --toolchain toolchain.cmake ..

When CMake does not report any errors, try building the project with ``make`` and then flashing it with either ``make flash_all``, to flash the device with the user application and SoftDevice, or ``make flash`` to flash only the user application [1]_. When everything went good, you should see "Hello, World" BLE device in *nRF Connect* app on your smartphone. In fact, any app for listing BLE devices will work, pick your favorite.

----

.. [1] To speed up the compilation process, use ``-j 6`` option for ``make``.