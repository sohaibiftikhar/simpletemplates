cmake_minimum_required(VERSION 3.14)
project(simple_templates)

set(CMAKE_CXX_STANDARD 14)

set(INCLUDES includes/library.h includes/Renderable.hpp includes/Template.hpp includes/Binding.hpp includes/common.hpp includes/Token.hpp includes/Parser.hpp modules/TemplateEngine.cpp includes/TemplateEngine.hpp includes/TemplateConfig.hpp test_includes/Specification.hpp test_includes/TestSuite.hpp)
set(MODULES modules/library.cpp modules/Renderable.cpp modules/Template.cpp includes/Token.hpp modules/Parser.cpp modules/Token.cpp modules/Binding.cpp modules/common.cpp modules/TemplateConfig.cpp test_modules/TestSuite.cpp test_modules/Specification.cpp)

set(TEST_INCLUDES test_includes/ParserSpec.hpp test_includes/TemplateConfigSpec.hpp)
set(TEST_MODULES test_modules/ParserSpec.cpp test_modules/TemplateConfigSpec.cpp)
set(TEST tests/main.cpp)

add_library(simple_templates ${INCLUDES} ${MODULES})

add_executable(engine_test ${INCLUDES} ${MODULES} ${TEST} ${TEST_INCLUDES} ${TEST_MODULES})