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

    synth.playNote("A4", 500);
    synth.playNote("A4", 500);
    synth.playNote("A4", 500);
    synth.playNote("F4", 350);
    synth.playNote("C5", 150);
    synth.playNote("A4", 500);
    synth.playNote("F4", 350);
    synth.playNote("C5", 150);
    synth.playNote("A4", 650);

    synth.playNote("pause", 150);

    synth.playNote("E5", 500);
    synth.playNote("E5", 500);
    synth.playNote("E5", 500);
    synth.playNote("F5", 350);
    synth.playNote("C5", 150);
    synth.playNote("G4S", 500);
    synth.playNote("F4", 350);
    synth.playNote("C5", 150);
    synth.playNote("A4", 650);

    synth.playNote("pause", 150);

    synth.playNote("A5", 500);
    synth.playNote("A4", 300);
    synth.playNote("A4", 150);
    synth.playNote("A5", 400);
    synth.playNote("G5S", 200);
    synth.playNote("G5", 200);
    synth.playNote("F5S", 125);
    synth.playNote("F5", 125);
    synth.playNote("F5S", 250);

    synth.playNote("pause", 250);

    synth.playNote("A4S", 250);
    synth.playNote("D5S", 400);
    synth.playNote("D5", 200);
    synth.playNote("C5S", 200);
    synth.playNote("C5", 125);
    synth.playNote("B4", 125);
    synth.playNote("C5", 250);

    synth.playNote("pause", 250);

    synth.playNote("F4", 125);
    synth.playNote("G4S", 500);
    synth.playNote("F4", 375);
    synth.playNote("A4", 125);
    synth.playNote("C5", 500);
    synth.playNote("A4", 375);
    synth.playNote("C5", 125);
    synth.playNote("E5", 650);

    synth.playNote("A5", 500);
    synth.playNote("A4", 300);
    synth.playNote("A4", 150);
    synth.playNote("A5", 400);
    synth.playNote("G5S", 200);
    synth.playNote("G5", 200);
    synth.playNote("F5S", 125);
    synth.playNote("F5", 125);
    synth.playNote("F5S", 250);

    synth.playNote("pause", 250);

    synth.playNote("A4S", 250);
    synth.playNote("D5S", 400);
    synth.playNote("D5", 200);
    synth.playNote("C5S", 200);
    synth.playNote("C5", 125);
    synth.playNote("B4", 125);
    synth.playNote("C5", 250);

    synth.playNote("pause", 250);

    synth.playNote("F4", 250);
    synth.playNote("G4S", 500);
    synth.playNote("F4", 375);
    synth.playNote("C5", 125);
    synth.playNote("A4", 500);
    synth.playNote("F4", 375);
    synth.playNote("C5", 125);
    synth.playNote("A4", 650);

    return 0;
}
