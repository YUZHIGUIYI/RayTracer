file(GLOB_RECURSE OneWeekendAppSrc CONFIGURE_DEPENDS OneWeekendApp/*.h OneWeekendApp/*.cpp)
add_executable(OneWeekendApplication ${OneWeekendAppSrc})
target_link_libraries(OneWeekendApplication PRIVATE OneWeekend)