/**
 * Plucked string synthesis using Karplus-Strong algorithm.
 *
 */

#include "aquila/synth/KarplusStrongSynthesizer.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>


class NoteReader
{
public:
    NoteReader(Aquila::Synthesizer& synthesizer):
        m_synthesizer(synthesizer)
    {
    }

    void playString(const std::string& notes)
    {
        std::istringstream stream(notes);
        playStream(stream);
    }

    void playFile(const std::string& filename)
    {
        std::ifstream stream(filename);
        playStream(stream);
    }

    void playStream(std::istream& stream)
    {
        std::string line, note;
        unsigned int duration, lineNumber = 0;
        while(std::getline(stream, line))
        {
            lineNumber++;
            if (!line.empty())
            {
                std::istringstream lineStream(line);
                if (lineStream >> note >> duration)
                {
                    m_synthesizer.playNote(note, duration);
                }
                else
                {
                    std::cerr << "Parse error on line " << lineNumber
                              << ": '" << line << "'" << std::endl;
                }
            }
        }
    }

private:
    Aquila::Synthesizer& m_synthesizer;
};

const std::string Cmajor =
    "C4 500\n"
    "D4 500\n"
    "E4 500\n"
    "F4 500\n"
    "G4 500\n"
    "A4 500\n"
    "B4 500\n"
    "C5 500\n"
    "pause 500\n"
    "C5 500\n"
    "B4 500\n"
    "A4 500\n"
    "G4 500\n"
    "F4 500\n"
    "E4 500\n"
    "D4 500\n"
    "C4 500\n";

int main(int argc, char** argv)
{
    std::cout << "Plucked string synthesis using Karplus-Strong algorithm\n";
    const Aquila::FrequencyType SAMPLE_FREQUENCY = 44100;
    Aquila::KarplusStrongSynthesizer synth(SAMPLE_FREQUENCY);
    NoteReader reader(synth);
    if (argc < 2)
    {
        std::cout << "No filename provided, playing C major scale" << std::endl;
        reader.playString(Cmajor);
    }
    else
    {
        std::cout << "Playing notes from " << argv[1] << std::endl;
        reader.playFile(argv[1]);
    }

    return 0;
}
