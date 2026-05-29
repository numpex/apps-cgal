add_executable(${APPS_CGAL_EXECUTABLE_PREFIX}_autorefine autorefine.cpp)
target_link_libraries(${APPS_CGAL_EXECUTABLE_PREFIX}_autorefine 
    PRIVATE 
    Ktirio-Geom::ktirio_geom
)
