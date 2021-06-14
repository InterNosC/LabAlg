#pragma once

namespace mp//my pair
{
	template<typename T, typename U>
	struct Pair
	{
		T first;
		U second;
		Pair(T first = T(), U second = U());
		bool operator==(const Pair<T, U>& pair2);
		bool operator!=(const Pair<T, U>& pair2);
		bool operator>(const Pair<T, U>& pair2);
		bool operator<(const Pair<T, U>& pair2);
		bool operator>=(const Pair<T, U>& pair2);
		bool operator<=(const Pair<T, U>& pair2);
		Pair<T, U>& operator=(const Pair<T, U>& pair2);
	};
}
namespace mp
{
	template<typename T, typename U>
	Pair<T, U>::Pair(T first, U second) :first{ first }, second{ second }{}
	template<typename T, typename U>
	bool Pair<T, U>::operator==(const Pair<T, U>& pair2)
	{
		return (this->first == pair2.first);
	}
	template<typename T, typename U>
	bool Pair<T, U>::operator!=(const Pair<T, U>& pair2)
	{
		return (this->first != pair2.first);
	}
	template<typename T, typename U>
	bool Pair<T, U>::operator>(const Pair<T, U>& pair2)
	{
		return (this->first > pair2.first);
	}
	template<typename T, typename U>
	bool Pair<T, U>::operator<(const Pair<T, U>& pair2)
	{
		return (this->first < pair2.first);
	}
	template<typename T, typename U>
	bool Pair<T, U>::operator>=(const Pair<T, U>& pair2)
	{
		return (this->first >= pair2.first);
	}
	template<typename T, typename U>
	bool Pair<T, U>::operator<=(const Pair<T, U>& pair2)
	{
		return (this->first <= pair2.first);
	}
	template<typename T, typename U>
	Pair<T, U>& Pair<T, U>::operator=(const Pair<T, U>& pair2)
	{
		this->first = pair2.first;
		this->second = pair2.second;
		return *this;
	}
}