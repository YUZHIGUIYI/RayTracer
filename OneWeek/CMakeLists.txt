file(GLOB_RECURSE OneWeekFiles CONFIGURE_DEPENDS src/*.cpp include/*.h)
add_library(OneWeek STATIC ${OneWeekFiles})
target_include_directories(OneWeek PUBLIC include)