#include <iostream>
#include "src/TestDetails.h"
#include "src/TestReporterStdout.h"
#include "src/TestRunner.h"
#include "src/Test.h"


class AquilaTestReporter : public UnitTest::TestReporterStdout
{
    void ReportTestStart(UnitTest::TestDetails const& test)
    {
        std::cout << test.testName << std::endl;
    }
};


int main()
{
    AquilaTestReporter reporter;
    UnitTest::TestRunner runner(reporter);
    return runner.RunTestsIf(UnitTest::Test::GetTestList(), NULL, UnitTest::True(), 0);
}
