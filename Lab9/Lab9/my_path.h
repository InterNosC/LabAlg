#pragma once

namespace mpath//my path
{
	template<typename T>
	struct Path
	{
		T distance;
		bool isMax;
		Path(T distance = T(), bool isMax = true);
		bool operator==(const Path<T>& path2);
		bool operator!=(const Path<T>& path2);
		bool operator>(const Path<T>& path2);
		bool operator<(const Path<T>& path2);
		bool operator>=(const Path<T>& path2);
		bool operator<=(const Path<T>& path2);
		Path<T>& operator=(const Path<T>& path2);
	};
}
namespace mpath
{
	template<typename T>
	Path<T>::Path(T distance, bool isMax):distance{distance},isMax{isMax}{}
	template<typename T>
	bool Path<T>::operator==(const Path<T>& path2)
	{
		return (this->isMax == path2.isMax && this->distance == path2.distance);
	}
	template<typename T>
	bool Path<T>::operator!=(const Path<T>& path2)
	{
		return (this->isMax != path2.isMax || this->distance != path2.distance);
	}
	template<typename T>
	bool Path<T>::operator>(const Path<T>& path2)
	{
		if (this->isMax) return true;
		else if (path2.isMax) return false;
		return (this->distance > path2.distance);
	}
	template<typename T>
	bool Path<T>::operator<(const Path<T>& path2)
	{
		if (this->isMax) return false;
		else if (path2.isMax) return true;
		return (this->distance < path2.distance);
	}
	template<typename T>
	bool Path<T>::operator>=(const Path<T>& path2)
	{
		return (*this == path2 || *this > path2);
	}
	template<typename T>
	bool Path<T>::operator<=(const Path<T>& path2)
	{
		return (*this == path2 || *this < path2);
	}
	template<typename T>
	Path<T>& Path<T>::operator=(const Path<T>& path2)
	{
		this->distance = path2.distance;
		this->isMax = path2.isMax;

		return *this;
	}
}