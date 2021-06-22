#include "book.h"

namespace wm
{
	std::size_t countKey(const std::string& line)
	{
		try
		{
			std::size_t x = std::stoi(line);
			return x;
		}
		catch (...)
		{
			std::size_t key = 0;
			for (std::size_t i = 0; i < line.size(); i++)
			{
				int number = tolower(line[i]) - 'a';
				key += number % 10;
				if (i < 8) key *= 10;
			}
			key = key / 10;
			return key;
		}
	}
	std::size_t Event::getKey()
	{
		return countKey(name);
	}
	std::size_t Day::getKey()
	{
		return countKey(name);
	}
	Event::Event(std::string name, std::size_t area) : name(name), area(area), isMin(false) {}
	Day::Day(std::string name, std::size_t area) : name(name), area(area) {}
	void Book::addDay(Day Day)
	{
		days.push_back(Day);
	}
	std::string Event::getName()
		const
	{
		return name;
	}
	void Day::addEvent(Event Event)
	{
		events.push_back(Event);
	}
	std::ostream& operator <<(std::ostream& out, const Event& Event)
	{
		out << Event.name;

		return out;
	}
	std::ostream& operator <<(std::ostream& out, const Day& Day)
	{
		out << Day.name << ": ";
		out << Day.events << std::endl;
		return out;
	}
	std::ostream& operator <<(std::ostream& out, const Book& map)
	{
		out << map.days << std::endl;
		return out;
	}
	template<typename T>
	std::ostream& operator <<(std::ostream& out, const std::vector<T>& arr)
	{
		out << " ";
		for (std::size_t i = 0; i < arr.size(); i++)
		{
			out << arr[i] << " ";
		}
		return out;
	}
	template<typename T>
	std::ostream& operator <<(std::ostream& out, const std::vector<std::shared_ptr<T>>& arr)
	{
		out << " ";
		for (std::size_t i = 0; i < arr.size(); i++)
		{
			if (arr[i]) out << *arr[i] << " ";
			else out << "# ";
		}
		return out;
	}
	bool Event::isEvent(std::string name)
	{
		return (this->name == name);
	}

	Book readdays(std::string path)
	{
		std::ifstream file(path);
		std::size_t DaySize = 0;
		file >> DaySize;
		Book map;
		Day day;
		for (std::size_t i = 0; i < DaySize; i++)
		{
			std::string DayName = "";
			std::size_t EventSize = 0;
			file >> DayName >> EventSize;
			day = Day(DayName);
			for (std::size_t j = 0; j < EventSize; j++)
			{
				std::string EventName = "";
				file >> EventName;
				day.addEvent(Event(EventName));
			}
			map.addDay(day);
		}
		return map;
	}
	bool operator==(Event& Event1, Event& Event2)
	{
		return (Event1.getName() == Event2.getName());
	}
	bool operator<=(Event& Event1, Event& Event2)
	{
		if (Event1.isMin) return true;
		else if (Event2.isMin) return false;
		return (Event1.getKey() <= Event2.getKey());
	}
	bool operator>=(Event& Event1, Event& Event2)
	{
		if (Event2.isMin) return true;
		else if (Event1.isMin) return false;
		return (Event1.getKey() >= Event2.getKey());
	}
	bool operator>(Event& Event1, Event& Event2)
	{
		if (Event2.isMin) return true;
		else if (Event1.isMin) return false;
		return (Event1.getKey() > Event2.getKey());
	}
	bool operator<(Event& Event1, Event& Event2)
	{
		if (Event1.isMin) return true;
		else if (Event2.isMin) return false;
		return (Event1.getKey() < Event2.getKey());
	}
	bool operator!=(Event& Event1, Event& Event2)
	{
		return (Event1.getName() != Event2.getName());
	}
}
namespace std
{
	string to_string(const wm::Event& Event)
	{
		return Event.getName();
	}
}