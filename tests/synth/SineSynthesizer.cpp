#include "aquila/synth/SineSynthesizer.h"
#include "UnitTest++/UnitTest++.h"


SUITE(SineSynthesizer)
{
    TEST(PlayNote)
    {
        Aquila::SineSynthesizer synthesizer(44100);
        synthesizer.playNote("A4", 100);
    }

    TEST(PlayUnknownNote)
    {
        Aquila::SineSynthesizer synthesizer(44100);
        synthesizer.playNote("XX", 100);
    }
}
