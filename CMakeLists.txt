cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

set(CMAKE_CONFIGURATION_TYPES Debug Profile Release Production CACHE TYPE INTERNAL FORCE )

MACRO(ADD_MSVC_PRECOMPILED_HEADER PrecompiledHeader PrecompiledSource SourcesVar)
  IF(MSVC)
    GET_FILENAME_COMPONENT(PrecompiledBasename ${PrecompiledHeader} NAME_WE)
    SET(PrecompiledBinary "${CMAKE_CURRENT_BINARY_DIR}/${PrecompiledBasename}.pch")
    SET(Sources ${${SourcesVar}})

    SET_SOURCE_FILES_PROPERTIES(${PrecompiledSource}
                                PROPERTIES COMPILE_FLAGS "/Yc\"${PrecompiledHeader}\" /Fp\"${PrecompiledBinary}\""
                                           OBJECT_OUTPUTS "${PrecompiledBinary}")
    SET_SOURCE_FILES_PROPERTIES(${Sources}
                                PROPERTIES COMPILE_FLAGS "/Yu\"${PrecompiledHeader}\" /FI\"${PrecompiledHeader}\" /Fp\"${PrecompiledBinary}\""
                                           OBJECT_DEPENDS "${PrecompiledBinary}")  
    # Add precompiled header to SourcesVar
    LIST(APPEND ${SourcesVar} ${PrecompiledSource})
  ENDIF(MSVC)
ENDMACRO(ADD_MSVC_PRECOMPILED_HEADER)

project(Avro_Arrow)

set(warnings "/W3 /WX")
	
set(CMAKE_CXX_FLAGS "/D WIN32 /D _WINDOWS /GR /Oi /EHsc")	
set(CMAKE_CXX_FLAGS_DEBUG "/D _DEBUG /D AVRO_DEBUG /MTd /Zi /Ob0 /Od /RTC1")
set(CMAKE_CXX_FLAGS_PROFILE "/D NDEBUG /D AVRO_PROFILE /MT /Zi /O2 /Ob1")
set(CMAKE_CXX_FLAGS_RELEASE "/D NDEBUG /D AVRO_RELEASE /MT /O2 /Ob2")
set(CMAKE_CXX_FLAGS_PRODUCTION "/D NDEBUG /D AVRO_PRODUCTION /MT /Ox /Ob2")
	
set(CMAKE_EXE_LINKER_FLAGS "/SUBSYSTEM:WINDOWS")
set(CMAKE_EXE_LINKER_FLAGS_DEBUG "/debug /INCREMENTAL")
set(CMAKE_EXE_LINKER_FLAGS_PROFILE "/debug /INCREMENTAL")
set(CMAKE_EXE_LINKER_FLAGS_RELEASE "/INCREMENTAL:NO")
set(CMAKE_EXE_LINKER_FLAGS_PRODUCTION "/INCREMENTAL:NO")

set(CMAKE_SHARED_LINKER_FLAGS "")
set(CMAKE_SHARED_LINKER_FLAGS_DEBUG "/debug")
set(CMAKE_SHARED_LINKER_FLAGS_PROFILE "/debug")
set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "/INCREMENTAL:NO")
set(CMAKE_SHARED_LINKER_FLAGS_PRODUCTION "/INCREMENTAL:NO")

set(CMAKE_CXX_FLAGS)

if( CMAKE_BUILD_TYPE STREQUAL "" )
	
	set( CMAKE_BUILD_TYPE "Debug")
	
endif ( CMAKE_BUILD_TYPE STREQUAL "" )

add_definitions(${warnings})

#builds engine and rendering engine
add_subdirectory(AVE)
add_subdirectory(ARE)

