cmake_minimum_required(VERSION 3.7.2)

set(CMAKE_USE_RELATIVE_PATHS TRUE)
project("clpp")
set("PROJECT_DESCRIPTION" "")
set("PROJECT_HOMEPAGE_URL" "https://github.com/makerbot/clp-parser")  # also https://sourceforge.net/project/clp-parser

set(CPACK_PACKAGE_VENDOR "Denis Shevchenko")
set(CPACK_PACKAGE_VERSION_MAJOR "0")
set(CPACK_PACKAGE_VERSION_MINOR "0")
set(CPACK_PACKAGE_VERSION_PATCH "0")
set(CPACK_PACKAGE_VERSION "${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}")

set(OUR_CMAKE_MODULES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
set(OUR_CMAKE_3PARTY_MODULES_DIR "${OUR_CMAKE_MODULES_DIR}/thirdParty")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${OUR_CMAKE_MODULES_DIR}" "${OUR_CMAKE_3PARTY_MODULES_DIR}" "${OUR_CMAKE_3PARTY_MODULES_DIR}/Boilerplate" "${OUR_CMAKE_3PARTY_MODULES_DIR}/DoxygenUtils")


include(Boilerplate)
include(DoxygenUtils)

set(BOOST_COMPS "filesystem;regex")

find_package(Boost COMPONENTS ${BOOST_COMPS} REQUIRED)

set(BCS_LINK "")
foreach(bc ${BOOST_COMPS})
	set(BCS_LINK "${BCS_LINK};Boost::${bc}")
endforeach()

set(Include_dir "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(Examples_Dir "${CMAKE_CURRENT_SOURCE_DIR}/example")

buildAndPackageLib("${PROJECT_NAME}"
	DO_NOT_PASSTHROUGH
	TYPE INTERFACE
	COMPONENT "lib"
	DESCRIPTION "${PROJECT_DESCRIPTION}"
	PUBLIC_INCLUDES ${Include_dir}
	PUBLIC_LIBS ${BCS_LINK}
)

option(WITH_EXAMPLES "Build examples" OFF)
if(WITH_EXAMPLES)
	file(GLOB_RECURSE EXAMPLES "${Examples_Dir}/*.cpp")
	foreach(example ${EXAMPLES})
		get_filename_component(exampleName "${example}" NAME_WE)
		add_executable("${exampleName}" "${example}")
		harden("${exampleName}")
		add_sanitizers("${exampleName}")
		target_include_directories("${exampleName}" PRIVATE "${Include_dir}")
		target_link_libraries("${exampleName}" "${PROJECT_NAME}")
	endforeach()
endif()

option(WITH_DOCS "Build docs" ON)
if(WITH_DOCS)
	find_package(Doxygen REQUIRED dot)

	load_doxyfile("${CMAKE_CURRENT_SOURCE_DIR}/doc/Doxyfile")
	set(DOXYGEN_PROJECT_BRIEF "${CPACK_PACKAGE_DESCRIPTION}")
	set(DOXYGEN_USE_MDFILE_AS_MAINPAGE "${CPACK_RESOURCE_FILE_README}")

	set("DOXYGEN_GENERATE_HTML" YES)
	set("DOXYGEN_GENERATE_MAN" YES)

	set(DOXYGEN_EXAMPLE_PATH "${Examples_Dir}")
	set(DOXYGEN_STRIP_FROM_PATH "${Include_dir}/clpp")
	set(DOXYGEN_STRIP_FROM_INC_PATH "${Include_dir}/clpp")


	file(GLOB_RECURSE HEADERS "${Include_dir}/*.h" "${Include_dir}/*.hxx" "${Include_dir}/*.hpp")
	doxygen_add_docs(docs
		"${HEADERS}"
		ALL
		USE_STAMP_FILE
	)
endif()

#pass_through_cpack_vars()

include(CPack)
