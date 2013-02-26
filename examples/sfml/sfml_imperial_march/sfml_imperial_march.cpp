/**
 * Playing the Imperial March from Star Wars.
 *
 * Notes and timings found at:
 *    http://processors.wiki.ti.com/index.php/Playing_The_Imperial_March
 */

#include "aquila/synth/SineSynthesizer.h"
#include <iostream>

int main(int argc, char** argv)
{
    std::cout << " The Imperial March (Darth Vader's Theme) \n\n"
                 " composed by John Williams \n"
                 " played by SFML, Aquila and... your speakers! \n\n"
                 " Aquila DSP library: \n"
                 " \t http://aquila-dsp.org \n\n"
                 " SFML multimedia library: \n"
                 " \t http://www.sfml-dev.org \n\n"
                 " Notes and timings found at: \n"
                 " \t http://processors.wiki.ti.com/index.php/Playing_The_Imperial_March \n\n"
                 " (c) Zbigniew Siciarz 2010 \n" << std::endl;

    const Aquila::FrequencyType SAMPLE_FREQUENCY = 44100;
    Aquila::SineSynthesizer synth(SAMPLE_FREQUENCY);

    synth.playNote("a", 500);
    synth.playNote("a", 500);
    synth.playNote("a", 500);
    synth.playNote("f", 350);
    synth.playNote("cH", 150);
    synth.playNote("a", 500);
    synth.playNote("f", 350);
    synth.playNote("cH", 150);
    synth.playNote("a", 650);

    synth.playNote("pause", 150);

    synth.playNote("eH", 500);
    synth.playNote("eH", 500);
    synth.playNote("eH", 500);
    synth.playNote("fH", 350);
    synth.playNote("cH", 150);
    synth.playNote("gS", 500);
    synth.playNote("f", 350);
    synth.playNote("cH", 150);
    synth.playNote("a", 650);

    synth.playNote("pause", 150);

    synth.playNote("aH", 500);
    synth.playNote("a", 300);
    synth.playNote("a", 150);
    synth.playNote("aH", 400);
    synth.playNote("gSH", 200);
    synth.playNote("gH", 200);
    synth.playNote("fSH", 125);
    synth.playNote("fH", 125);
    synth.playNote("fSH", 250);

    synth.playNote("pause", 250);

    synth.playNote("aS", 250);
    synth.playNote("dSH", 400);
    synth.playNote("dH", 200);
    synth.playNote("cSH", 200);
    synth.playNote("cH", 125);
    synth.playNote("b", 125);
    synth.playNote("cH", 250);

    synth.playNote("pause", 250);

    synth.playNote("f", 125);
    synth.playNote("gS", 500);
    synth.playNote("f", 375);
    synth.playNote("a", 125);
    synth.playNote("cH", 500);
    synth.playNote("a", 375);
    synth.playNote("cH", 125);
    synth.playNote("eH", 650);

    synth.playNote("aH", 500);
    synth.playNote("a", 300);
    synth.playNote("a", 150);
    synth.playNote("aH", 400);
    synth.playNote("gSH", 200);
    synth.playNote("gH", 200);
    synth.playNote("fSH", 125);
    synth.playNote("fH", 125);
    synth.playNote("fSH", 250);

    synth.playNote("pause", 250);

    synth.playNote("aS", 250);
    synth.playNote("dSH", 400);
    synth.playNote("dH", 200);
    synth.playNote("cSH", 200);
    synth.playNote("cH", 125);
    synth.playNote("b", 125);
    synth.playNote("cH", 250);

    synth.playNote("pause", 250);

    synth.playNote("f", 250);
    synth.playNote("gS", 500);
    synth.playNote("f", 375);
    synth.playNote("cH", 125);
    synth.playNote("a", 500);
    synth.playNote("f", 375);
    synth.playNote("cH", 125);
    synth.playNote("a", 650);

    return 0;
}
