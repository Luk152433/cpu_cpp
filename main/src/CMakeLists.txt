add_library(Function reader.cpp printer.cpp watchdog.cpp analizer.cpp thread.cpp)


target_include_directories(Function 
                        PUBLIC ${PROJECT_SOURCE_DIR}/include/
                        
                        )

#${PROJECT_SOURCE_DIR}/include/
target_link_libraries(Function compiler_flags) 
 