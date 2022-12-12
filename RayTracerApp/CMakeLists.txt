file(GLOB_RECURSE OneWeekendAppSrc CONFIGURE_DEPENDS OneWeekendApp/*.h OneWeekendApp/*.cpp)
add_executable(OneWeekendApplication ${OneWeekendAppSrc})
target_link_libraries(OneWeekendApplication PRIVATE OneWeekend)

file(GLOB_RECURSE OneWeekAppSrc CONFIGURE_DEPENDS OneWeekApp/*.h OneWeekApp/*.cpp)
add_executable(OneWeekApplication ${OneWeekAppSrc})
target_link_libraries(OneWeekApplication PRIVATE OneWeek)

add_custom_command(
		TARGET OneWeekApplication 
		POST_BUILD 
		COMMAND 
			${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/texture ${PROJECT_SOURCE_DIR}/bin/texture
)

enable_testing()

add_test(
        NAME OneWeekApplicationTest
        COMMAND $<TARGET_FILE:OneWeekApplication> 12 > imageTwo.ppm
)
