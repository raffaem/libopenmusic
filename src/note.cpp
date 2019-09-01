#include "note.hpp"
#include <algorithm>
#include <iostream>
using namespace std;

unsigned int notex2num(E_NOTE_EX note)
{
	unsigned nthis;
	switch(note)
	{
		case NOTEX_C: nthis=0; break;
		case NOTEX_D: nthis=1; break;
		case NOTEX_E: nthis=2; break;
		case NOTEX_F: nthis=3; break;
		case NOTEX_G: nthis=4; break;
		case NOTEX_A: nthis=5; break;		
		case NOTEX_B: nthis=6; break;
		default: break;
	}
	return nthis;
}

std::string notex2str(E_NOTE_EX note)
{
	string str;
	switch(note)
	{
		case NOTEX_C: str=string("C"); break;
		case NOTEX_D: str=string("D"); break;
		case NOTEX_E: str=string("E"); break;
		case NOTEX_F: str=string("F"); break;
		case NOTEX_G: str=string("G"); break;
		case NOTEX_A: str=string("A"); break;		
		case NOTEX_B: str=string("B"); break;
		default: break;
	}
	return str;
}

Note::Note(std::string str, bool& res)
{
	this->init();

	res=true;
    std::transform(str.begin(), str.end(), str.begin(), ::toupper);

	char n = str[0];

	switch(n)
	{
		case 'C': this->note=NOTEX_C; break;
		case 'D': this->note=NOTEX_D; break;
		case 'E': this->note=NOTEX_E; break;
		case 'F': this->note=NOTEX_F; break;
		case 'G': this->note=NOTEX_G; break;
		case 'A': this->note=NOTEX_A; break;
		case 'B': this->note=NOTEX_B; break;
		default: break;
	}

	if(str.size() == 2)
	{
		if(str[1] == 'S' || str[1] == '#') this->alteration = E_ALTERATION::SHARP;
		else if(str[1] == 'B') this->alteration = E_ALTERATION::FLAT;
	}

	else if(str.size() == 3)
	{
		if(str[2] == 'S' || str[2] == '#') this->alteration = E_ALTERATION::DOUBLE_SHARP;
		else if(str[2] == 'B') this->alteration = E_ALTERATION::DOUBLE_FLAT;
	}
    
}

Note::Note(E_NOTE_EX enote, E_ALTERATION ealteration)
{
	this->init();
	this->note=enote;
	this->alteration=ealteration;
}

Note::~Note(void)
{
}

unsigned int Note::getHalftones(Note b)
{
	int ht = b.getNoteU() + b.getAlterationI() - this->getNoteU() - this->getAlterationI();
	if(ht<0)
		ht = 12 + ht;
	return ht;
}

unsigned int Note::getStaffDist(Note b)
{
	unsigned int nthis = notex2num(this->note);
	unsigned int nb = notex2num(b.note);
	return nb-nthis; 
}

string Note::toStr()
{
	string base = notex2str(this->note);

	switch(this->alteration)
	{
	case E_ALTERATION::SHARP: base += string("#"); break;
	case E_ALTERATION::DOUBLE_SHARP: base += string("##"); break;
	case E_ALTERATION::FLAT: base += string("b"); break;
	case E_ALTERATION::DOUBLE_FLAT: base += string("bb"); break;
	}

	return base;
}

void Note::print()
{
	cout << this->toStr();
}

unsigned int Note::getChromatic()
{
	unsigned int chromo;

	switch(this->note)
	{
		case E_NOTE_EX::NOTEX_C: chromo = 0; break;
		case E_NOTE_EX::NOTEX_D: chromo = 2; break;
		case E_NOTE_EX::NOTEX_E: chromo = 4; break;
		case E_NOTE_EX::NOTEX_F: chromo = 5; break;
		case E_NOTE_EX::NOTEX_G: chromo = 7; break;
		case E_NOTE_EX::NOTEX_A: chromo = 9; break;
		case E_NOTE_EX::NOTEX_B: chromo = 11; break;
	}

	switch(this->alteration)
	{
		case E_ALTERATION::NONE: break;
		case E_ALTERATION::SHARP: chromo += 1; break;
		case E_ALTERATION::DOUBLE_SHARP: chromo += 2; break;
		case E_ALTERATION::FLAT: chromo -= 1; break;
		case E_ALTERATION::DOUBLE_FLAT: chromo -= 2; break;
		default: break;
	}

	return chromo;
}

bool Note::fromChromatic(unsigned int ch)
{
	switch(ch)
	{
	case 0: this->note = NOTEX_C; this->alteration = E_ALTERATION::NONE; return true; break;
	case 1: this->note = NOTEX_C; this->alteration = E_ALTERATION::SHARP; return true; break;
	case 2: this->note = NOTEX_D; this->alteration = E_ALTERATION::NONE; return true; break;
	case 3: this->note = NOTEX_D; this->alteration = E_ALTERATION::SHARP; return true; break;
	case 4: this->note = NOTEX_E; this->alteration = E_ALTERATION::NONE; return true; break;
	case 5: this->note = NOTEX_F; this->alteration = E_ALTERATION::NONE; return true; break;
	case 6: this->note = NOTEX_F; this->alteration = E_ALTERATION::SHARP; return true; break;
	case 7: this->note = NOTEX_G; this->alteration = E_ALTERATION::NONE; return true; break;
	case 8: this->note = NOTEX_G; this->alteration = E_ALTERATION::SHARP; return true; break;
	case 9: this->note = NOTEX_A; this->alteration = E_ALTERATION::NONE; return true; break;
	case 10: this->note = NOTEX_A; this->alteration = E_ALTERATION::SHARP; return true; break;
	case 11: this->note = NOTEX_B; this->alteration = E_ALTERATION::NONE; return true; break;
	case 12: this->note = NOTEX_C; this->alteration = E_ALTERATION::NONE; this->octave += 1; return true; break;
	default: return false;
	}
}

void Note::addHalftone()
{
	this->fromChromatic(this->getChromatic()+1);
}

const Note Note::operator+(const unsigned& halftones)
{
	Note n(*this);

    for(unsigned int i=1; i<=halftones; i++)
	{
		n.addHalftone();
	}

	return n;
}

void Note::dot()
{
	// d1 = d0 + d0/2 = (3/2) d0
	this->duration[0] *= 3;
	this->duration[1] *= 2;
}
