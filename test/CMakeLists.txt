configure_lit_site_cfg(
  ${CMAKE_CURRENT_SOURCE_DIR}/lit.site.cfg.py.in
  ${CMAKE_CURRENT_BINARY_DIR}/lit.site.cfg.py
  MAIN_CONFIG
  ${CMAKE_CURRENT_SOURCE_DIR}/lit.cfg.py
  PATHS
  "TENSORFORGE_SOURCE_DIR"
  "TENSORFORGE_BINARY_DIR"
  "TENSORFORGE_TOOLS_DIR"
)

add_lit_testsuite(check-tensorforge "Running TensorForge regression tests"
    ${CMAKE_CURRENT_BINARY_DIR}
)
