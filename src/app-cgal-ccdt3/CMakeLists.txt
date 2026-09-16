add_executable(${APPS_CGAL_EXECUTABLE_PREFIX}_ccdt3 ccdt3.cpp)
target_link_libraries(${APPS_CGAL_EXECUTABLE_PREFIX}_ccdt3
    PRIVATE
    Ktirio-Geom::ktirio_geom
)
