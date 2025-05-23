# Copyright (C) 1995-2019, Rene Brun and Fons Rademakers.
# All rights reserved.
#
# For the licensing terms see $ROOTSYS/LICENSE.
# For the list of contributors see $ROOTSYS/README/CREDITS.

############################################################################
# CMakeLists.txt file for building ROOT core/dictgen package
############################################################################

# Provides capabilities to parse Linkdef / selection files and generate
# dictionaries.
#
# These files are linked into rootcling_stage1 and libCling. rootcling accesses
# them through rootcling_impl.

ROOT_OBJECT_LIBRARY(Dictgen
  BaseSelectionRule.cxx
  ClassSelectionRule.cxx
  DictSelectionReader.cxx
  LinkdefReader.cxx
  rootcling_impl.cxx
  Scanner.cxx
  SelectionRules.cxx
  TModuleGenerator.cxx
  VariableSelectionRule.cxx
  XMLReader.cxx
)

# This directory contains files that include llvm, which can give warnings.
if(NOT MSVC)
  target_compile_options(Dictgen PRIVATE -Wno-error)
endif()


add_dependencies(Dictgen CLING)

if(NOT builtin_cling)
  # FIXME: Resolve this once the ClangTargets.cmake allows us to specify the
  # targets we need.
  add_dependencies(Dictgen clang-tablegen-targets)
endif()

target_include_directories(Dictgen PRIVATE
  ${CMAKE_SOURCE_DIR}/core/dictgen/src
  ${CMAKE_SOURCE_DIR}/core/dictgen/res
  ${CMAKE_SOURCE_DIR}/core/foundation/res
  ${CMAKE_SOURCE_DIR}/core/clingutils/res
  ${CMAKE_SOURCE_DIR}/core/base/inc
  ${CMAKE_SOURCE_DIR}/core/clib/inc
  ${CMAKE_SOURCE_DIR}/core/meta/inc
  ${CMAKE_SOURCE_DIR}/core/foundation/inc
  ${CMAKE_BINARY_DIR}/ginclude
  ${CLING_INCLUDE_DIRS}
)

# Register the llvm include directories after clangs. This instructs the compiler to resolve
# headers from our builtin clang. That's an issue when we are building with bultin_llvm=Off
# and we have installed clang headers, too.
target_include_directories(Dictgen SYSTEM PRIVATE ${CLANG_INCLUDE_DIRS} ${LLVM_INCLUDE_DIRS})
set_target_properties(Dictgen PROPERTIES
  COMPILE_FLAGS "${CMAKE_CXX_FLAGS} ${CLING_CXXFLAGS}"
  VISIBILITY_INLINES_HIDDEN "ON"
)

if(CXX_HAS_fno_rtti)
    set_source_files_properties(src/rootcling_impl.cxx   PROPERTIES COMPILE_FLAGS "-fno-rtti")
    set_source_files_properties(src/LinkdefReader.cxx    PROPERTIES COMPILE_FLAGS "-fno-rtti")
    set_source_files_properties(src/TModuleGenerator.cxx PROPERTIES COMPILE_FLAGS "-fno-rtti")
endif()

#---CreateRootClingCommandLineOptions------------------------------------------------------------------
generateHeader(Dictgen
  ${CMAKE_SOURCE_DIR}/core/dictgen/src/rootcling-argparse.py
  ${CMAKE_BINARY_DIR}/ginclude/rootclingCommandLineOptionsHelp.h
)

ROOT_ADD_TEST_SUBDIRECTORY(test)
