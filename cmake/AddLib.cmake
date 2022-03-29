macro(add_static_lib LIB_NAME LIB_PATH)
add_library(${LIB_NAME} STATIC IMPORTED)
set_target_properties(${LIB_NAME}  PROPERTIES IMPORTED_LOCATION ${LIB_PATH})
endmacro(add_static_lib)

macro(add_dynamic_lib LIB_NAME LIB_PATH)
add_library(${LIB_NAME} SHARED IMPORTED)
set_target_properties(${LIB_NAME}  PROPERTIES IMPORTED_LOCATION ${LIB_PATH})
endmacro(add_dynamic_lib)
