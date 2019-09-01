#include "chord.hpp"
#include <iostream>
using namespace std;
using namespace om;

// CONSTANTS DEFINITIONS

// TRIADS
const int CHORD_MAJOR_TRIAD[] = {0,4,7};
const int CHORD_MINOR_TRIAD[] = {0,3,7};
const int CHORD_DIMINISHED_TRIAD[] = {0,3,6};
const int CHORD_AUGMENTED_TRIAD[] = {0,4,8};

//SEVENTHS
const int CHORD_MAJOR_SEVENTH[] = {0,4,7,11};
const int CHORD_MINOR_SEVENTH[] = {0,3,7,10};
const int CHORD_DOMINANT_SEVENTH[] = {0,4,7,10};

const int CHORD_DIMINISHED_SEVENTH[] = {0,3,6,9};
const int CHORD_HALF_DIMINISHED_SEVENTH[] = {0,3,6,10};
const int CHORD_MINOR_MAJOR_SEVENTH[] = {0,3,7,11};

const int CHORD_AUGMENTED_MAJOR_SEVENTH[] = {0,4,8,11};
const int CHORD_AUGMENTED_SEVENTH[] = {0,4,8,10};
const int CHORD_DIMINISHED_MAJOR_SEVENTH[] = {0,3,6,11};

// CHORD CLASS
Chord::Chord() {}

void Chord::addNote(Note n)
{
    notes.push_back(n);
}

void Chord::createTriad(Note a, Note b, Note c)
{
    notes.push_back(a);
    notes.push_back(b);
    notes.push_back(c);
    this->identify();
}

void Chord::createSeventh(Note a, Note b, Note c, Note d)
{
    notes.push_back(a);
    notes.push_back(b);
    notes.push_back(c);
    notes.push_back(d);
    this->identify();
}

void Chord::identify()
{
    //RECOGNIZE SEVENTHS
    if(this->notes.size()==4)
    {
        Note n1 = this->notes[0];
        Note n2 = this->notes[1];
        Note n3 = this->notes[2];
        Note n4 = this->notes[3];

        int intervals[4];
        intervals[0] = 0; //The first element is always the root note
        intervals[1] = n1.getHalftones(n2);
        intervals[2] = n1.getHalftones(n3);
        intervals[3] = n1.getHalftones(n4);

        if     (std::equal(intervals, intervals+4,CHORD_MAJOR_SEVENTH))    this->type=SEV_MAJOR;
        else if(std::equal(intervals, intervals+4,CHORD_MINOR_SEVENTH))      this->type=SEV_MINOR;
        else if(std::equal(intervals, intervals+4,CHORD_DOMINANT_SEVENTH)) this->type=SEV_DOMINANT;

        else if(std::equal(intervals, intervals+4,CHORD_DIMINISHED_SEVENTH))  this->type=SEV_DIMINISHED;
        else if(std::equal(intervals, intervals+4,CHORD_HALF_DIMINISHED_SEVENTH))      this->type=SEV_HALF_DIMINISHED;
        else if(std::equal(intervals, intervals+4,CHORD_MINOR_MAJOR_SEVENTH)) this->type=SEV_MINOR_MAJOR;

        else if(std::equal(intervals, intervals+4,CHORD_AUGMENTED_MAJOR_SEVENTH))  this->type=SEV_AUGMENTED_MAJOR;
        else if(std::equal(intervals, intervals+4,CHORD_AUGMENTED_SEVENTH))      this->type=SEV_AUGMENTED;
        else if(std::equal(intervals, intervals+4,CHORD_DIMINISHED_MAJOR_SEVENTH)) this->type=SEV_DIMINISHED_MAJOR;

        else                                                               this->type=CHORD_UNRECOGNIZED;
    }

    //RECOGNIZE TRIADS
    else if(this->notes.size()==3)
    {
        Note n1 = this->notes[0];
        Note n2 = this->notes[1];
        Note n3 = this->notes[2];

        int intervals[3];
        intervals[0] = 0; //The first element is always the root note
        intervals[1] = n1.getHalftones(n2);
        intervals[2] = n1.getHalftones(n3);

        if(std::equal(intervals, intervals+3,     CHORD_MAJOR_TRIAD))      this->type=TRI_MAJOR;
        else if(std::equal(intervals, intervals+3,CHORD_MINOR_TRIAD))      this->type=TRI_MINOR;
        else if(std::equal(intervals, intervals+3,CHORD_DIMINISHED_TRIAD)) this->type=TRI_DIMINISHED;
        else if(std::equal(intervals, intervals+3,CHORD_AUGMENTED_TRIAD))  this->type=TRI_AUGMENTED;
        else                                                               this->type=CHORD_UNRECOGNIZED;
    }
}

void Chord::printNotesList()
{
    for(size_t i=0; i<notes.size(); i++)
    {
        notes[i].print();
        if(i != notes.size()-1) cout<<" - ";
    }
}

void Chord::print()
{
    this->notes[0].print();
    switch (this->type)
    {

        //TRIADS
    case TRI_MAJOR:
        break;
    case TRI_MINOR:
        cout <<"m";
        break;
    case TRI_DIMINISHED:
        cout<<"dim";
        break;
    case TRI_AUGMENTED:
        cout<<"aug";
        break;

        //SEVENTHS
    case SEV_AUGMENTED:
        cout <<"aug7";
        break;
    case SEV_AUGMENTED_MAJOR:
        cout <<"maj+7";
        break;
    case SEV_DIMINISHED:
        cout <<"dim7";
        break;
    case SEV_DIMINISHED_MAJOR:
        cout <<"dim-maj-7";
        break;
    case SEV_DOMINANT:
        cout <<"7";
        break;
    case SEV_HALF_DIMINISHED:
        cout <<"m7b5";
        break;
    case SEV_MAJOR:
        cout <<"maj7";
        break;
    case SEV_MINOR:
        cout <<"min7";
        break;
    case SEV_MINOR_MAJOR:
        cout <<"mM7";
        break;

    case CHORD_UNRECOGNIZED:
        cout<<"UNRECOGNIZED";
        break;
    }

    cout << " (" ;
     printNotesList();
     cout << ")";
}
