add_executable(massif2imgTest test.cpp)
if(BUILD_BOOST)
	add_dependencies(massif2imgTest boost)
endif()
target_link_libraries(massif2imgTest PRIVATE Catch2WithMain libmassif2img)

configure_file(massif.1.out massif.1.out COPYONLY)
add_test(NAME massif2imgTest COMMAND massif2imgTest)
