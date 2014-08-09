# Install script for directory: /home/zbyszek/Development/unittest-cpp

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "/usr/local")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

# Install shared libraries without execute permission?
IF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  SET(CMAKE_INSTALL_SO_NO_EXE "1")
ENDIF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/zbyszek/Development/unittest-cpp/build-gcc/libUnitTest++.a")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/UnitTest++" TYPE FILE FILES
    "/home/zbyszek/Development/unittest-cpp/UnitTest++/MemoryOutStream.h"
    "/home/zbyszek/Development/unittest-cpp/UnitTest++/CheckMacros.h"
    "/home/zbyszek/Development/unittest-cpp/UnitTest++/TestResults.h"
    "/home/zbyszek/Development/unittest-cpp/UnitTest++/TestDetails.h"
    "/home/zbyszek/Development/unittest-cpp/UnitTest++/UnitTest++.h"
    "/home/zbyszek/Development/unittest-cpp/UnitTest++/UnitTestPP.h"
    "/home/zbyszek/Development/unittest-cpp/UnitTest++/CompositeTestReporter.h"
    "/home/zbyszek/Development/unittest-cpp/UnitTest++/ExecuteTest.h"
    "/home/zbyszek/Development/unittest-cpp/UnitTest++/TestList.h"
    "/home/zbyszek/Development/unittest-cpp/UnitTest++/ReportAssert.h"
    "/home/zbyszek/Development/unittest-cpp/UnitTest++/DeferredTestResult.h"
    "/home/zbyszek/Development/unittest-cpp/UnitTest++/Test.h"
    "/home/zbyszek/Development/unittest-cpp/UnitTest++/TimeHelpers.h"
    "/home/zbyszek/Development/unittest-cpp/UnitTest++/TestMacros.h"
    "/home/zbyszek/Development/unittest-cpp/UnitTest++/HelperMacros.h"
    "/home/zbyszek/Development/unittest-cpp/UnitTest++/DeferredTestReporter.h"
    "/home/zbyszek/Development/unittest-cpp/UnitTest++/TestRunner.h"
    "/home/zbyszek/Development/unittest-cpp/UnitTest++/CurrentTest.h"
    "/home/zbyszek/Development/unittest-cpp/UnitTest++/Checks.h"
    "/home/zbyszek/Development/unittest-cpp/UnitTest++/AssertException.h"
    "/home/zbyszek/Development/unittest-cpp/UnitTest++/XmlTestReporter.h"
    "/home/zbyszek/Development/unittest-cpp/UnitTest++/TimeConstraint.h"
    "/home/zbyszek/Development/unittest-cpp/UnitTest++/TestSuite.h"
    "/home/zbyszek/Development/unittest-cpp/UnitTest++/ExceptionMacros.h"
    "/home/zbyszek/Development/unittest-cpp/UnitTest++/ReportAssertImpl.h"
    "/home/zbyszek/Development/unittest-cpp/UnitTest++/TestReporter.h"
    "/home/zbyszek/Development/unittest-cpp/UnitTest++/TestReporterStdout.h"
    "/home/zbyszek/Development/unittest-cpp/UnitTest++/Config.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/UnitTest++/Posix" TYPE FILE FILES
    "/home/zbyszek/Development/unittest-cpp/UnitTest++/Posix/TimeHelpers.h"
    "/home/zbyszek/Development/unittest-cpp/UnitTest++/Posix/SignalTranslator.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(CMAKE_INSTALL_COMPONENT)
  SET(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
ELSE(CMAKE_INSTALL_COMPONENT)
  SET(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
ENDIF(CMAKE_INSTALL_COMPONENT)

FILE(WRITE "/home/zbyszek/Development/unittest-cpp/build-gcc/${CMAKE_INSTALL_MANIFEST}" "")
FOREACH(file ${CMAKE_INSTALL_MANIFEST_FILES})
  FILE(APPEND "/home/zbyszek/Development/unittest-cpp/build-gcc/${CMAKE_INSTALL_MANIFEST}" "${file}\n")
ENDFOREACH(file)
