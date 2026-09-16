cmake_minimum_required(VERSION 3.21.0)

project( apps-cgal VERSION 0.1.0 )

set(EXTRA_VERSION "")
set(PROJECT_SHORTNAME "apps-cgal")
set(APPS_CGAL_CMAKE_PREFIX "APPS_CGAL")
set(APPS_CGAL_EXECUTABLE_PREFIX "apps_cgal")
set(APPS_CGAL_LIBRARY "apps_cgal")
set(APPS_CGAL_LIBRARY_PREFIX "apps_cgal")
include(GNUInstallDirs)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare( ktirio-geom
    GIT_REPOSITORY https://github.com/feelpp/ktirio-geom.git
    GIT_TAG b452b3a5ee0d0c1a42da174c0becb5730e3d7965
)
FetchContent_MakeAvailable(ktirio-geom)

add_subdirectory( src )
