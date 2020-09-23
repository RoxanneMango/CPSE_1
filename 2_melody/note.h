#ifndef NOTE_H
#define NOTE_H

class Note
{
public:
	const int & frequency;
	const int & duration;
	Note(const int & frequency, const int & duration) : frequency(frequency), duration(duration)
	{}
};

#endif // NOTE_H