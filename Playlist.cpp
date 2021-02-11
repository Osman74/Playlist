#include "Playlist.h"



Playlist::Playlist()
{
}


Playlist::~Playlist()
{
}

bool Playlist::Song_Entry::set_id(int id)
{
	if (id < 0)
		return false;
	else
		_id = id;
	return true;
}

bool Playlist::Song_Entry::set_name(std::string name)
{
	if (name == "")
		return false;
	else
		_name = name;
	return true;
}