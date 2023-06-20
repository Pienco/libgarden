#ifndef UTIL_FACTORY_HPP
#define UTIL_FACTORY_HPP


template<typename T, typename... Args>
using Creator = T * (*)(Args&&... args);

template<typename T>
using Destroyer = void(*)(T*);


template<typename T>
class Factory
{

public:

	inline static T* Create()
	{
		return new T();
	}
	inline static void Destroy(T* ptr)
	{
		delete ptr;
	}
};

#endif
