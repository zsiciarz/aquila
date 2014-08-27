#include "aquila/Exceptions.h"
#include "UnitTest++/UnitTest++.h"


SUITE(Exceptions)
{
    TEST(Exception)
    {
        try
        {
            throw Aquila::Exception("message");
        }
        catch (const Aquila::Exception& exc)
        {
            CHECK_EQUAL("message", exc.what());
        }
    }

    TEST(FormatException)
    {
        try
        {
            throw Aquila::FormatException("message");
        }
        catch (const Aquila::FormatException& exc)
        {
            CHECK_EQUAL("message", exc.what());
        }
    }

    TEST(ConfigurationException)
    {
        try
        {
            throw Aquila::ConfigurationException("message");
        }
        catch (const Aquila::ConfigurationException& exc)
        {
            CHECK_EQUAL("message", exc.what());
        }
    }
}
