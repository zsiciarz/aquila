/**
 * Plucked string synthesis using Karplus-Strong algorithm.
 *
 */

#include "aquila/synth/KarplusStrongSynthesizer.h"
#include <iostream>


int main(int argc, char** argv)
{
    std::cout << "Plucked string synthesis using Karplus-Strong algorithm\n";
    const Aquila::FrequencyType SAMPLE_FREQUENCY = 44100;

    Aquila::KarplusStrongSynthesizer synth(SAMPLE_FREQUENCY);
    // play the C major scale up and down
    synth.playNote("c");
    synth.playNote("d");
    synth.playNote("e");
    synth.playNote("f");
    synth.playNote("g");
    synth.playNote("a");
    synth.playNote("b");
    synth.playNote("cH");
    synth.playNote("pause");
    synth.playNote("cH");
    synth.playNote("b");
    synth.playNote("a");
    synth.playNote("g");
    synth.playNote("f");
    synth.playNote("e");
    synth.playNote("d");
    synth.playNote("c");

    return 0;
}
