cmake_minimum_required(VERSION 2.6)

project(UnitTest++ CXX)

include_directories(src)

################################################################################
#
# UnitTest++ sources
#
################################################################################

set(UNITTESTPP_SOURCES
    src/AssertException.cpp
    src/Checks.cpp
    src/CompositeTestReporter.cpp
    src/CurrentTest.cpp
    src/DeferredTestReporter.cpp
    src/DeferredTestResult.cpp
    src/MemoryOutStream.cpp
    src/ReportAssert.cpp
    src/Test.cpp
    src/TestDetails.cpp
    src/TestList.cpp
    src/TestReporter.cpp
    src/TestReporterStdout.cpp
    src/TestResults.cpp
    src/TestRunner.cpp
    src/TimeConstraint.cpp
    src/XmlTestReporter.cpp
)

if(UNIX)
    list(APPEND UNITTESTPP_SOURCES
        src/Posix/SignalTranslator.cpp
        src/Posix/TimeHelpers.cpp
    )
elseif(WIN32)
    list(APPEND UNITTESTPP_SOURCES
        src/Win32/TimeHelpers.cpp
    )
endif()

add_library(UnitTest++ STATIC EXCLUDE_FROM_ALL ${UNITTESTPP_SOURCES})


################################################################################
#
# UnitTest++ self-test sources
#
################################################################################

set(UNITTESTPP_TEST_SOURCES
    src/tests/Main.cpp
    src/tests/TestAssertHandler.cpp
    src/tests/TestCheckMacros.cpp
    src/tests/TestChecks.cpp
    src/tests/TestCompositeTestReporter.cpp
    src/tests/TestCurrentTest.cpp
    src/tests/TestDeferredTestReporter.cpp
    src/tests/TestExceptions.cpp
    src/tests/TestMemoryOutStream.cpp
    src/tests/TestTest.cpp
    src/tests/TestTestList.cpp
    src/tests/TestTestMacros.cpp
    src/tests/TestTestResults.cpp
    src/tests/TestTestRunner.cpp
    src/tests/TestTestSuite.cpp
    src/tests/TestTimeConstraint.cpp
    src/tests/TestTimeConstraintMacro.cpp
    src/tests/TestUnitTestPP.cpp
    src/tests/TestXmlTestReporter.cpp
)

add_executable(TestUnitTest++ EXCLUDE_FROM_ALL ${UNITTESTPP_TEST_SOURCES})
target_link_libraries(TestUnitTest++ UnitTest++)
