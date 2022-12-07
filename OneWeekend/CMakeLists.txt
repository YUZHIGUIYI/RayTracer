file(GLOB_RECURSE OneWeekendFiles CONFIGURE_DEPENDS src/*.cpp include/*.h)
add_library(OneWeekend STATIC ${OneWeekendFiles})
target_include_directories(OneWeekend PUBLIC include)