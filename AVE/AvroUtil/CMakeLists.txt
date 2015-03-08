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
set(CMAKE_CXX_FLAGS_PROFILE "/D NDEBUG /D AVRO_PROFILE /MT /Zi /O2 /Ob1")
set(CMAKE_CXX_FLAGS_RELEASE "/D NDEBUG /D AVRO_RELEASE /MT /O2 /Ob2")
set(CMAKE_CXX_FLAGS_PRODUCTION "/D NDEBUG /D AVRO_PRODUCTION /MT /Ox /Ob2")
	
set(CMAKE_SHARED_LINKER_FLAGS "")
set(CMAKE_SHARED_LINKER_FLAGS_DEBUG "/debug /INCREMENTAL")
set(CMAKE_SHARED_LINKER_FLAGS_PROFILE "/debug /INCREMENTAL")
set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "/INCREMENTAL:NO")
set(CMAKE_SHARED_LINKER_FLAGS_PRODUCTION "/INCREMENTAL:NO")

set(AvroUtil_DIR ${Avro_Arrow_SOURCE_DIR}/AVE/AvroUtil)
set(AvroUtil_BIN ${AvroUtil.DIR}/bin)
set(AvroUtil_TMP ${AvroUtil_DIR}/tmp)

#loads headers
file(GLOB_RECURSE HDRS 
		${AvroUtil_DIR}/src/core/*.h
		${AvroUtil_DIR}/src/core/*.hxx
		${AvroUtil_DIR}/src/core/*.hpp
)

#loads source files
file(GLOB_RECURSE SRCS 
		${AvroUtil_DIR}/src/core/*.c
		${AvroUtil_DIR}/src/core/*.cpp
		${AvroUtil_DIR}/src/core/*.cc
		${AvroUtil_DIR}/src/core/*.cxx
)

include_directories(
	${AvroUtil_DIR}/inc
	${AvroUtil_DIR}/src/core
	${AvroUtil_DIR}/headers
	${AvroUtil_DIR}/sources
)

#add the library
ADD_MSVC_PRECOMPILED_HEADER("AU_stdafx.h" "${AvroUtil_DIR}/src/pch/AU_stdafx.cpp" SRCS)
add_library(AvroUtil STATIC ${HDRS} ${SRCS})

set_target_properties(AvroUtil PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${AvroUtil_BIN}")
set_target_properties(AvroUtil PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG "${AvroUtil_BIN}/$(Platform)/debug")
set_target_properties(AvroUtil PROPERTIES RUNTIME_OUTPUT_DIRECTORY_PROFILE "${AvroUtil_BIN}/$(Platform)/profile")
set_target_properties(AvroUtil PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE "${AvroUtil_BIN}/$(Platform)/release")
set_target_properties(AvroUtil PROPERTIES RUNTIME_OUTPUT_DIRECTORY_PRODUCTION "${AvroUtil_BIN}/$(Platform)/production")
set_target_properties(AvroUtil PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${AvroUtil_BIN}")
set_target_properties(AvroUtil PROPERTIES LIBRARY_OUTPUT_DIRECTORY_DEBUG "${AvroUtil_BIN}/$(Platform)/debug")
set_target_properties(AvroUtil PROPERTIES LIBRARY_OUTPUT_DIRECTORY_PROFILE "${AvroUtil_BIN}/$(Platform)/profile")
set_target_properties(AvroUtil PROPERTIES LIBRARY_OUTPUT_DIRECTORY_RELEASE "${AvroUtil_BIN}/$(Platform)/release")
set_target_properties(AvroUtil PROPERTIES LIBRARY_OUTPUT_DIRECTORY_PRODUCTION "${AvroUtil_BIN}/$(Platform)/production")
set_target_properties(AvroUtil PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${AvroUtil_BIN}")
set_target_properties(AvroUtil PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${AvroUtil_BIN}/$(Platform)/debug")
set_target_properties(AvroUtil PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_PROFILE "${AvroUtil_BIN}/$(Platform)/profile")
set_target_properties(AvroUtil PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${AvroUtil_BIN}/$(Platform)/release")
set_target_properties(AvroUtil PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_PRODUCTION "${AvroUtil_BIN}/$(Platform)/production")

set_target_properties(AvroUtil PROPERTIES INTERMEDIATE_DIRECTORY "${AvroUtil_TMP}")
set_target_properties(AvroUtil PROPERTIES INTERMEDIATE_DIRECTORY_DEBUG "${AvroUtil_TMP}/$(Platform)/debug")
set_target_properties(AvroUtil PROPERTIES INTERMEDIATE_DIRECTORY_PROFILE "${AvroUtil_TMP}/$(Platform)/profile")
set_target_properties(AvroUtil PROPERTIES INTERMEDIATE_DIRECTORY_RELEASE "${AvroUtil_TMP}/$(Platform)/release")
set_target_properties(AvroUtil PROPERTIES INTERMEDIATE_DIRECTORY_PRODUCTION "${AvroUtil_TMP}/$(Platform)/production")

