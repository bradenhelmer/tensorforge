find_package(GTest REQUIRED)

add_executable(TensorForgeUnitTests
  Frontend/TokenTest.cpp
)

llvm_map_components_to_libnames(LLVM_LIBS Support)

target_link_libraries(TensorForgeUnitTests
  GTest::gtest
  TFFrontend
  GTest::gtest_main
  ${LLVM_LIBS}
)

add_test(NAME TensorForgeUnitTests COMMAND TensorForgeUnitTests)

add_custom_target(unit
    COMMAND $<TARGET_FILE:TensorForgeUnitTests>
    DEPENDS TensorForgeUnitTests
    COMMENT "Running TensorForge unit tests"
    VERBATIM
)
