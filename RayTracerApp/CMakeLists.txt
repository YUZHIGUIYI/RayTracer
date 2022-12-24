option(GENERAL_OPTION "General scene" OFF)
option(CORNELL_OPTION "Cornell scene" OFF)
option(VOLUMES_OPTION "Cornell scene with volumes" OFF)

file(GLOB_RECURSE OneWeekendAppSrc CONFIGURE_DEPENDS OneWeekendApp/*.h OneWeekendApp/*.cpp)
add_executable(OneWeekendApplication ${OneWeekendAppSrc})
target_link_libraries(OneWeekendApplication PRIVATE OneWeekend)

file(GLOB_RECURSE OneWeekAppSrc CONFIGURE_DEPENDS OneWeekApp/*.h OneWeekApp/*.cpp)
add_executable(OneWeekApplication ${OneWeekAppSrc})
target_link_libraries(OneWeekApplication PRIVATE OneWeek)

if(GENERAL_OPTION AND (NOT CORNELL_OPTION) AND (NOT VOLUMES_OPTION))
	message(STATUS "Enable general scene render")
	target_compile_definitions(OneWeekApplication PUBLIC GENERAL_RENDER)
endif()

if(CORNELL_OPTION AND (NOT GENERAL_OPTION) AND (NOT VOLUMES_OPTION))
	message(STATUS "Enable cornell box render")
	target_compile_definitions(OneWeekApplication PUBLIC CORNELLBOX_RENDER)
endif()

if(VOLUMES_OPTION AND (NOT GENERAL_OPTION) AND (NOT CORNELL_OPTION))
	message(STATUS "Enable cornell box with volumes render")
	target_compile_definitions(OneWeekApplication PUBLIC VOLUMES_RENDER)
endif()

if((NOT VOLUMES_OPTION) AND (NOT GENERAL_OPTION) AND (NOT CORNELL_OPTION))
	message(STATUS "Enable final scene render")
endif()

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
