#pragma once
#include "PluginSDK.h"
#include <algorithm>

using namespace std;

#pragma region template
template <class T>
class SArray {
public:
	SArray() {};
	SArray(vector<T> Svector) { elems = Svector; };
private:
	vector<T> elems;     // elements 

public:
	SArray<T> Add(T);
	SArray<T> RemoveAll(std::function<bool(T)>);
	SArray<T> RemoveAll()
	{
		elems.clear();
		return SArray<T>(elems);
	}
	SArray<T> Where(std::function<bool(T)>);
	SArray<T> AddRange(SArray<T>);
	SArray<T> AddRange(vector<T>);
	bool Any(std::function<bool(T)>);
	bool Any()
	{
		return !elems.empty();
	}
	vector<T> ToVector()
	{
		return elems;
	}
	template<class T2>
	SArray<T2> Select(std::function<T2(T)>);
	T FirstOrDefault(std::function<bool(T)>);
	T FirstOrDefault()
	{
		if (elems.empty())
			return T();
		return elems.front();
	};
	T LastOrDefault(std::function<bool(T)>);
	T LastOrDefault()
	{
		if (elems.empty())
			return T();
		return elems.back();
	};
	template <class T2>
	T MinOrDefault(std::function<T2(T)>);
	template <class T2>
	T MaxOrDefault(std::function<T2(T)>);
	int Count()
	{
		return elems.size();
	}
	template <class T2>
	SArray<T> OrderBy(std::function<T2(T)>);
};


template <class T>
SArray<T> SArray<T>::Add(T elem)
{
	elems.push_back(elem);
	return SArray<T>(elems);
}
template <class T>
SArray<T> SArray<T>::AddRange(SArray<T> elemstoadd)
{
	vector<T> vec = elemstoadd.ToVector();
	elems.insert(elems.end(), vec.begin(), vec.end());
	return SArray<T>(elems);
}
template <class T>
SArray<T> SArray<T>::AddRange(vector<T> vec)
{
	elems.insert(elems.end(), vec.begin(), vec.end());
	return SArray<T>(elems);
}


template <class T>
SArray<T> SArray<T>::RemoveAll(std::function<bool(T)> Remove)
{
	vector<T> newelems;
	for each (T i in elems)
	{
		if (!Remove(i))
			newelems.push_back(i);
	}
	elems = newelems;
	return SArray<T>(newelems);
}

template<class T>
SArray<T> SArray<T>::Where(std::function<bool(T)> Where)
{
	vector<T> newvec;
	for each (T i in elems)
	{
		if (Where(i))
			newvec.push_back(i);
	}
	return newvec;
}

template<class T>
bool SArray<T>::Any(std::function<bool(T)> Any)
{
	vector<T> newelems;
	newelems = this->Where([&](T i) {return Any(i); }).ToVector();
	return !newelems.empty();
}

template<class T>
template<class T2>
SArray<T2> SArray<T>::Select(std::function<T2(T)> Select)
{
	vector<T2> newelems;
	for each (T i in elems)
	{
		newelems.push_back(Select(i));
	}
	return SArray<T2>(newelems);
}

template <class T>
T SArray<T>::FirstOrDefault(std::function<bool(T)> FirstOrDefault)
{
	vector<T> newvec;
	newvec = this->Where([&](T i) {return FirstOrDefault(i); }).ToVector();
	if (newvec.empty())
		return T();
	return newvec.front();
}

template <class T>
T SArray<T>::LastOrDefault(std::function<bool(T)> LastOrDefault)
{
	vector<T> newvec;
	newvec = this->Where([&](T i) {return LastOrDefault(i); }).ToVector();
	if (newvec.empty())
		return T();
	return newvec.back();
}

template <class T>
template <class T2>
T SArray<T>::MinOrDefault(std::function<T2(T)> MinOrDefault)
{
	vector<T> newvec;
	newvec = elems;
	T returnelem;
	returnelem = T();
	if (newvec.empty())
		return returnelem;
	returnelem = newvec.front();
	for each (T i in newvec)
	{
		if (MinOrDefault(i) < MinOrDefault(returnelem))
			returnelem = i;
	}
	return returnelem;
}

template <class T>
template <class T2>
T SArray<T>::MaxOrDefault(std::function<T2(T)> MaxOrDefault)
{
	vector<T> newvec;
	newvec = elems;
	T returnelem;
	returnelem = T();
	if (newvec.empty())
		return returnelem;
	returnelem = newvec.front();
	for each (T i in newvec)
	{
		if (MaxOrDefault(i) > MaxOrDefault(returnelem))
			returnelem = i;
	}
	return returnelem;
}

template<class T>
template<class T2>
SArray<T> SArray<T>::OrderBy(std::function<T2(T)> OrderBy)
{
	std::sort(elems.begin(), elems.end(), [&](T a, T b) { return OrderBy(a) < OrderBy(b); });
	return SArray<T>(elems);
}


#pragma  endregion 

class FarmLocation
{
public:
	Vec3 CastPosition;
	Vec3 CastPositionFrom;
	int HitCount = 0;
	IUnit* CastOnUnit = nullptr;
	FarmLocation(Vec3 castposition, Vec3 castpositionfrom, int hitcount, IUnit* castonunit)
	{
		CastPosition = castposition;
		CastPositionFrom = castpositionfrom;
		HitCount = hitcount;
		CastOnUnit = castonunit;
	}
	FarmLocation() {};
};