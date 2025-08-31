add_library(libmassif2img
                        Logger.cpp
                        Block.cpp
                        Snapshot.cpp
                        CSV.cpp
                        Extension.cpp
                        LineMatcher.cpp
                        MassifFile.cpp
                        BlockAnalyzer.cpp
                        PythonCodegen.cpp
                        Ax.cpp)
add_executable(main main.cpp)

# if(BUILD_BOOST)
# 	add_dependencies(libmassif2img boost)
# endif()

target_link_libraries(libmassif2img PUBLIC ${LIBS})
target_include_directories(libmassif2img PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(main PRIVATE libmassif2img)
target_compile_definitions(main PRIVATE SPDLOG_ACTIVE_LEVEL=SPDLOG_LEVEL_DEBUG)
if(spdlog_FOUND)
target_compile_definitions(main PRIVATE SPDLOG_FMT_EXTERNAL=ON)
target_compile_definitions(libmassif2img PRIVATE SPDLOG_FMT_EXTERNAL=ON)
endif()

install(TARGETS main DESTINATION bin)
