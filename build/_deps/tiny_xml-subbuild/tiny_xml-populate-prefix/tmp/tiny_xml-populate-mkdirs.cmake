# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/arturl/dev/CG/CG_TP/build/_deps/tiny_xml-src"
  "/home/arturl/dev/CG/CG_TP/build/_deps/tiny_xml-build"
  "/home/arturl/dev/CG/CG_TP/build/_deps/tiny_xml-subbuild/tiny_xml-populate-prefix"
  "/home/arturl/dev/CG/CG_TP/build/_deps/tiny_xml-subbuild/tiny_xml-populate-prefix/tmp"
  "/home/arturl/dev/CG/CG_TP/build/_deps/tiny_xml-subbuild/tiny_xml-populate-prefix/src/tiny_xml-populate-stamp"
  "/home/arturl/dev/CG/CG_TP/build/_deps/tiny_xml-subbuild/tiny_xml-populate-prefix/src"
  "/home/arturl/dev/CG/CG_TP/build/_deps/tiny_xml-subbuild/tiny_xml-populate-prefix/src/tiny_xml-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/arturl/dev/CG/CG_TP/build/_deps/tiny_xml-subbuild/tiny_xml-populate-prefix/src/tiny_xml-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/arturl/dev/CG/CG_TP/build/_deps/tiny_xml-subbuild/tiny_xml-populate-prefix/src/tiny_xml-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
