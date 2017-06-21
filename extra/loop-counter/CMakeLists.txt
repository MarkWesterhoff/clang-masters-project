set(LLVM_LINK_COMPONENTS support)

add_clang_executable(loop-counter
  LoopCounter.cpp
  )
target_link_libraries(loop-counter
  clangTooling
  clangBasic
  clangASTMatchers
  )