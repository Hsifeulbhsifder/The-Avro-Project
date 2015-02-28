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

set(CMAKE_CXX_FLAGS "/D WIN32 /D _WINDOWS /GR /EHsc")	
set(CMAKE_CXX_FLAGS_DEBUG "/D _DEBUG /D AVRO_DEBUG /MTd /Zi /Ob0 /Od /RTC1")
set(CMAKE_CXX_FLAGS_PROFILE "/D NDEBUG /D AVRO_PROFILE /MT /Zi /O2 /Ob1 /RTC1")
set(CMAKE_CXX_FLAGS_RELEASE "/D NDEBUG /D AVRO_RELEASE /MT /O2 /Ob2 /RTCs")
set(CMAKE_CXX_FLAGS_PRODUCTION "/D NDEBUG /D AVRO_PRODUCTION /MT /Ox /Ob2")
	
set(CMAKE_SHARED_LINKER_FLAGS "")
set(CMAKE_SHARED_LINKER_FLAGS_DEBUG "/debug /INCREMENTAL")
set(CMAKE_SHARED_LINKER_FLAGS_PROFILE "/debug /INCREMENTAL")
set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "/INCREMENTAL :NO")
set(CMAKE_SHARED_LINKER_FLAGS_PRODUCTION "/INCREMENTAL :NO")

set(ARE_DIR ${Avro_Arrow_SOURCE_DIR}/ARE)
set(ARE_BIN ${ARE_DIR}/bin)
set(ARE_TMP ${ARE_DIR}/tmp)

file(GLOB_RECURSE HDRS 
		${ARE_DIR}/src/core/*.h
		${ARE_DIR}/src/core/*.hxx
		${ARE_DIR}/src/core/*.hpp
)

#loads source files
file(GLOB_RECURSE SRCS 
		${ARE_DIR}/src/core/*.c
		${ARE_DIR}/src/core/*.cpp
		${ARE_DIR}/src/core/*.cc
		${ARE_DIR}/src/core/*.cxx
)

include_directories(
	${ARE_DIR}/inc
	${ARE_DIR}/src/core
	${ARE_DIR}/headers
	${ARE_DIR}/sources
	${Avro_Arrow_SOURCE_DIR}/AVE/AvroUtil/inc
	${Avro_Arrow_SOURCE_DIR}/AVE/AvroUtil/src/core
	${Avro_Arrow_SOURCE_DIR}/AVE/AvroUtil/headers
	${Avro_Arrow_SOURCE_DIR}/AVE/AvroUtil/sources
)

#adds the library
ADD_MSVC_PRECOMPILED_HEADER("ARE_stdafx.h" "${ARE_DIR}/src/pch/ARE_stdafx.cpp" SRCS)
add_library(ARE SHARED ${HDRS} ${SRCS})
set_target_properties(ARE PROPERTIES LINKER_LANGUAGE CXX)

set_target_properties(ARE PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${Avro_Arrow_SOURCE_DIR}/bin")
set_target_properties(ARE PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG "${Avro_Arrow_SOURCE_DIR}/bin/$(Platform)/debug")
set_target_properties(ARE PROPERTIES RUNTIME_OUTPUT_DIRECTORY_PROFILE "${Avro_Arrow_SOURCE_DIR}/bin/$(Platform)/profile")
set_target_properties(ARE PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE "${Avro_Arrow_SOURCE_DIR}/bin/$(Platform)/release")
set_target_properties(ARE PROPERTIES RUNTIME_OUTPUT_DIRECTORY_PRODUCTION "${Avro_Arrow_SOURCE_DIR}/bin/$(Platform)/production")
set_target_properties(ARE PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${ARE_BIN}")
set_target_properties(ARE PROPERTIES LIBRARY_OUTPUT_DIRECTORY_DEBUG "${ARE_BIN}/$(Platform)/debug")
set_target_properties(ARE PROPERTIES LIBRARY_OUTPUT_DIRECTORY_PROFILE "${ARE_BIN}/$(Platform)/profile")
set_target_properties(ARE PROPERTIES LIBRARY_OUTPUT_DIRECTORY_RELEASE "${ARE_BIN}/$(Platform)/release")
set_target_properties(ARE PROPERTIES LIBRARY_OUTPUT_DIRECTORY_PRODUCTION "${ARE_BIN}/$(Platform)/production")
set_target_properties(ARE PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${ARE_BIN}")
set_target_properties(ARE PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${ARE_BIN}/$(Platform)/debug")
set_target_properties(ARE PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_PROFILE "${ARE_BIN}/$(Platform)/profile")
set_target_properties(ARE PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${ARE_BIN}/$(Platform)/release")
set_target_properties(ARE PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_PRODUCTION "${ARE_BIN}/$(Platform)/production")

set_target_properties(ARE PROPERTIES VS_INTERMEDIATE_DIRECTORY "${ARE_TMP}")
set_target_properties(ARE PROPERTIES VS_INTERMEDIATE_DIRECTORY_DEBUG "${ARE_TMP}/$(Platform)/debug")
set_target_properties(ARE PROPERTIES VS_INTERMEDIATE_DIRECTORY_PROFILE "${ARE_TMP}/$(Platform)/profile")
set_target_properties(ARE PROPERTIES VS_INTERMEDIATE_DIRECTORY_RELEASE "${ARE_TMP}/$(Platform)/release")
set_target_properties(ARE PROPERTIES VS_INTERMEDIATE_DIRECTORY_PRODUCTION "${ARE_TMP}/$(Platform)/production")

#links utilities
target_link_libraries(ARE AvroUtil)

install (TARGETS ARE RUNTIME DESTINATION "${Avro_Arrow_SOURCE_DIR}/bin/$(Platform)/$(Configuration)")