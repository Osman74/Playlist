#include "Playlist.h"
int main()
{
	Playlist* P = new Playlist();
	P->push_back(Playlist::Song_Entry(0, "Sia, David Guetta - Floating Through Space"));
	P->push_front(Playlist::Song_Entry(1, "Rag'n'Bone Man - All You Ever Wanted"));
	P->advance_cursor();
	P->insert_at_cursor(Playlist::Song_Entry(2, "Selena Gomez, Rauw Alejandro - Baila Conmigo"));
	std::cout << P->to_string();
	std::cout << "After clear\n";
	P->clear();
	std::cout << P->to_string();
	system("pause");
	return 0;
}