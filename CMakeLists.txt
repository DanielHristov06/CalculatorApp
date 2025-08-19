cmake_minimum_required(VERSION 3.16)
project(CalculatorApp)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories("include")

file(GLOB_RECURSE SRC_FILES "src/*.cpp")
file(GLOB_RECURSE HEADER_FILES "include/*.h")

add_executable(Calculator ${SRC_FILES} ${HEADER_FILES})

# --- wxWidgets build configuration (no find_package needed) ---
# Build static libraries with the MD runtime, no samples/tests, no PCH.
set(wxBUILD_SHARED              OFF CACHE BOOL "" FORCE)  # static libs (.lib)
set(wxBUILD_MONOLITHIC          OFF CACHE BOOL "" FORCE)  # OFF = link wx::core + wx::base
set(wxBUILD_PRECOMP             OFF CACHE BOOL "" FORCE)
set(wxBUILD_SAMPLES             OFF CACHE BOOL "" FORCE)
set(wxBUILD_TESTS               OFF CACHE BOOL "" FORCE)
set(wxBUILD_DEMOS               OFF CACHE BOOL "" FORCE)
set(wxBUILD_USE_STATIC_RUNTIME  OFF CACHE BOOL "" FORCE)  # use /MD, not /MT

# Add the wxWidgets source tree that sits in your repo
add_subdirectory(wxWidgets-3.3.1)

# Link against the wxWidgets targets exported by that subdir
target_link_libraries(Calculator PRIVATE wx::core wx::base)

# (Optional) a couple of Windows niceties
if(MSVC)
  target_compile_definitions(Calculator PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()

if(WIN32)
	set_target_properties(Calculator PROPERTIES WIN32_EXECUTABLE TRUE)
endif()