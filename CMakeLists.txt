cmake_minimum_required(VERSION 3.7)
include(macros.cmake)
project(hlvm-runtime)

#include_directories("v8")
include_directories(include)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_STANDARD 14)
use_riscv_musl_toolchain(64)
set(SOURCE_FILES
        helpers.cpp
        helpers.h
		library.h
        jsvalue.h
        math.cpp
		meta.cpp
        math.h
        machine.cpp
        machine_riscv.h
		machine.h
		time.h
		time.cpp
		string.cpp
		rule_functions/fetch_trigger_data.cpp
		rule_functions/fetch_trigger_data.h
		rule_functions/rule_params.h
		rule_functions/rule_api.cpp
		#v8/src/base/platform/mutex.cc
		#v8/src/base/platform/time.cc
		#v8/src/base/platform/semaphore.cc
		#v8/src/base/bits.cc
		#v8/src/base/once.cc
		#v8/src/base/logging.cc
		#v8/src/base/utils/random-number-generator.cc
)

if (WIN32)
    set(
        SOURCE_FILES
        ${SOURCE_FILES}
        v8/src/base/platform/platform-win32.cc
    )
else()
	#set(
	    #SOURCE_FILES
	    #${SOURCE_FILES}
	    #v8/src/base/platform/platform-posix.cc
	    #v8/src/base/platform/platform-posix-time.cc
	    #)
endif()

if (APPLE)
    set(
        SOURCE_FILES
        ${SOURCE_FILES}
        v8/src/base/platform/platform-macos.cc
    )
endif()

if (LINUX)
	#set(
	#SOURCE_FILES
	#${SOURCE_FILES}
	#v8/src/base/platform/platform-linux.cc
	#)
endif()

add_library(hlvm-runtime STATIC ${SOURCE_FILES})
#target_link_libraries(hlvm-runtime "-static" "-lstdc++")
