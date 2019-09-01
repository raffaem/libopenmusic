#pragma once
#include <string>

enum E_NOTE_EX
{
    NOTEX_C = 0,
    NOTEX_D = 2,
    NOTEX_E = 4,
    NOTEX_F = 5,
    NOTEX_G = 7,
    NOTEX_A = 9,
    NOTEX_B = 11
};

//C=0, D=1, E=2, exc.
unsigned int notex2num(E_NOTE_EX note);

enum E_ALTERATION
{
	DOUBLE_FLAT = -2,
	FLAT,
	NONE,
	SHARP,
	DOUBLE_SHARP
};

class Note
{
	E_NOTE_EX note;
	E_ALTERATION alteration;
	unsigned short int octave;

	unsigned short int duration[2];

public:

	inline void init() {this->note=NOTEX_C; this->octave=4; this->alteration=E_ALTERATION::NONE; this->duration[0]=1; this->duration[1]=4;}

	Note() {this->init();}
	Note(E_NOTE_EX enote, E_ALTERATION ealteration);
	Note(std::string str, bool& res);
	~Note(void);

	inline E_NOTE_EX getNote() {return this->note;}
	inline void setNote(E_NOTE_EX n) {this->note=n;}
	inline unsigned int getNoteU() {return static_cast<unsigned int>(this->note); }
	inline E_ALTERATION getAlteration() {return this->alteration;}
	inline short getAlterationI() {return static_cast<short>(this->alteration);}

	inline unsigned short getOctave() {return this->octave;}
	inline void setOctave(short int oct) {this->octave = oct;}
	inline void setDuration(short int d[2]) {this->duration[0] = d[0]; this->duration[1] = d[1];}

	unsigned int getHalftones(Note b);
	//get line and space distance in the staff
	unsigned int getStaffDist(Note b);

	//C=0, C#=1, D=2, D#=3, E=4, F=5, exc...
	unsigned int getChromatic();
	// Build note from distance on the chromatic scale. 
	//0 <= chromo <= 12. 
	//chromo==0 => C
	//chromo==1 => C#   exc.
	bool fromChromatic(unsigned int chromo);

	void print();
	std::string toStr();

	void addHalftone();
	const Note operator+(const unsigned& halftones);

	//Get position on a 88-Key piano. It has 7 octaves, 3 keys before and 1 key after
	//There are 12 keys in an octave (C-B)
	inline unsigned int getKeyboardPosition() {return 3 + (this->getOctave()-1)*12 + (this->getChromatic()+1);}

	inline unsigned int getMIDIKey() {return this->getKeyboardPosition() + 20;}

	inline bool operator< (Note n) {return this->getKeyboardPosition() < n.getKeyboardPosition();}
	inline bool operator> (Note n) {return this->getKeyboardPosition() > n.getKeyboardPosition();}

	//add half of the duration
	void dot();

};

