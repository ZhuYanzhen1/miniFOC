set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_VERSION 1)
cmake_minimum_required(VERSION 3.16)

# specify cross compilers and tools
set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_ASM_COMPILER arm-none-eabi-gcc)
set(CMAKE_AR arm-none-eabi-ar)
set(CMAKE_OBJCOPY arm-none-eabi-objcopy)
set(CMAKE_OBJDUMP arm-none-eabi-objdump)
set(SIZE arm-none-eabi-size)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# project settings
project(miniFOC C ASM)
set(CMAKE_C_STANDARD 11)

add_compile_options(-mfloat-abi=soft)
add_compile_options(-mcpu=cortex-m3 -mthumb -mthumb-interwork -specs=nosys.specs)
add_compile_options(-ffunction-sections -fdata-sections -fno-common -fmessage-length=0)
add_compile_options(-O2)

include_directories(system library/inc hardware ./ algorithm)

add_definitions(-DUSE_STDPERIPH_DRIVER -DGD32F130_150)

file(GLOB_RECURSE SOURCES "library/src/*.c" "system/*.c" "main.c"
        "system/startup_gd32f130.s" "hardware/*.c" "algorithm/*.c")

set(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/system/gd32f130g6u6.ld)

add_link_options(-Wl,-gc-sections,--print-memory-usage,-Map=${PROJECT_BINARY_DIR}/${PROJECT_NAME}.map)
add_link_options(-mcpu=cortex-m3 -mthumb -mthumb-interwork --specs=nano.specs)
add_link_options(-T ${LINKER_SCRIPT})
add_executable(${PROJECT_NAME}.elf ${SOURCES} ${LINKER_SCRIPT})
set(HEX_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.hex)
add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -Oihex $<TARGET_FILE:${PROJECT_NAME}.elf> ${HEX_FILE}
        COMMENT "Building ${HEX_FILE}")
