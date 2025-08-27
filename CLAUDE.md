# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

TensorForge is an MLIR-based tensor compiler for GPUs. It's built as a modern compiler using LLVM/MLIR infrastructure with a traditional frontend-to-backend architecture.

## Build System

This project uses CMake with LLVM/MLIR integration:

- **Build**: `cmake -B build && cmake --build build`
- **Format code**: `cmake --build build --target format`
- **Check formatting**: `cmake --build build --target format-check`

The project requires LLVM/MLIR to be installed and discoverable by CMake. The build system automatically configures compiler flags to match LLVM's build configuration (RTTI, exceptions, etc.).

## Architecture

The codebase follows a layered compiler architecture:

- **Frontend** (`lib/Frontend/`, `include/TensorForge/Frontend/`):
  - `Token.h/TokenMacros.h`: Token definitions using X-macro pattern for maintainability
  - `Lexer.h/.cpp`: Lexical analysis (currently skeleton)
  - `Parser.h/.cpp`: Syntax analysis (currently skeleton)
  - `AST.h`: Abstract syntax tree definitions (currently skeleton)

- **Main executable** (`tools/tensorforge/`):
  - `tensorforge.cpp`: Main compiler driver using LLVM CommandLine library

The project uses CMake's modular structure with separate libraries:
- `TFFrontend`: Shared library containing frontend components
- `tensorforge`: Main executable linking against TFFrontend and LLVM

## Code Style

- Uses clang-format for consistent formatting
- C++17 standard
- LLVM/MLIR coding conventions
- Include guards follow pattern: `TF_<COMPONENT>_<FILE>_H`
- Namespace: `tensorforge`

## Development Status

This is an early-stage project with basic infrastructure in place. The frontend components (lexer, parser, AST) are currently skeleton implementations.