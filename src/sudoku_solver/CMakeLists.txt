# Fetch dependencies.
find_package(SFML COMPONENTS Graphics Window System CONFIG REQUIRED)

# Build executable
file(GLOB_RECURSE sources *.cpp)
add_executable(sudoku_solver ${sources})
target_include_directories(sudoku_solver PUBLIC ${PROJECT_SOURCE_DIR}/include/sudoku_solver)
target_link_libraries(sudoku_solver PUBLIC SFML::Graphics SFML::Window SFML::System)
target_compile_features(sudoku_solver PUBLIC cxx_std_23)

file(COPY ${PROJECT_SOURCE_DIR}/data/assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
