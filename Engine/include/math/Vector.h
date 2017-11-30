/*
	Vector.h
	Michael Steer
	2017-10-16

	Vector Class

	Wrote by myself as a  challenge to test my programming skills against
	what is reqired to be a c++1z programmer
*/

#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <algorithm>			  // For min and max
#include <type_traits>			  // For StaticAssert calls
#include <array>				  // For std::array
#include <ostream>				  // For std::ostream
#include <numeric>				  // For std::Accumulate		

#include "MathFunc.h"

/* Useful Typedefs */
template<typename, size_t>
class Vector;
template<typename T>
using Vector2 = Vector<T, 2>;
template<typename T>
using Vector3 = Vector<T, 3>;
template<typename T>
using Vector4 = Vector<T, 4>;

using Vector2f = Vector<float, 2>;
using Vector3f = Vector<float, 3>;
using Vector4f = Vector<float, 4>;

using Vector2d = Vector<double, 2>;
using Vector3d = Vector<double, 3>;
using Vector4d = Vector<double, 4>;

/*
	<< Operator for printing the Vector to stream
	Format: [A_i, B_i, ... , N_i]
*/
template<typename T, size_t _size>
std::ostream &operator<<(std::ostream &os, const Vector<T, _size> &out) {
	os << "[";
	for (size_t i = 0; i < _size - 1; i++) {
		os << out[i] << ", ";
	}
	return os << out[out.length() - 1] << "]";
}
								    
/*
	Vector Class
	Way to convey information in the form of vectors

	- The vector must be of a floating point type derivitive and
	  have a non zero size, otherwise the vector will be 
	  static_assert guarded

	Functionality:
	Creation			 - Created either as a blank array of zeros
						   From an array, from an initializer list,
						   From an array of type T, or from another
						   vector

	Deletion			 - Clears all data from inner array before
						   deleting

	arr					 - Returns inner data array
	length				 - Returns the length of the array

	Scalar Operations	 - Operators + - * / += -= *= /= have
						   all been overloaded for per element
						   addition operations. These oparators
						   modify the original vector

	Vector Operations	 - Operators + - * / += -= *= /= have
						   all been overloaded for scalar 
						   modification to all elements. These
						   operators modify the original vector

	Sum					 - Returns the sum of all elements in
						   the vector

	Magnitude			 - Returns the magnitude of the vector

	Normalized		 - Returns a normalized copy of the vector

	Normalize			 - Normalizes the original vector

	Angle				 - Returns the angle between two vectors
						   in radians

	Dot Product			 - Returns the dot product of two vectors

	Cross Product		 - If the vector has a size of 2, the 
						   dot product is returned. 
						 - If the vector has a size of 3, the 
						   cross product is returned
					     - Any other size is static_assert 
						   guarded

	Reversed			 - Returns a reversed copy of the
						   original vector

	Reverse				 - Reverses the order of the vectors
						   elemements within the original 
						   vector


*/
template<typename T, size_t _size>
#ifdef _WIN32
class __declspec(align(16)) Vector {
#elif _LINUX
class __attribute__ align(16) Vector{
#endif
	static_assert(std::is_floating_point<T>::value,
		"Vector Type Error: Must be of floating point type");
	static_assert(_size > 0,
		"Vector Type Error: Size must be nonzero");

private:
	std::array<T, _size> items;	

	friend std::ostream &operator<< <>(std::ostream &os, const Vector &out);
	
	void zeroarr() const { 
		this->items.empty(); 
	}

public:
	Vector() : items() {}
	Vector(std::array<T, _size> values) : items(values) {}

	~Vector() {};

	Vector(const Vector& other) {
		items = other.arr();
	};

	Vector(const Vector&& other) {
		if (this != &other) {
			items.empty();
			items = other.arr();

			other.zeroarr();
		}
	}

	Vector& operator= (const Vector &other) {
		std::swap(items, other.arr());

		return *this;
	}

	std::array<T, _size> arr() const { 
		return items; 
	}

	size_t length() const { 
		return _size;
	}
	
	friend Vector operator+ (Vector org,
							 const Vector &other) {
		org += other;

		return org;
	}

