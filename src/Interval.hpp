#pragma once
#include "note.hpp"
#include <string>

enum E_INTERVAL_QUALITY
{
	AUGMENTED=1,
	MAJOR,
	MINOR,
	DIMINISHED,
	PERFECT
};

std::string quality2str(E_INTERVAL_QUALITY quality);

class Interval
{
	E_INTERVAL_QUALITY quality;
	unsigned type;

public:
	Interval(Note a, Note b);
	~Interval(void);
	void print();
};

