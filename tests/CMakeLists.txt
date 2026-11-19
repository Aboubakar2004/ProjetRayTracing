include(FetchContent)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.7.1
  GIT_SHALLOW TRUE)
FetchContent_MakeAvailable(Catch2)

add_executable(unit_tests greeting/test_greeting.cpp math/test_vector.cpp
  image/test_image.cpp)
target_link_libraries(unit_tests PRIVATE raytracer_core Catch2::Catch2WithMain)

include(Catch)
catch_discover_tests(unit_tests)
