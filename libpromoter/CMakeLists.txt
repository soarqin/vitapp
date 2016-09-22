add_custom_command(OUTPUT libScePromoterUtil_stub.a
        COMMAND vita-libs-gen ${CMAKE_CURRENT_SOURCE_DIR}/promoterutil.json building
        COMMAND ${CMAKE_MAKE_PROGRAM} -Cbuilding
        COMMAND ${CMAKE_COMMAND} -E copy building/libScePromoterUtil_stub.a libScePromoterUtil_stub.a
        COMMAND ${CMAKE_COMMAND} -E remove_directory building
        )
add_custom_target(libpromoter DEPENDS libScePromoterUtil_stub.a)
