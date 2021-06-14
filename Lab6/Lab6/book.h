#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
namespace wm//book
{
	class Event
	{
	private:
		std::string name;
		std::size_t area;
	public:
		bool isMin;
		std::string getName() const;
		bool isEvent(std::string name);//checks name of Event
		Event(std::string name = "-", std::size_t area = 0);
		std::size_t getKey();//returns key by name
		friend std::ostream& operator <<(std::ostream& out, const Event& Event);
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
		std::size_t getKey();
		friend std::ostream& operator <<(std::ostream& out, const Day& Day);
	};
	class Book
	{
	public:
		std::vector<Day> days;

		void addDay(Day Day);//adds Day to this map
		friend std::ostream& operator <<(std::ostream& out, const Book& map);//output for struct MyKey
	};
	std::size_t countKey(const std::string& line);//counts key by line
	Book readdays(std::string path);//reads a events from file
	template<typename T>
	std::ostream& operator <<(std::ostream& out, const std::vector<T>& arr);
	template<typename T>
	std::ostream& operator <<(std::ostream& out, const std::vector<std::shared_ptr<T>>& arr);
	//operators for Event
	bool operator==(Event& Event1, Event& Event2);
	bool operator<=(Event& Event1, Event& Event2);
	bool operator>=(Event& Event1, Event& Event2);
	bool operator>(Event& Event1, Event& Event2);
	bool operator<(Event& Event1, Event& Event2);
	bool operator!=(Event& Event1, Event& Event2);
}
namespace std
{
	string to_string(const wm::Event& Event);
}