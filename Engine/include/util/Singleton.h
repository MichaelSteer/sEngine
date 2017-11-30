/*
	Singleton.h
	Michael Steer
	2017-08-03
*/

#ifndef __SINGLETON_H__
#define __SINGLETON_H__


template<class T, typename... Args>
class Singleton {
public:
	static T& getInstance(Args... args) {
		static T instance(args...);
		std::cout << "&T:" << &instance << std::endl;
		return instance;
	}
protected:
	Singleton() {}
	~Singleton() {}
private:
	Singleton(const Singleton & other) = delete;
	Singleton& operator=(const Singleton & other) = delete;
	Singleton& operator=(const Singleton && other) = delete;
};

#endif // __SINGLETON_H__