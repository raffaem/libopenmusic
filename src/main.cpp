#include <string>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <conio.h>     /* include for kbhit() and getch() functions */

#include "chord.hpp"
#include "scale.hpp"
#include "note.hpp"
#include "interval.hpp"

#include <windows.h>   /* required before including mmsystem.h */
#include <mmsystem.h>  /* multimedia functions (such as MIDI) for Windows */

using namespace std;
using namespace om;

void scaleEx();
void intervalEx();
int playEx();

Note getNote()
{
	Note eroot;
    bool bre;

    do
    {
        cout << "Insert a note (like C, CS, D, exc..): ";
        string notestr;
        cin>>notestr;
        eroot = Note::Note(notestr,bre);
        if(!bre)
            cout << "Unrecognized note" << endl;
    }
    while(!bre);

	return eroot;
}

int main()
{
	cout << "1 - Scale example " << endl;
	cout << "2 - Interval example " << endl;
	cout << "3 - MIDI example " << endl;
	cout << "Digit a number: " << endl;
	int n;
	cin >> n;

	switch(n)
	{
	case 1: scaleEx(); break;
	case 2: intervalEx(); break;
	case 3: playEx(); break;
	default: cout << "not valid"; break;
	}

	system("pause");
	return 0;
}

HMIDIOUT device;    // MIDI device interface for sending MIDI output
// variable which is both an integer and an array of characters:
union { unsigned long word; unsigned char data[4]; } message;
int flag;           // monitor the status of returning functions

void notePlay(Note note, int milliseconds)
{
	// message.data[0] = command byte of the MIDI message, for example: 0x90. Note-off is 0x80
   // message.data[1] = first data byte of the MIDI message, for example: 60
   // message.data[2] = second data byte of the MIDI message, for example 100
   // message.data[3] = not used for any MIDI messages, so set to 0
   message.data[0] = 0x90;  // MIDI note-on message (requires to data bytes)
   message.data[1] = note.getMIDIKey();    // MIDI note-on message: Key number (60 = middle C)
   message.data[2] = 100;   // MIDI note-on message: Key velocity (100 = loud)
   message.data[3] = 0;     // Unused parameter

   // Main event loop
   flag = midiOutShortMsg(device, message.word);
   if (flag != MMSYSERR_NOERROR) printf("Warning: MIDI Output is not open.\n");

   //note-off message
   Sleep(milliseconds);
   message.data[0] = 0x80;
   flag = midiOutShortMsg(device, message.word);
   if (flag != MMSYSERR_NOERROR) printf("Warning: MIDI Output is not open.\n");
}

int playEx()
{
	bool stop=false;
	int midiport = 0;       // select which MIDI output port to open
      
   // Open the MIDI output port
   flag = midiOutOpen(&device, midiport, 0, 0, CALLBACK_NULL);
   if (flag != MMSYSERR_NOERROR) {printf("Error opening MIDI Output.\n"); return 1;}

	Note n;
	n.setOctave(4);
	cout << "Keyboard pos: " << n.getKeyboardPosition() << endl;

	//tempo di 1/8
	unsigned int stdtime = 500;

	n.setNote(NOTEX_E);
	notePlay(n,stdtime);
	notePlay(n,stdtime);

	n.setNote(NOTEX_F);
	notePlay(n, 3*stdtime);
	n.setNote(NOTEX_E);
	notePlay(n, 3*stdtime);

	n.setNote(NOTEX_G);
	notePlay(n, 4*stdtime);
	n.setNote(NOTEX_F);
	notePlay(n, 4*stdtime);

   // turn any MIDI notes currently playing:
   midiOutReset(device);

   // Remove any data in MIDI device and close the MIDI Output port
   midiOutClose(device);

   return 0;
}

void intervalEx()
{
	Note note1 = getNote();
	Note note2 = getNote();
	Interval in(note1, note2);
	in.print();
	cout << endl;
}

void scaleEx()
{
    Note root = getNote();
	bool bre = true;

    string scaleseq;
    do
    {
        cout << "Insert:\n1 for major scale \n2 for natural minor scale\n3 for harmonic minor scale\nChoise: ";
        int num;
        cin>>num;

        switch(num)
        {
            case 1: scaleseq = SCALE_MAJOR; bre=true; break;
            case 2: scaleseq = SCALE_NATURAL_MINOR; bre=true; break;
            case 3: scaleseq = SCALE_HARMONIC_MINOR; bre=true; break;
            default: bre=false; cout << "Invalid choice" << endl;
        }
    }
    while(!bre);

    Scale scale(root, scaleseq);
    scale.print();
    cout<<endl;

    cout << "***********************************************" << endl;
    cout << "Chords triads:" << endl;
    cout << "***********************************************" << endl;

    vector<om::Chord> chords = scale.genChordsTriad();
    for(unsigned i=0; i<chords.size(); i++)
    {
        chords[i].print();
        cout<<endl;
    }

    cout << "***********************************************" << endl;
    cout << "Chords sevenths:" << endl;
    cout << "***********************************************" << endl;

    chords = scale.genChordsSeventh();
    for(unsigned i=0; i<chords.size(); i++)
    {
        chords[i].print();
        cout<<endl;
    }

    cout << "***********************************************" << endl;

}
