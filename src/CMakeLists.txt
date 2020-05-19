
file(GLOB SOURCES CONFIGURE_DEPENDS *.h *.cpp)

add_library(src ${SOURCES} Colors.cpp)
target_include_directories(src PUBLIC ./ ../imgui)
target_link_libraries(src imgui pugixml sfml-graphics)
