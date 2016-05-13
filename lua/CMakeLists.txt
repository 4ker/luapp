project(lua)

if(MINGW)   # TODO: 查阅这些编译选项的意义
    add_definitions(-O2 -g -Wall -Wextra -Werror)
elseif(UNIX)
    add_definitions(-O2 -g -Wall -Wextra -Werror -fPIC -DLUA_USE_POSIX)
    include_directories(/usr/include)
    link_directories(/usr/lib)
endif()

set(SOURCE  # 也可以用 file( GLOB SOURCE *.c ) # 甚至 GLOB -> GLOB_RECURSE
    lapi.c
    lauxlib.c
    lbaselib.c
    lbitlib.c
    lcode.c
    lcorolib.c
    lctype.c
    ldblib.c
    ldebug.c
    ldo.c
    ldump.c
    lfunc.c
    lgc.c
    linit.c
    liolib.c
    llex.c
    lmathlib.c
    lmem.c
    loadlib.c
    lobject.c
    lopcodes.c
    loslib.c
    lparser.c
    lstate.c
    lstring.c
    lstrlib.c
    ltable.c
    ltablib.c
    ltm.c
    lundump.c
    lutf8lib.c
    lvm.c
    lzio.c
    )

# C 的 链接方式和 C++ 不一样
set_source_files_properties(${SOURCE} PROPERTIES LANGUAGE C)

set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR})  # 这个配置
add_library(lua STATIC ${SOURCE})               # 会影响到这个 library 的安装

if(MSVC)                                        # 但 MSVC 有自己的安装方式，所以需要额外的配置
    set_target_properties( lua PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY            ${PROJECT_BINARY_DIR}
        LIBRARY_OUTPUT_DIRECTORY_DEBUG      ${PROJECT_BINARY_DIR}
        LIBRARY_OUTPUT_DIRECTORY_RELEASE    ${PROJECT_BINARY_DIR}
        RUNTIME_OUTPUT_DIRECTORY            ${PROJECT_BINARY_DIR}
        RUNTIME_OUTPUT_DIRECTORY_DEBUG      ${PROJECT_BINARY_DIR}
        RUNTIME_OUTPUT_DIRECTORY_RELEASE    ${PROJECT_BINARY_DIR}
        ARCHIVE_OUTPUT_DIRECTORY            ${PROJECT_BINARY_DIR}
        ARCHIVE_OUTPUT_DIRECTORY_DEBUG      ${PROJECT_BINARY_DIR}
        ARCHIVE_OUTPUT_DIRECTORY_RELEASE    ${PROJECT_BINARY_DIR}
    )
endif()