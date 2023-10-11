set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_VERSION 1)
cmake_minimum_required(VERSION 3.22)

# specify cross compilers and tools
message(STATUS "Operation system is ${CMAKE_HOST_SYSTEM_NAME}")
if (CMAKE_HOST_SYSTEM_NAME MATCHES "Linux")
    set(COMPILER_DIR $ENV{CH32_DEV}bin/riscv-none-embed-)
    set(CMAKE_C_COMPILER ${COMPILER_DIR}gcc)
    set(CMAKE_CXX_COMPILER ${COMPILER_DIR}g++)
    set(CMAKE_ASM_COMPILER ${COMPILER_DIR}gcc)
    set(CMAKE_LINKER ${COMPILER_DIR}gcc)
    set(CMAKE_AR ${COMPILER_DIR}ar)
    set(CMAKE_OBJCOPY ${COMPILER_DIR}objcopy)
    set(CMAKE_OBJDUMP ${COMPILER_DIR}objdump)
    set(SIZE ${COMPILER_DIR}size.exe)
elseif (CMAKE_HOST_SYSTEM_NAME MATCHES "Windows")
    set(COMPILER_DIR $ENV{CH32_DEV}bin/riscv-none-elf-)
    set(CMAKE_C_COMPILER ${COMPILER_DIR}gcc.exe)
    set(CMAKE_CXX_COMPILER ${COMPILER_DIR}g++.exe)
    set(CMAKE_ASM_COMPILER ${COMPILER_DIR}gcc.exe)
    set(CMAKE_LINKER ${COMPILER_DIR}gcc.exe)
    set(CMAKE_AR ${COMPILER_DIR}ar.exe)
    set(CMAKE_OBJCOPY ${COMPILER_DIR}objcopy.exe)
    set(CMAKE_OBJDUMP ${COMPILER_DIR}objdump.exe)
    set(SIZE ${COMPILER_DIR}size.exe)
endif ()
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# project settings
project(miniFOC C ASM)
set(CMAKE_C_STANDARD 99)

# debug options
set(DEBUG_SERIAL_BAUDRATE 115200)
set(DEBUG_SERIAL_PORT COM9)
set(DEBUG_SERIAL ON)

# version generate
add_custom_target(update_version_file ALL
        COMMAND ${CMAKE_COMMAND} -E echo "Updating version.h"
        COMMAND ${CMAKE_COMMAND} -P ${CMAKE_SOURCE_DIR}/version.cmake
        DEPENDS ${CMAKE_SOURCE_DIR}/version.cmake
)

# compile and running options
if (${DEBUG_SERIAL})
    add_definitions(-DDEBUG)
endif ()
add_definitions(-DDEBUG_SERIAL_BAUDRATE=${DEBUG_SERIAL_BAUDRATE})
add_compile_options(-march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -msave-restore -fmessage-length=0)
add_compile_options(-fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized)
add_compile_options($<$<COMPILE_LANGUAGE:ASM>:-x$<SEMICOLON>assembler-with-cpp>)
add_compile_options(-O1 -g)

# link options
set(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/system/linkscript.ld)
add_link_options(-nostartfiles -Xlinker --gc-sections -Wl,--print-memory-usage,-Map,${PROJECT_BINARY_DIR}/${PROJECT_NAME}.map)
add_link_options(--specs=nano.specs --specs=nosys.specs -march=rv32imac -mabi=ilp32 -flto)
add_link_options(-T ${LINKER_SCRIPT})

# source and header files
include_directories(system user library/include hardware algorithm)
file(GLOB_RECURSE SOURCES "system/startup.s" "system/*.c" "library/source/*.c" "user/*.c" "hardware/*.c" "algorithm/*.c")

add_executable(${PROJECT_NAME}.elf ${SOURCES} ${LINKER_SCRIPT})
add_dependencies(${PROJECT_NAME}.elf update_version_file)

# generate hex and bin file
set(HEX_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.hex)
set(BIN_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.bin)
set(LIST_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.lst)

add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -O ihex $<TARGET_FILE:${PROJECT_NAME}.elf> ${HEX_FILE}
        COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${PROJECT_NAME}.elf> ${BIN_FILE}
        COMMENT "Building ${HEX_FILE}
Building ${BIN_FILE}")
add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
        COMMAND ${CMAKE_OBJDUMP} --all-headers --demangle --disassemble -M xw $<TARGET_FILE:${PROJECT_NAME}.elf> > ${LIST_FILE}
        COMMENT "Building ${LIST_FILE}")