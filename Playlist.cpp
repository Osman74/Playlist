#include "Playlist.h"



Playlist::Playlist()
{
	_head = new Node();
	_tail = new Node();
	_prev_to_current = new Node();
}


Playlist::~Playlist()
{
	delete _head;
	delete _tail;
	delete _prev_to_current;
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

Playlist::Node* Playlist::Node::insert_next(Node *p)
{
	Node* tmp = this->get_next();
	_next = p;
	p->_next = tmp;
	return this;
}

Playlist* Playlist::insert_at_cursor(const Playlist::Song_Entry& s)
{
	Node* tmp = new Node(s);
	_prev_to_current->insert_next(tmp);
	_size++;
	return this;
}

Playlist* Playlist::push_back(const Song_Entry& s)
{
	Node* tmp = _prev_to_current;
	_prev_to_current = _tail;
	insert_at_cursor(s);
	if (tmp->get_next() != nullptr)
	{
		_prev_to_current = tmp;
		_tail = _tail->get_next();
	}
	else
	{
		_head = _prev_to_current;
		_tail = _prev_to_current->get_next();
	}

	return this;
}

Playlist* Playlist::push_front(const Song_Entry& s)
{
	Node* tmp = _prev_to_current;
	_prev_to_current = _head;
	insert_at_cursor(s);
	_prev_to_current = tmp;
	return this;
}

Playlist* Playlist::advance_cursor()
{
	if (_prev_to_current->get_song().get_id() == _tail->get_song().get_id())
		_prev_to_current = nullptr;
	else
		_prev_to_current = _prev_to_current->get_next();
	return this;
}

Playlist* Playlist::circular_advance_cursor()
{
	if (_prev_to_current->get_song().get_id() == _tail->get_song().get_id())
		_prev_to_current = _head;
	else
		_prev_to_current = _prev_to_current->get_next();
	return this;
}

Playlist::Song_Entry& Playlist::get_current_song() const
{
	if (_prev_to_current->get_song().get_id() == _tail->get_song().get_id())
		return _head->get_song();
	return _prev_to_current->get_next()->get_song();
}

Playlist::Node* Playlist::Node::remove_next()
{
	Node* tmp = _next;
	_next = _next->_next;
	delete tmp;
	return this;
}

Playlist* Playlist::remove_at_cursor()
{
	_prev_to_current->remove_next();
	_size--;
	return this;
}

Playlist* Playlist::rewind()
{
	_prev_to_current = _head;
	return this;
}

Playlist* Playlist::clear()
{
	Node* tmp = _head;
	while (_head->get_next()->get_song().get_id() != _tail->get_song().get_id())
		tmp->remove_next();
	_head->remove_next();
	_prev_to_current = _head;
	_tail = _head;
	_size = 0;
	return this;
}

Playlist::Song_Entry& Playlist::find_by_id(int id) const
{
	Node* tmp = _head;
	while (tmp != _tail)
		if (tmp->get_song().get_id() == id)
			return tmp->get_song();
	if (_tail->get_song().get_id() == id)
		return _tail->get_song();
	return _head->get_song();
}
Playlist::Song_Entry& Playlist::find_by_name(std::string songName) const
{
	Node* tmp = _head;
	while (tmp != _tail)
		if (tmp->get_song().get_name() == songName)
			return tmp->get_song();
	if (_tail->get_song().get_name() == songName)
		return _tail->get_song();
	return _head->get_song();
}

std::string Playlist::to_string() const
{
	std::string str = std::string();
	str = "Playlist: [" + std::to_string(_size) + "] entries.\n";
	if (_size == 0)
		return str;
	int i = 0;
	Node* tmp = _head->get_next();
	while ((i < 25) && (tmp->get_song().get_id() != _tail->get_song().get_id()))
	{
		str += "{ id: [" + std::to_string(tmp->get_song().get_id()) + "], name: [" + tmp->get_song().get_name() + "] }";
			if (tmp->get_song().get_id() == _prev_to_current->get_song().get_id())
				str += " [P]";
		str += "\n";
		i++;
		tmp = tmp->get_next();
	}
	if (tmp == _tail)
	{
		str += "{ id: [" + std::to_string(tmp->get_song().get_id()) + "], name: [" + tmp->get_song().get_name() + "] } [T]\n";
		return str;
	}

	str += "...\n";
	str += "{ id: [" + std::to_string(tmp->get_song().get_id()) + "], name: [" + tmp->get_song().get_name() + "] } [P]\n";
	str += "...\n";
	str += "{ id: [" + std::to_string(tmp->get_song().get_id()) + "], name: [" + tmp->get_song().get_name() + "] } [T]";
	return str;
}
