# TensorForge Lit test runner config

import os
import lit.formats
from lit.llvm import llvm_config

config.name = "TensorForge"
config.test_format = lit.formats.ShTest(not llvm_config.use_lit_shell)

config.suffixes = [
    ".tf"
]

config.excludes = [
    "CMakeLists.txt",
    "README.txt",
    "LICENSE.txt",
]

config.test_source_root = os.path.dirname(__file__)
config.test_exec_root = os.path.join(config.tensorforge_obj_root, "test")

llvm_config.use_default_substitutions()

tool_dirs = [config.tensorforge_tools_dir]

tools = [
    "tensorforge"
]

llvm_config.add_tool_substitutions(tools, tool_dirs)
