# set(bitscpp_PREFIX ${CMAKE_CURRENT_BINARY_DIR}/external/bitscpp)
# set(bitscpp_INCLUDE ${bitscpp_PREFIX}/src/bitscpp_dep/include)
# ExternalProject_Add(
#         bitscpp_dep
#         PREFIX ${bitscpp_PREFIX}
#         CONFIGURE_COMMAND ""
#         BUILD_COMMAND ""
#         INSTALL_COMMAND ""
#         CMAKE_ARGS -DCMAKE_CXX_STANDARD=${CMAKE_CXX_STANDARD} -DCMAKE_C_COMPILER='${CMAKE_C_COMPILER}' -DCMAKE_CXX_COMPILER='${CMAKE_CXX_COMPILER}' -DCMAKE_SYSTEM_PROCESSOR=${DCMAKE_SYSTEM_PROCESSOR}
#           -DCMAKE_ASM_FLAGS='${CMAKE_ASM_FLAGS}' -DCMAKE_LINK_FLAGS='${CMAKE_LINK_FLAGS}'
# )

include_directories(../bitscpp_src/include/)


# file(GLOB ExampleFiles ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB ExampleFiles ${CMAKE_CURRENT_SOURCE_DIR}/bitscpp_v2.cpp)
foreach(ExampleFile ${ExampleFiles})
    get_filename_component(ExampleName ${ExampleFile} NAME_WE)
	add_executable(${ExampleName} ${ExampleFile}
		../bitscpp_src/thirdpart/half_float/HalfFloat.cpp
# 		../bitscpp_src/src/ByteReader_v2.cpp
# 		Writer_v2.cxx
# 		../bitscpp_src/src/Endianness.cpp
	)
#     add_dependencies(${ExampleName} bitscpp)
    target_include_directories(${ExampleName} PUBLIC ${bitscpp_INCLUDE})
    target_link_libraries(${ExampleName} PRIVATE Testing::core)
#     target_link_libraries(${ExampleName} PUBLIC bitscpp)
    add_test(NAME test_${ExampleName} COMMAND ${ExampleName})
	set_property(TARGET ${ExampleName} PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
endforeach()


#     get_filename_component(ExampleName bitscpp_v2.cpp NAME_WE)
#     add_executable(${ExampleName} bitscpp_v2.cpp)
#     add_dependencies(${ExampleName} bitscpp)
#     target_include_directories(${ExampleName} PUBLIC ${bitscpp_INCLUDE})
#     target_link_libraries(${ExampleName} PRIVATE Testing::core)
#     target_link_libraries(${ExampleName} PUBLIC bitscpp)
#     add_test(NAME test_${ExampleName} COMMAND ${ExampleName})
