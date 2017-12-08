/*
	MathFunc.h
	Michael Steer
	2017-11-05

	Utility math funcitons that don't deserve
	their own files 
*/


#ifndef __MATHFUNC_H__
#define __MATHFUNC_H__

/*
	Returns True if two floats are roughly the same
*/
template<typename T>
inline bool closeEquals(T a, T b, T sigma = 0.0001f) {
	return (a <= (b + sigma/2)) && (a >= (b - sigma/2));
}

#endif // __MATHFUNC_H__