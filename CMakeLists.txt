cmake_minimum_required(VERSION 3.18)
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR ARM)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
project(stm32pro C ASM)

set(LINKER_SCRIPT ${PROJECT_SOURCE_DIR}/gcc/STM32F103C8Tx_FLASH.ld)
set(MCPU cortex-m3)

# 递归包含源文件
file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS
  gcc/startup_stm32f103xb.s
  src/*)

# 从源文件中排除
list(REMOVE_ITEM PROJECT_SOURCES)

set(PROJECT_LIST ${PROJECT_NAME}.elf)
foreach(_project ${PROJECT_LIST})
  add_executable(${_project})
  target_sources(${_project} PRIVATE ${PROJECT_SOURCES})

  # 头文件路径
  target_include_directories(${_project} PRIVATE
    src/user
    src/system
    src/public
    src/hardware
    src/hardware/CMSIS/Include
    src/hardware/CMSIS/Device/ST/STM32F1xx/Include
    src/hardware/STM32F1xx_HAL_Driver/Inc
    src/function
    third_party/freertos/repo/include)

  # 预定义
  target_compile_definitions(${_project} PRIVATE
    STM32F103xB
    USE_FULL_LL_DRIVER
    HSE_VALUE=12000000U)

  target_compile_options(${_project} PRIVATE
    $<$<COMPILE_LANGUAGE:C>:-xc>
    $<$<COMPILE_LANGUAGE:ASM>:-x assembler-with-cpp> -mthumb -mcpu=${MCPU}
    $<$<CONFIG:Debug>:-Og> -Wall -ffunction-sections -fdata-sections -MMD)

  target_link_options(${_project} PRIVATE
    -mthumb -mcpu=${MCPU} -T${LINKER_SCRIPT} --specs=nosys.specs
    --specs=nano.specs -Wl,--gc-sections -Wl,--print-memory-usage
    -Wl,-Map=${PROJECT_NAME}.map)

  target_link_libraries(${_project} PRIVATE m)

  set_target_properties(${_project} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
    C_STANDARD 11
    C_STANDARD_REQUIRED ON
    C_EXTENSIONS OFF)

  add_custom_command(TARGET ${_project} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -Oihex $<TARGET_FILE:${_project}>
    ${PROJECT_SOURCE_DIR}/bin/${PROJECT_NAME}.hex)
endforeach()
