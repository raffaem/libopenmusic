#ifndef CHORD_HPP_INCLUDED
#define CHORD_HPP_INCLUDED

#include <vector>
#include "note.hpp"

namespace om
{

enum E_CHORD_TYPE
{
    //TRIADS
    TRI_MAJOR,
    TRI_MINOR,
    TRI_DIMINISHED,
    TRI_AUGMENTED,

    //SEVENTHS
    SEV_MAJOR,
    SEV_MINOR,
    SEV_DOMINANT,

    SEV_DIMINISHED,
    SEV_HALF_DIMINISHED,
    SEV_MINOR_MAJOR,

    SEV_AUGMENTED_MAJOR,
    SEV_AUGMENTED,
    SEV_DIMINISHED_MAJOR,

    CHORD_UNRECOGNIZED
};

class Chord
{
    std::vector<Note> notes;
    E_CHORD_TYPE type;
public:
    Chord();
    void addNote(Note n);
    void createTriad(Note a, Note b, Note c);
    void createSeventh(Note a, Note b, Note c, Note d);
    void identify();
    void printNotesList();
    void print();
};

}

#endif
