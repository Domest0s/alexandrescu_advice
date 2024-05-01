if(WIN32)
    set(asm_compiler ASM_MASM)
else()
    set(asm_compiler ASM_NASM)
endif()

project(asm_sort LANGUAGES ${asm_compiler})

set(HEADER_FILES
  include/asm_sort/bubble_sort.h
  include/asm_sort/quick_sort.h
)

if(WIN32)
    set(SOURCE_FILES
      bubble_sort_win_masm.asm
      quick_sort_win_masm.asm
    )
else() # UNIX
    set(SOURCE_FILES
      bubble_sort_linux_nasm.asm
      quick_sort_linux_nasm.asm
    )
endif()

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES} ${HEADER_FILES})

source_group("Source files" FILES ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME}
  PUBLIC
    include)

if (UNIX)
    if (CMAKE_BUILD_TYPE STREQUAL "Debug")
      target_compile_options(${PROJECT_NAME} PRIVATE -g -Fdwarf)
    endif()
else()
    message("CMAKE_BUILD_TYPE = ${CMAKE_BUILD_TYPE}")
    if (CMAKE_BUILD_TYPE STREQUAL "Debug")
      target_compile_options(${PROJECT_NAME} PRIVATE /Zi)
    endif()
endif()

# target_compile_options(${PROJECT_NAME} PRIVATE "/largeaddressaware:no")
