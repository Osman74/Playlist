#pragma once
#include <string>
#include <iostream>
class Playlist
{
public:
	class Song_Entry {
	private:
		int _id;
		std::string _name;
	public:
		Song_Entry(int id = 0, std::string name = "Unnamed")
			: _id(id), _name(name) {}
		int get_id() const { return _id; }
		std::string get_name() const { return _name; }
		bool set_id(int id);
		bool set_name(std::string name);
		bool operator==(const Song_Entry& that) {
			return this->_id == that._id && this->_name == that._name;
		}
		bool operator!=(const Song_Entry& that) {
			return !(*this == that);
		}
		friend std::ostream& operator<<(std::ostream& os, const Song_Entry& s) {
			return os << "{ id: " << s.get_id() << ", name: " << s.get_name() << " }";
		}
		friend class Tests; // Don't remove this line
	};
	Playlist();
	~Playlist();
};

