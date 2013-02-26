/**
 * @file Synthesizer.cpp
 *
 * Base class for SFML-based audio synthesizers.
 *
 * This file is part of the Aquila DSP library.
 * Aquila is free software, licensed under the MIT/X11 License. A copy of
 * the license is provided with the library in the LICENSE file.
 *
 * @package Aquila
 * @version 3.0.0-dev
 * @author Zbigniew Siciarz
 * @date 2007-2013
 * @license http://www.opensource.org/licenses/mit-license.php MIT
 * @since 3.0.0
 */

#include "Synthesizer.h"

namespace Aquila
{
    /**
     * Creates the mapping between note names and frequencies.
     *
     * @return initialized note map
     */
    NoteMapType initNoteMap()
    {
        NoteMapType notes;
        notes["c"] = 261;
        notes["d"] = 294;
        notes["e"] = 329;
        notes["f"] = 349;
        notes["g"] = 391;
        notes["gS"] = 415;
        notes["a"] = 440;
        notes["aS"] = 455;
        notes["b"] = 466;
        notes["cH"] = 523;
        notes["cSH"] = 554;
        notes["dH"] = 587;
        notes["dSH"] = 622;
        notes["eH"] = 659;
        notes["fH"] = 698;
        notes["fSH"] = 740;
        notes["gH"] = 784;
        notes["gSH"] = 830;
        notes["aH"] = 880;
        return notes;
    }

    NoteMapType Synthesizer::m_notes = initNoteMap();

    /**
     * Plays a single note.
     *
     * This method only does the lookup from note name to frequency and
     * delegates the actual playing to pure virtual method playFrequency.
     *
     * Unrecognized note names are silent for the given duration.
     *
     * @param note note name (@see m_notes)
     * @param duration duration in milliseconds
     */
    void Synthesizer::playNote(std::string note, unsigned int duration)
    {
        if (m_notes.count(note) == 0)
        {
            sf::Sleep(duration / 1000.0f);
        }
        else
        {
            FrequencyType frequency = m_notes[note];
            playFrequency(frequency, duration);
        }
    }
}
