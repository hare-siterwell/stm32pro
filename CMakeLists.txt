cmake_minimum_required(VERSION 3.15)
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR ARM)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
project(stm32pro C ASM)

set(LINKER_SCRIPT "${PROJECT_SOURCE_DIR}/startup/STM32F103C8Tx_FLASH.ld")

file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS
  startup/*.s
  drivers/STM32F1xx_HAL_Driver/Src/*.c
  src/*.c
)

set(PROJECT_LIST ${PROJECT_NAME}.elf)

foreach(_project ${PROJECT_LIST})
  add_executable(${_project})

  target_sources(${_project} PRIVATE ${PROJECT_SOURCES})

  target_include_directories(${_project} PRIVATE
    drivers/CMSIS/Device/ST/STM32F1xx/Include
    drivers/CMSIS/Include
    drivers/STM32F1xx_HAL_Driver/Inc
    src/hardware
    src/system
    src/user
  )

  target_compile_definitions(${_project} PRIVATE
    -DSTM32F103xB
    -DUSE_FULL_LL_DRIVER
    -DHSE_VALUE=12000000U
  )

  target_compile_options(${_project} PRIVATE
    $<$<COMPILE_LANGUAGE:C>:-mcpu=cortex-m3>
    -mthumb -fno-builtin -Wall -ffunction-sections
    -fdata-sections -fomit-frame-pointer -mabi=aapcs
    $<$<COMPILE_LANGUAGE:ASM>:-x assembler-with-cpp>
    $<$<CONFIG:Debug>:-Og -g>
    $<$<CONFIG:Release>:-Os>
  )

  target_link_options(${_project} PRIVATE
    -Wl,--gc-sections --specs=nano.specs --specs=nosys.specs
    -Wl,-Map=${PROJECT_NAME}.map -T${LINKER_SCRIPT}
    $<$<CONFIG:Release>:-flto>
  )

  target_link_libraries(${_project} PRIVATE
    c
    m
    nosys
  )

  set_target_properties(${_project} PROPERTIES
    C_STANDARD 99
    C_STANDARD_REQUIRED ON
    C_EXTENSIONS ON
  )

  add_custom_command(TARGET ${_project} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -Oihex $<TARGET_FILE:${_project}>
    ${PROJECT_SOURCE_DIR}/bin/${PROJECT_NAME}.hex
  )
endforeach()
