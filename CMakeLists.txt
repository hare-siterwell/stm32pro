cmake_minimum_required(VERSION 3.18)
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR ARM)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
project(stm32pro C ASM)

set(LINKER_SCRIPT "${PROJECT_SOURCE_DIR}/SW4STM32/STM32F103C8Tx_FLASH.ld")
set(CMAKE_C_FLAGS "-mcpu=cortex-m3")

add_executable(${PROJECT_NAME}.elf)

file(GLOB SOURCES CONFIGURE_DEPENDS
  SW4STM32/*.s
  Drivers/STM32F1xx_HAL_Driver/Src/*.c
  Src/*.c
  Src/App/*.c
  Src/Bsp/*.c
)
target_sources(${PROJECT_NAME}.elf PRIVATE ${SOURCES})

target_include_directories(${PROJECT_NAME}.elf PRIVATE
  Drivers/CMSIS/Device/ST/STM32F1xx/Include
  Drivers/CMSIS/Include
  Drivers/STM32F1xx_HAL_Driver/Inc
  Inc
  Src/Bsp
)

target_compile_definitions(${PROJECT_NAME}.elf PRIVATE
  -DSTM32F103xB
  -DUSE_FULL_LL_DRIVER
  -DHSE_VALUE=12000000U
)
target_compile_options(${PROJECT_NAME}.elf PRIVATE
  -mthumb -fno-builtin -Wall -ffunction-sections
  -fdata-sections -fomit-frame-pointer -mabi=aapcs
  $<$<COMPILE_LANGUAGE:ASM>:-x assembler-with-cpp>
  $<$<CONFIG:Debug>:-Og -g>
  $<$<CONFIG:Release>:-Os>
)

target_link_options(${PROJECT_NAME}.elf PRIVATE
  -Wl,--gc-sections --specs=nano.specs --specs=nosys.specs
  -Wl,-Map=${PROJECT_NAME}.map -T${LINKER_SCRIPT}
  $<$<CONFIG:Release>:-flto>
)
target_link_directories(${PROJECT_NAME}.elf PRIVATE)
target_link_libraries(${PROJECT_NAME}.elf PRIVATE
  c
  m
  nosys
)

set_target_properties(${PROJECT_NAME}.elf PROPERTIES
  C_STANDARD 99
  C_STANDARD_REQUIRED ON
  C_EXTENSIONS ON
)

add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
  COMMAND ${CMAKE_OBJCOPY} -Obinary ${PROJECT_NAME}.elf
          ${PROJECT_SOURCE_DIR}/bin/${PROJECT_NAME}.bin
)
