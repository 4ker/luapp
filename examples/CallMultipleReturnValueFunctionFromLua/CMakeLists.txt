project(CallMultipleReturnValueFunctionFromLua)

if(MINGW)
	add_definitions(-O2 -g -Wall -Wextra -Werror)
elseif(UNIX)
	add_definitions(-O2 -g -Wall -Wextra -Werror)
endif()

set(NAME "CallMultipleReturnValueFunctionFromLua")

include_directories(${LUAPP_INCLUDE_DIR})
link_directories(   ${LUAPP_LIBRARY_DIR})

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})

add_executable(${NAME} CallMultipleReturnValueFunctionFromLua.cpp)

target_link_libraries(${NAME} ${LUAPP_LIBRARY_NAME})

if(MSVC)
	set_target_properties(${NAME} PROPERTIES
    # 这些是生成的 binary 的路径    
		RUNTIME_OUTPUT_DIRECTORY            ${PROJECT_BINARY_DIR}
		RUNTIME_OUTPUT_DIRECTORY_DEBUG      ${PROJECT_BINARY_DIR}
		RUNTIME_OUTPUT_DIRECTORY_RELEASE    ${PROJECT_BINARY_DIR}
		ARCHIVE_OUTPUT_DIRECTORY            ${PROJECT_BINARY_DIR}
		ARCHIVE_OUTPUT_DIRECTORY_DEBUG      ${PROJECT_BINARY_DIR}
		ARCHIVE_OUTPUT_DIRECTORY_RELEASE    ${PROJECT_BINARY_DIR}
	)
    # 这是 install 的路径
    install( TARGETS ${NAME} DESTINATION bin )
endif()
