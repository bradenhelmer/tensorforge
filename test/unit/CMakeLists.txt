add_executable(TensorForgeUnitTests
  Frontend/TokenTest.cpp
)

llvm_map_components_to_libnames(LLVM_LIBS Support)

target_link_libraries(TensorForgeUnitTests
  TFFrontend
  GTest::gtest
  GTest::gtest_main
  ${LLVM_LIBS}
)

add_test(NAME TensorForgeUnitTests COMMAND TensorForgeUnitTests)
