IF(CMAKE_SIZEOF_VOID_P EQUAL 8)
	ADD_DEFINITIONS(-DX64)
ELSE()
	ADD_DEFINITIONS(-DX86)
ENDIF(CMAKE_SIZEOF_VOID_P EQUAL 8)