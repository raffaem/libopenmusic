#include "scale.hpp"
#include <iostream>
using namespace std;
using namespace om;

Note Scale::getNoteSecure(size_t index)
{
    if(index >= notes.size()) index = index % notes.size();
    return notes[index];
}

Scale::Scale(Note root, std::string seq)
{
    notes.push_back(root);
    unsigned toadd = 0;

    for(size_t i=0; i<seq.size(); i++)
    {
        if(seq[i] == 'T')
            toadd += 2;
        else if(seq[i] == 'S')
            toadd += 1;
        else if(seq[i] == '3')
            toadd += 3;

        Note newnote = root+toadd;
        //cout << "New note" << newnote.toStr() << endl;
        notes.push_back(newnote);
    }
}

void Scale::print()
{
    for(size_t i=0; i<notes.size(); i++)
    {
        notes[i].print();
        cout<<" - ";
    }
    // The last note is the root one an octave higher. The last note is never memorized in the notes vector
    notes[0].print();
}

std::vector<Chord> Scale::genChordsTriad()
{
    vector<Chord> chs;

    // For every note, take that note, the 2nd note after and the 4th note after to make a triad
    for(size_t i=0; i<notes.size(); i++)
    {
        Chord ch;
        Note n1 = getNoteSecure(i);
        Note n2 = getNoteSecure(i+2);
        Note n3 = getNoteSecure(i+4);
        ch.createTriad(n1,n2,n3);
        chs.push_back(ch);
    }

    return chs;
}

std::vector<Chord> Scale::genChordsSeventh()
{
    vector<Chord> chs;

    // For every note, take that note, the 2nd note after and the 4th note after to make a triad
    for(size_t i=0; i<notes.size(); i++)
    {
        Chord ch;
        Note n1 = getNoteSecure(i);
        Note n2 = getNoteSecure(i+2);
        Note n3 = getNoteSecure(i+4);
        Note n4 = getNoteSecure(i+6);
        ch.createSeventh(n1,n2,n3,n4);
        chs.push_back(ch);
    }

    return chs;
}
