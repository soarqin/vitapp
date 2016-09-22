file(GLOB SOURCE_FILES *.cc *.c)
file(GLOB HEADER_FILES *.hh *.h)

include_directories(../libpromoter)
add_library(vitapp STATIC ${SOURCE_FILES} ${HEADER_FILES})
add_dependencies(vitapp libpromoter)
target_link_libraries(vitapp ScePromoterUtil_stub)

set_target_properties(vitapp PROPERTIES PUBLIC_HEADER "${HEADER_FILES}")
install(TARGETS vitapp
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        PUBLIC_HEADER DESTINATION include/vitapp)