#loads Avro_Arrow headers
file(GLOB_RECURSE HDRS 
		${Avro_Arrow_SOURCE_DIR}/src/core/*.h
		${Avro_Arrow_SOURCE_DIR}/src/core/*.hxx
		${Avro_Arrow_SOURCE_DIR}/src/core/*.hpp
)

#loads Avro_Arrow source files
file(GLOB_RECURSE SRCS 
		${Avro_Arrow_SOURCE_DIR}/src/core/*.c
		${Avro_Arrow_SOURCE_DIR}/src/core/*.cpp
		${Avro_Arrow_SOURCE_DIR}/src/core/*.cc
		${Avro_Arrow_SOURCE_DIR}/src/core/*.cxx
)

include_directories(
	${Avro_Arrow_SOURCE_DIR}/inc
	${Avro_Arrow_SOURCE_DIR}/src/core
	${Avro_Arrow_SOURCE_DIR}/headers
	${Avro_Arrow_SOURCE_DIR}/sources
	${Avro_Arrow_SOURCE_DIR}/ARE/inc
	${Avro_Arrow_SOURCE_DIR}/ARE/src/core
	${Avro_Arrow_SOURCE_DIR}/ARE/headers
	${Avro_Arrow_SOURCE_DIR}/ARE/sources
	${Avro_Arrow_SOURCE_DIR}/AVE/inc
	${Avro_Arrow_SOURCE_DIR}/AVE/src/core
	${Avro_Arrow_SOURCE_DIR}/AVE/headers
	${Avro_Arrow_SOURCE_DIR}/AVE/sources
	${Avro_Arrow_SOURCE_DIR}/AVE/AvroUtil/inc
	${Avro_Arrow_SOURCE_DIR}/AVE/AvroUtil/src/core
	${Avro_Arrow_SOURCE_DIR}/AVE/AvroUtil/headers
	${Avro_Arrow_SOURCE_DIR}/AVE/AvroUtil/sources
)

set(Avro_Arrow_BIN ${Avro_Arrow_SOURCE_DIR}/bin)
set(Avro_Arrow_TMP ${Avro_Arrow_SOURCE_DIR}/tmp)

#adds Avro_Arrow executable
ADD_MSVC_PRECOMPILED_HEADER("AA_stdafx.h" "${Avro_Arrow_SOURCE_DIR}/src/pch/AA_stdafx.cpp" SRCS)
add_executable (Avro_Arrow ${HDRS} ${SRCS})
set_target_properties(Avro_Arrow PROPERTIES LINKER_LANGUAGE CXX)

set_target_properties(Avro_Arrow PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${Avro_Arrow_BIN}")
set_target_properties(Avro_Arrow PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG "${Avro_Arrow_BIN}/$(Platform)/debug")
set_target_properties(Avro_Arrow PROPERTIES RUNTIME_OUTPUT_DIRECTORY_PROFILE "${Avro_Arrow_BIN}/$(Platform)/profile")
set_target_properties(Avro_Arrow PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE "${Avro_Arrow_BIN}/$(Platform)/release")
set_target_properties(Avro_Arrow PROPERTIES RUNTIME_OUTPUT_DIRECTORY_PRODUCTION "${Avro_Arrow_BIN}/$(Platform)/production")
set_target_properties(Avro_Arrow PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${Avro_Arrow_BIN}")
set_target_properties(Avro_Arrow PROPERTIES LIBRARY_OUTPUT_DIRECTORY_DEBUG "${Avro_Arrow_BIN}/$(Platform)/debug")
set_target_properties(Avro_Arrow PROPERTIES LIBRARY_OUTPUT_DIRECTORY_PROFILE "${Avro_Arrow_BIN}/$(Platform)/profile")
set_target_properties(Avro_Arrow PROPERTIES LIBRARY_OUTPUT_DIRECTORY_RELEASE "${Avro_Arrow_BIN}/$(Platform)/release")
set_target_properties(Avro_Arrow PROPERTIES LIBRARY_OUTPUT_DIRECTORY_PRODUCTION "${Avro_Arrow_BIN}/$(Platform)/production")
set_target_properties(Avro_Arrow PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${Avro_Arrow_BIN}")
set_target_properties(Avro_Arrow PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${Avro_Arrow_BIN}/$(Platform)/debug")
set_target_properties(Avro_Arrow PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_PROFILE "${Avro_Arrow_BIN}/$(Platform)/profile")
set_target_properties(Avro_Arrow PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${Avro_Arrow_BIN}/$(Platform)/release")
set_target_properties(Avro_Arrow PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_PRODUCTION "${Avro_Arrow_BIN}/$(Platform)/production")

set_target_properties(Avro_Arrow PROPERTIES INTERMEDIATE_DIRECTORY "${Avro_Arrow_TMP}")
set_target_properties(Avro_Arrow PROPERTIES INTERMEDIATE_DIRECTORY_DEBUG "${Avro_Arrow_TMP}/$(Platform)/debug")
set_target_properties(Avro_Arrow PROPERTIES INTERMEDIATE_DIRECTORY_PROFILE "${Avro_Arrow_TMP}/$(Platform)/profile")
set_target_properties(Avro_Arrow PROPERTIES INTERMEDIATE_DIRECTORY_RELEASE "${Avro_Arrow_TMP}/$(Platform)/release")
set_target_properties(Avro_Arrow PROPERTIES INTERMEDIATE_DIRECTORY_PRODUCTION "${Avro_Arrow_TMP}/$(Platform)/production")

#links engine and rendering engine
target_link_libraries(Avro_Arrow AVE ARE)