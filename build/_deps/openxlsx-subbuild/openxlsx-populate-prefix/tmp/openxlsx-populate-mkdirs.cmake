# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file LICENSE.rst or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION ${CMAKE_VERSION}) # this file comes with cmake

# If CMAKE_DISABLE_SOURCE_CHANGES is set to true and the source directory is an
# existing directory in our source tree, calling file(MAKE_DIRECTORY) on it
# would cause a fatal error, even though it would be a no-op.
if(NOT EXISTS "/home/lain/Dev/projects/penentuan-gelombang-pecah/build/_deps/openxlsx-src")
  file(MAKE_DIRECTORY "/home/lain/Dev/projects/penentuan-gelombang-pecah/build/_deps/openxlsx-src")
endif()
file(MAKE_DIRECTORY
  "/home/lain/Dev/projects/penentuan-gelombang-pecah/build/_deps/openxlsx-build"
  "/home/lain/Dev/projects/penentuan-gelombang-pecah/build/_deps/openxlsx-subbuild/openxlsx-populate-prefix"
  "/home/lain/Dev/projects/penentuan-gelombang-pecah/build/_deps/openxlsx-subbuild/openxlsx-populate-prefix/tmp"
  "/home/lain/Dev/projects/penentuan-gelombang-pecah/build/_deps/openxlsx-subbuild/openxlsx-populate-prefix/src/openxlsx-populate-stamp"
  "/home/lain/Dev/projects/penentuan-gelombang-pecah/build/_deps/openxlsx-subbuild/openxlsx-populate-prefix/src"
  "/home/lain/Dev/projects/penentuan-gelombang-pecah/build/_deps/openxlsx-subbuild/openxlsx-populate-prefix/src/openxlsx-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/lain/Dev/projects/penentuan-gelombang-pecah/build/_deps/openxlsx-subbuild/openxlsx-populate-prefix/src/openxlsx-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/lain/Dev/projects/penentuan-gelombang-pecah/build/_deps/openxlsx-subbuild/openxlsx-populate-prefix/src/openxlsx-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