	friend Vector operator+ (Vector org,
							 const T &a) {
		org += a;

		return org;
	}

	friend Vector operator- (Vector org,
						     const Vector &other) {
		org -= other;

		return org;
	}

	friend Vector operator- (Vector org,
							 const T &a) {
		org -= a;

		return org;
	}

	friend Vector operator* (Vector org,
							 const Vector &other) {
		org *= other;

		return org;
	}

	friend Vector operator* (Vector org,
							 const T &a) {
		org *= a;

		return org;
	}

	friend Vector operator/ (Vector org,
							 const Vector &other) {
		return org /= other;
	}

	friend Vector operator/ (Vector org,
							 const T &a) {
		org /= a;

		return org;
	}

	T& operator[](size_t idx){ 
			  return items[idx]; 
	}

	const T& operator[](size_t idx) const { 
		return items[idx]; 
	}

	Vector& operator+= (const Vector& other) {
		for (size_t i = 0; i < arr().size(); i++) {
			items[i] = items[i] + other[i];
		}

		return *this;
	}

	Vector& operator+= (const T& a) {
		for (size_t i = 0; i < arr().size(); i++) {
			items[i] = items[i] + a;
		}

		return *this;
	}

	Vector& operator-= (const Vector& other) {
		for (size_t i = 0; i < arr().size(); i++) {
			items[i] = items[i] - other[i];
		}

		return *this;
	}

	Vector& operator-= (const T& a) {
		for (size_t i = 0; i < arr().size(); i++) {
			items[i] = items[i] - a;
		}

		return *this;
	}

	Vector& operator*= (const Vector& other) {
		for (size_t i = 0; i < arr().size(); i++) {
			items[i] *= other[i];
		}

		return *this;
	}

	Vector& operator*= (const T& a) {
		for (size_t i = 0; i < arr().size(); i++) {
			items[i] = items[i] * a;
		}

		return *this;
	}
	
	Vector& operator/= (const Vector& other) {
		for (size_t i = 0; i < arr().size(); i++) {
			items[i] /= (T)other[i];
		}

		return *this;
	}

	Vector& operator/= (const T& a) {
		for (size_t i = 0; i < arr().size(); i++) {
			items[i] = items[i] / a;
		}

		return *this;
	}

	bool operator== (const Vector& other) {
		for (size_t i = 0; i < _size; i++) {
			if (!closeEquals<T>(other[i], items[i])) {
				return false;
			}
		}

		return true;
	}

	bool operator!= (const Vector& other) {
		return !(*this == other);
	}

	T Sum() const {
		return std::accumulate(items.begin(), items.end(), 0);
	}

	T Magnitude() const {
		T out = 0.0f;
		for (auto item : items) {
			out += item*item;
		}
		out = std::pow(out, 0.5);

		return out;	   
	}

	Vector Normalized() const {
		return *this / Magnitude();
	}

	Vector& Normalize() {
		return Normalized();
	}

	T Angle(Vector &other) const {
		return std::acos(this->dotProduct(other) / (this->magnitude()*other.magnitude));
	}

	T DotProduct(Vector &other) const {
		T out = 0;
		for (size_t i = 0; i < items.size(); i++) {
			out += items[i] * other[i];
		}

		return out;
	}

	T CrossProduct(const Vector2<T> &a, const Vector2<T> &b) {
		return a.DotProduct(b);
	}

	Vector3<T> CrossProduct(const Vector3<T> &a, const Vector3<T> &b) {
		return Vector({ (a[1] * b[2]) - (a[2] * b[1]),
					    (a[2] * b[0]) - (a[0] * b[2]),
						(a[0] * b[1]) - (a[1] * b[0]) });
	}

	auto CrossProduct(const Vector &b) {
		static_assert(_size == 2 || _size == 3, "Vector Error: Cannot perform cross product if size is not 2 or 3");

		return CrossProduct(*this, b);
	}	

	Vector Reversed() const {
		Vector<T, _size> out();
		for (size_t i = 0; i < items.size(); i++) {
			out[i] = items[items.size() - 1 - i];
		}

		return out;
	}

	Vector &Reverse() {
		return Reversed();
	}

};


#endif // __VECTOR_H__