include(FetchContent)
find_package(Doxygen)

# Declare doxygen-awesome-css dependency.
FetchContent_Declare(
    doxyawe
    GIT_REPOSITORY https://github.com/jothepro/doxygen-awesome-css.git
    GIT_TAG v2.2.1
)

# Download doxygen-awesome-css.
FetchContent_MakeAvailable(doxyawe)
FetchContent_GetProperties(doxyawe)

# Configure doxygen-awesome-css.
set(DOXYGEN_GENERATE_TREEVIEW YES)
set(DOXYGEN_DISABLE_INDEX NO)
set(DOXYGEN_FULL_SIDEBAR NO)
set(DOXYGEN_HTML_COLORSTYLE LIGHT)
set(DOXYGEN_HTML_HEADER header.html) # see generate-header.sh
set(DOXYGEN_HTML_EXTRA_FILES
  ${doxyawe_SOURCE_DIR}/doxygen-awesome-darkmode-toggle.js
  ${doxyawe_SOURCE_DIR}/doxygen-awesome-fragment-copy-button.js
  ${doxyawe_SOURCE_DIR}/doxygen-awesome-paragraph-link.js
)
set(DOXYGEN_HTML_EXTRA_STYLESHEET
  ${doxyawe_SOURCE_DIR}/doxygen-awesome.css
  ${doxyawe_SOURCE_DIR}/doxygen-awesome-sidebar-only.css
  ${doxyawe_SOURCE_DIR}/doxygen-awesome-sidebar-only-darkmode-toggle.css
)

# Disable code folding (not yet compatable with doxygen-awesome-css).
if(DOXYGEN_VERSION VERSION_GREATER_EQUAL 1.9.8)
  set(DOXYGEN_HTML_CODE_FOLDING NO)
endif()

# Additional Doxygen config.
set(DOXYGEN_PROJECT_NAME "Type Pack")
set(DOXYGEN_USE_MDFILE_AS_MAINPAGE ${CMAKE_SOURCE_DIR}/README.md)

# Strip source dir from paths.
set(DOXYGEN_FULL_PATH_NAMES YES)
set(DOXYGEN_STRIP_FROM_PATH ${CMAKE_SOURCE_DIR})
set(DOXYGEN_STRIP_FROM_INC_PATH ${CMAKE_SOURCE_DIR})

# Add custom css.
list(APPEND DOXYGEN_HTML_EXTRA_STYLESHEET custom.css)

# Add doc target.
doxygen_add_docs(typack_doc
  ${CMAKE_SOURCE_DIR}/README.md
  ${CMAKE_SOURCE_DIR}/doc/API.md
  ${CMAKE_SOURCE_DIR}/include/typack/typack.hpp
)
