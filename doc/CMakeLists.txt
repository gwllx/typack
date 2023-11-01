include(FetchContent)
find_package(Doxygen)

# Declare doxygen-awesome-css dependency.
FetchContent_Declare(
    doc_theme
    GIT_REPOSITORY https://github.com/jothepro/doxygen-awesome-css.git
    GIT_TAG df83fbf22cfff76b875c13d324baf584c74e96d0 # v2.2.1
)

# Download doxygen-awesome-css.
FetchContent_MakeAvailable(doc_theme)
FetchContent_GetProperties(doc_theme)

# Configure doxygen-awesome-css.
set(DOXYGEN_GENERATE_TREEVIEW YES)
set(DOXYGEN_DISABLE_INDEX NO)
set(DOXYGEN_FULL_SIDEBAR NO)
set(DOXYGEN_HTML_COLORSTYLE LIGHT)
set(DOXYGEN_HTML_HEADER header.html) # see generate-header.sh
set(DOXYGEN_HTML_EXTRA_FILES
  ${doc_theme_SOURCE_DIR}/doxygen-awesome-darkmode-toggle.js
  ${doc_theme_SOURCE_DIR}/doxygen-awesome-fragment-copy-button.js
  ${doc_theme_SOURCE_DIR}/doxygen-awesome-paragraph-link.js
)
set(DOXYGEN_HTML_EXTRA_STYLESHEET
  ${doc_theme_SOURCE_DIR}/doxygen-awesome.css
  ${doc_theme_SOURCE_DIR}/doxygen-awesome-sidebar-only.css
  ${doc_theme_SOURCE_DIR}/doxygen-awesome-sidebar-only-darkmode-toggle.css
)

# Add docs target.
doxygen_add_docs(typack_doc ${CMAKE_SOURCE_DIR}/include/typack/typack.hpp)
