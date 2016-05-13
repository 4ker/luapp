# project(CallFunctionFromLua)

if(MINGW)
	add_definitions(-O2 -g -Wall -Wextra -Werror)
elseif(UNIX)
	add_definitions(-O2 -g -Wall -Wextra -Werror)
endif()

set(NAME "CallFunctionFromLua")

include_directories(${LUAPP_INCLUDE_DIR})
link_directories(   ${LUAPP_LIBRARY_DIR})

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})

add_executable(${NAME} CallFunctionFromLua.cpp)

target_link_libraries(${NAME} ${LUAPP_LIBRARY_NAME})

# 结果就是，安装到了 build\examples\CallFunctionFromLua 目录
# 如果不定义 `project(CallFunctionFromLua)'（我已经把它注释了），
# 则会安装到上一个（层） project 的 binary dir: 这里的情况就是 \build 目录。
if(MSVC)
	set_target_properties(${NAME} PROPERTIES
		RUNTIME_OUTPUT_DIRECTORY            ${PROJECT_BINARY_DIR}
		RUNTIME_OUTPUT_DIRECTORY_DEBUG      ${PROJECT_BINARY_DIR}
		RUNTIME_OUTPUT_DIRECTORY_RELEASE    ${PROJECT_BINARY_DIR}
		ARCHIVE_OUTPUT_DIRECTORY            ${PROJECT_BINARY_DIR}
		ARCHIVE_OUTPUT_DIRECTORY_DEBUG      ${PROJECT_BINARY_DIR}
		ARCHIVE_OUTPUT_DIRECTORY_RELEASE    ${PROJECT_BINARY_DIR}
	)
endif()
