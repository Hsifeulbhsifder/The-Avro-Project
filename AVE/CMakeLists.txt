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

set(warnings "/W3 /WX")
	
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

#builds utilities
add_subdirectory(AvroUtil)

set(AVE_DIR ${Avro_Arrow_SOURCE_DIR}/AVE)
set(AVE_BIN ${AVE_DIR}/bin)
set(AVE_TMP ${AVE_DIR}/tmp)

#loads headers
file(GLOB_RECURSE HDRS 
		${AVE_DIR}/src/core/*.h
		${AVE_DIR}/src/core/*.hxx
		${AVE_DIR}/src/core/*.hpp
)

#loads source files
file(GLOB_RECURSE SRCS 
		${AVE_DIR}/src/core/*.c
		${AVE_DIR}/src/core/*.cpp
		${AVE_DIR}/src/core/*.cc
		${AVE_DIR}/src/core/*.cxx
)

include_directories(
	${AVE_DIR}/inc
	${AVE_DIR}/src/core
	${AVE_DIR}/headers
	${AVE_DIR}/sources
	${Avro_Arrow_SOURCE_DIR}/ARE/inc
	${Avro_Arrow_SOURCE_DIR}/ARE/src/core
	${Avro_Arrow_SOURCE_DIR}/ARE/headers
	${Avro_Arrow_SOURCE_DIR}/ARE/sources
	${AVE_DIR}/AvroUtil/inc
	${AVE_DIR}/AvroUtil/src/core
	${AVE_DIR}/AvroUtil/headers
	${AVE_DIR}/AvroUtil/sources
)

#adds the library
ADD_MSVC_PRECOMPILED_HEADER("AVE_stdafx.h" "${AVE_DIR}/src/pch/AVE_stdafx.cpp" SRCS)
add_library(AVE SHARED ${HDRS} ${SRCS})
set_target_properties(AVE PROPERTIES LINKER_LANGUAGE CXX)

set_target_properties(AVE PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${Avro_Arrow_SOURCE_DIR}/bin")
set_target_properties(AVE PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG "${Avro_Arrow_SOURCE_DIR}/bin/$(Platform)/debug")
set_target_properties(AVE PROPERTIES RUNTIME_OUTPUT_DIRECTORY_PROFILE "${Avro_Arrow_SOURCE_DIR}/bin/$(Platform)/profile")
set_target_properties(AVE PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE "${Avro_Arrow_SOURCE_DIR}/bin/$(Platform)/release")
set_target_properties(AVE PROPERTIES RUNTIME_OUTPUT_DIRECTORY_PRODUCTION "${Avro_Arrow_SOURCE_DIR}/bin/$(Platform)/production")
set_target_properties(AVE PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${AVE_BIN}")
set_target_properties(AVE PROPERTIES LIBRARY_OUTPUT_DIRECTORY_DEBUG "${AVE_BIN}/$(Platform)/debug")
set_target_properties(AVE PROPERTIES LIBRARY_OUTPUT_DIRECTORY_PROFILE "${AVE_BIN}/$(Platform)/profile")
set_target_properties(AVE PROPERTIES LIBRARY_OUTPUT_DIRECTORY_RELEASE "${AVE_BIN}/$(Platform)/release")
set_target_properties(AVE PROPERTIES LIBRARY_OUTPUT_DIRECTORY_PRODUCTION "${AVE_BIN}/$(Platform)/production")
set_target_properties(AVE PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${AVE_BIN}")
set_target_properties(AVE PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${AVE_BIN}/$(Platform)/debug")
set_target_properties(AVE PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_PROFILE "${AVE_BIN}/$(Platform)/profile")
set_target_properties(AVE PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${AVE_BIN}/$(Platform)/release")
set_target_properties(AVE PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_PRODUCTION "${AVE_BIN}/$(Platform)/production")

set_target_properties(AVE PROPERTIES VS_INTERMEDIATE_DIRECTORY "${AVE_TMP}")
set_target_properties(AVE PROPERTIES VS_INTERMEDIATE_DIRECTORY_DEBUG "${AVE_TMP}/$(Platform)/debug")
set_target_properties(AVE PROPERTIES VS_INTERMEDIATE_DIRECTORY_PROFILE "${AVE_TMP}/$(Platform)/profile")
set_target_properties(AVE PROPERTIES VS_INTERMEDIATE_DIRECTORY_RELEASE "${AVE_TMP}/$(Platform)/release")
set_target_properties(AVE PROPERTIES VS_INTERMEDIATE_DIRECTORY_PRODUCTION "${AVE_TMP}/$(Platform)/production")

#links utilities and rendering engine
target_link_libraries(AVE AvroUtil)
target_link_libraries(AVE ARE)

install (TARGETS AVE RUNTIME DESTINATION "${Avro_Arrow_SOURCE_DIR}/bin/$(Platform)/$(Configuration)")