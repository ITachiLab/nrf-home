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
- make

Version of the ARM Toolchain should comply with SDK's requirements. So first you download the SDK, and within it you should find a file ``components\toolchain\gcc\Makefile.posix`` and check the toolchain path it defines. By looking at the path you can determine the recommended toolchain version. This file and ``Makefile.windows`` can be modified in case the toolchain lives in another directory.

Configuration
+++++++++++++

The file ``config.json`` contains a basic configuration required for building.

    :gccPath: A full path to ARM GCC executable
    :sdkPath: A full path nRF SDK directory

Example:

.. code-block:: json

    {
      "gccPath": "C:/Program Files (x86)/GNU Arm Embedded Toolchain/9 2020-q2-update/bin/arm-none-eabi-gcc.exe",
      "sdkPath": "C:/opt/nrf5_sdk_17.1.0_ddde560"
    }

This should be enough for most cases, but I'm encouraging you to check contents of ``CMakeLists.txt`` to verify that compiler definitions are correct, in case you build project for a chip other than nRF52840.

Build and flash
+++++++++++++++

Try building and flashing the project before you apply any changes. This will guarantee that everything is properly set up.

Inside the ``nrf-template`` directory execute the following commands::

    mkdir build
    cd build
    cmake -G Ninja --toolchain toolchain.cmake ..

When CMake does not report any errors, try building the project with ``make`` and flashing it with ``make flash``. When everything went good, you should see "Hello, World" BLE device in *nRF Connect* app on your smartphone. Any app for listing BLE devices will work, pick your favorite.