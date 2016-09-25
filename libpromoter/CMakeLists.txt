SET (TARGETLIB ${CMAKE_CURRENT_BINARY_DIR}/libScePromoterUtil_stub.a)

execute_process(COMMAND ${CMAKE_VITASDK}/bin/vita-libs-gen ${CMAKE_CURRENT_SOURCE_DIR}/promoterutil.json ${CMAKE_CURRENT_BINARY_DIR}/build_libs)

file(GLOB AS_FILES ${CMAKE_CURRENT_BINARY_DIR}/build_libs/*.S)

set(AS_COMMAND true)
set(AR_COMMAND ${CMAKE_VITASDK_PREFIX}ar cru ${TARGETLIB})
foreach(file ${AS_FILES})
    get_filename_component(name ${file} NAME_WE)
    list(APPEND AS_COMMAND && ${CMAKE_VITASDK_PREFIX}as ${file} -o ${name}.o)
    list(APPEND AR_COMMAND ${name}.o)
endforeach(file)

add_custom_command(OUTPUT ${TARGETLIB}
    COMMAND ${AS_COMMAND}
    COMMAND ${AR_COMMAND}
    COMMAND ${CMAKE_VITASDK_PREFIX}ranlib ${TARGETLIB}
)

add_custom_target(libpromoter_target DEPENDS ${TARGETLIB})
add_library(libpromoter STATIC IMPORTED GLOBAL)
add_dependencies(libpromoter libpromoter_target)
set_target_properties(libpromoter PROPERTIES IMPORTED_LOCATION ${TARGETLIB} INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR})