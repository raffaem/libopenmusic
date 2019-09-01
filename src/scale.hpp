#ifndef SCALE_HPP_INCLUDED
#define SCALE_HPP_INCLUDED
#pragma once

#include <vector>
#include <string>
#include "note.hpp"
#include "chord.hpp"

// The scale end on the last note, and NOT on the root note, so the C major scale is
// C D E F G A B
// and NOT
// C D E F G A B C
// The root note at the end is somehow implicit
const std::string SCALE_MAJOR = "TTSTTT";
const std::string SCALE_NATURAL_MINOR = "TSTTSTT";
const std::string SCALE_HARMONIC_MINOR = "TSTTS3";

const std::string SCALE_CHROMATIC = "SSSSSSSSSSS";

const std::string SCALE_IONIAN = SCALE_MAJOR;
const std::string SCALE_DORIAN = "TSTTTS";
const std::string SCALE_PHRYGIAN = "STTTST";
const std::string SCALE_LYDIAN = "TTTSTT";
const std::string SCALE_MIXOLYDIAN = "TTSTTS";
const std::string SCALE_AEOLIAN = "TSTTST";
const std::string SCALE_LOCRIAN = "STTSTT";

class Scale
{
    std::vector<Note> notes;
    Note getNoteSecure(size_t index);
public:
    Scale(Note root, std::string seq);
    void print();
    std::vector<om::Chord> genChordsTriad();
    std::vector<om::Chord> genChordsSeventh();
};

#endif // SCALE_HPP_INCLUDED
