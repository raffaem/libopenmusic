#include "interval.hpp"
#include <iostream>

using namespace std;

std::string quality2str(E_INTERVAL_QUALITY quality)
{
	string str;
	switch(quality)
	{
		case E_INTERVAL_QUALITY::AUGMENTED: str = string("augmented"); break;
		case E_INTERVAL_QUALITY::DIMINISHED: str = string("diminished"); break;
		case E_INTERVAL_QUALITY::MAJOR: str = string("major"); break;
		case E_INTERVAL_QUALITY::MINOR: str = string("minor"); break;
		case E_INTERVAL_QUALITY::PERFECT: str = string("perfect"); break;
		default: str = string("unrecognized"); break;
	}
	return str;
}

const int interval_halftones[] =
{
	0, // 1 perfect
	2, //2 major
	4, //3 major
	5, //4 perfect
	7, //5 perfect
	9, //6 major
	11, //7 major
	12 //8 perfect
};

Interval::Interval(Note a, Note b)
{
	this->type = a.getStaffDist(b) + 1;

	unsigned int normal_ht = interval_halftones[this->type-1];
	unsigned int real_ht = a.getHalftones(b);
	int diff = real_ht - normal_ht;

	//2,3,6,7 are majors
	if(this->type == 2 || this->type == 3 || this->type == 6 || this->type == 7)
	{
		if(diff == 0) {this->quality = E_INTERVAL_QUALITY::MAJOR;}
		else if(diff == -1) {this->quality = E_INTERVAL_QUALITY::MINOR;}
		else if(diff == -2) {this->quality = E_INTERVAL_QUALITY::DIMINISHED;}
		else if(diff == 1) {this->quality = E_INTERVAL_QUALITY::AUGMENTED;}
	}

	//1,4,5,8 are perfects
	else if(this->type == 1 || this->type == 4 || this->type == 5 || this->type == 8)
	{
		if(diff == 0) {this->quality = E_INTERVAL_QUALITY::PERFECT;}
		else if(diff == -1) {this->quality = E_INTERVAL_QUALITY::DIMINISHED;}
		else if(diff == 1) {this->quality = E_INTERVAL_QUALITY::AUGMENTED;}
	}
}

Interval::~Interval(void)
{
}

void Interval::print()
{
	cout << this->type << " " << quality2str(this->quality);
}
