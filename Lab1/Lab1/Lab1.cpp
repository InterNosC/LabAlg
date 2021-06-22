#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>
#include <memory>
#include <string>

namespace ph//perfect hashing
{
	class Event
	{
	private:
		std::string name;
		std::size_t area;
	public:
		bool isEvent(std::string name);//checks name of Event
		Event(std::string name = "Empty", std::size_t area = 0);
		friend std::ostream& operator <<(std::ostream& out, const Event& Event);
		std::size_t getKey()const;//creates key from name
	};
	class Day
	{
	private:
		std::string name;
		std::size_t area;
	public:
		std::vector<Event> events;				

		Day(std::string name = "Empty", std::size_t area = 0);
		void addEvent(Event Event);//adds Event to this Day
		std::size_t getKey()const;//creates key from name
		friend std::ostream& operator <<(std::ostream& out, const Day& Day);
	};	
	class Book
	{	
	public:
		std::vector<Day> days;		

		void addDay(Day Day);//adds Day to this map
		friend std::ostream& operator <<(std::ostream& out, const Book& map);//output for struct MyKey
	};	
	struct Coefficients
	{
		std::size_t m;
		std::size_t a;
		std::size_t b;
		std::size_t p;
		Coefficients(std::size_t m = 1);//creates variables 'a' and 'b'
	};
	class HashTable
	{
	private:
		Coefficients coef;
		std::vector<std::shared_ptr<Event>> table;
	public:
		HashTable(const std::vector<Day>& days);//creates hash table from arr
		HashTable();//default constructor
		friend std::ostream& operator <<(std::ostream& out, const HashTable& hTable);//output for class HashTable
		std::shared_ptr<Event> findEvent(std::string name);//find Event by name
	};
	class PHash
	{
	private:
		std::vector<HashTable> arr;
		Coefficients coef;
	public:
		PHash(const Book& map);//hashes keys to table
		friend std::ostream& operator << (std::ostream& out, const PHash& hTable);//output for class PHash
		std::shared_ptr<Event> findEvent(std::string nameDay, std::string nameEvent);//find Event in Day
	};
	std::size_t countKey(const std::string& line);//counts key by line
	std::size_t hash(std::size_t key, Coefficients coef);//hash function
	template<typename T>
	std::ostream& operator <<(std::ostream& out, const std::vector<std::shared_ptr<T>>& arr);//output for std::vector*
	template<typename T>
	std::ostream& operator <<(std::ostream& out, const std::vector<T>& arr);//output for std::vector
	Book readdays(std::string path);//reads days and events from file
	void findMenu(PHash& pHash);//menu to find Event
	std::vector<std::string> split(std::string line, std::string delimiter);//splir the line
}
namespace ph
{
	Event::Event(std::string name, std::size_t area): name(name), area(area){}
	Day::Day(std::string name, std::size_t area) : name(name), area(area) {}
	void Book::addDay(Day Day)
	{
		days.push_back(Day);
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
	std::size_t Day::getKey()
		const
	{
		return countKey(name);
	}
	std::size_t Event::getKey()
		const
	{
		return countKey(name);
	}
	std::size_t countKey(const std::string& line)
	{
		std::size_t key = 0;
		for (std::size_t i = 0; i < line.size(); i++)
		{
			int number = tolower(line[i]) - 'a';
			key += number % 10;
			if( i < 8) key *= 10;
		}
		key = key/10;

		return key;
	}
	PHash::PHash(const Book& map)
	{
		coef = Coefficients(map.days.size());
		arr = std::vector<HashTable>(coef.m);
		std::vector<std::vector<Day>> matrix(coef.m);
		for (std::size_t i = 0; i < coef.m; i++)
		{
			std::size_t j = hash(map.days[i].getKey(), coef);
			matrix[j].push_back(map.days[i]);
		}
		for (std::size_t i = 0; i < coef.m; i++)
		{
			arr[i] = HashTable(matrix[i]);
		}
	}
	std::ostream& operator << (std::ostream& out, const PHash& h)
	{
		out << h.arr;
		return out;
	}
	std::size_t hash(std::size_t key, Coefficients coef)
	{
		return (((coef.a * key + coef.b ) % coef.p) % coef.m);
	}
	Coefficients::Coefficients(std::size_t m)
		: m(m), p(101)
	{
		a = rand() % p;
		b = rand() % (p - 1) + 1;
	}
	HashTable::HashTable(const std::vector<Day>& days)
		:coef(Coefficients(0))
	{
		for (std::size_t i = 0; i < days.size(); i++)
			coef.m += days[i].events.size();
		coef.m *= coef.m;
		table = std::vector<std::shared_ptr<Event>>(coef.m, nullptr);
		for (std::size_t k = 0; k < days.size(); k++)
		{
			for (std::size_t i = 0; i < days[k].events.size(); i++)
			{
				std::size_t j = hash(days[k].events[i].getKey(), coef);
				while (table[j])
				{
					j++;
					if (j >= coef.m) j = 0;
				}
				table[j] = std::make_shared<Event>(days[k].events[i]);
			}
		}		
	}
	HashTable::HashTable() : table({}), coef(1) {}
	std::ostream& operator <<(std::ostream& out, const HashTable& hTable)
	{
		out << std::endl << "m=" << hTable.coef.m << ", a=" << hTable.coef.a << ", b=" << hTable.coef.b << " -> ";
		out << hTable.table;
		return out;
	}
	std::shared_ptr<Event> PHash::findEvent(std::string nameDay, std::string nameEvent)
	{
		std::size_t j = hash(countKey(nameDay), coef);
		return arr[j].findEvent(nameEvent);
	}
	bool Event::isEvent(std::string name)
	{
		return (this->name == name);
	}
	std::shared_ptr<Event> HashTable::findEvent(std::string name)
	{
		std::size_t j = hash(countKey(name), coef);
		std::size_t i = 0;
		while (table[j] && !table[j]->isEvent(name))
		{
			j++;
			i++;
			if (j >= table.size()) j = 0;
			if (i == table.size()) break;
		}
		if(table[j]) return table[j];
		return nullptr;
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

	void findMenu(PHash& pHash)
	{
		while (true)
		{
			std::string line = "0";
			std::cout << "Enter name of Day "
				<< "and name of Event to find Event in hash "
				<< "table or enter 0 to exit:" << std::endl;
			getline(std::cin,line);
			if (line == "0") return;
			std::vector<std::string> lines = split(line, " ");
			if (lines.size() != 2)
			{
				std::cout << "Incorrect data!" << std::endl;
				return;
			}
			std::shared_ptr<Event> Event = pHash.findEvent(lines[0], lines[1]);
			if (Event) std::cout << *Event << " was found!" << std::endl;
			else std::cout << "Entered Event wasn't found!" << std::endl;
		}
	}

	std::vector<std::string> split(std::string line, std::string delimiter)
	{
		std::vector<std::string> lines;
		size_t pos = 0;
		std::string token;
		while ((pos = line.find(delimiter)) != std::string::npos) {
			token = line.substr(0, pos);
			lines.push_back(token);
			line.erase(0, pos + delimiter.length());
		}
		lines.push_back(line);
		return lines;
	}
}

using namespace ph;
int main()
{
	std::string inPath = "input.txt", outPath = "output.txt";
	std::cout << "Reads days from file '" << inPath 
		<< "' and creates Hash table!" << std::endl;
	PHash pHash = PHash(readdays(inPath));
	std::ofstream file(outPath);
	file << pHash << std::endl;
	std::cout << "Hash table is added to file '" << outPath << "'." << std::endl;
	findMenu(pHash);
    return 0;
}
