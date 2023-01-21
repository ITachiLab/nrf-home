set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

if(NOT DEFINED ENV{GCC_PATH} AND NOT DEFINED ENV{SDK_ROOT})
    file(READ "config.json" config)
    string(JSON GCC_PATH GET ${config} gccPath)
    string(JSON SDK_ROOT GET ${config} sdkRoot)

    set(ENV{GCC_PATH} ${GCC_PATH})
    set(ENV{SDK_ROOT} ${SDK_ROOT})
endif()

set(CMAKE_C_COMPILER "${GCC_PATH}")
set(CMAKE_ASM_COMPILER "${GCC_PATH}")