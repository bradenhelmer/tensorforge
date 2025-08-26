add_executable(
    tensorforge
    tensorforge.cpp
)

llvm_map_components_to_libnames(LLVM_LIBS Option Support)

target_link_libraries(
    tensorforge
    TFFrontend
    ${LLVM_LIBS}
)
