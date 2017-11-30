/*
	Matrix.h
	Michael Steer
	2017-11-05
	
	Matrix Class
*/
#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <array>		// std::array
#include <type_traits>  // for static_assert stuff
#include <ostream>		// std::ostream
#include <iostream>		// std::cout, std::endl

#include "Vector.h"
template<typename, size_t, size_t>
class Matrix;



template<typename T, size_t m, size_t n>
std::ostream &operator<<(std::ostream &os, const Matrix<T, m, n> &out) {
	os << "[ ";
	for (size_t i = 0; i < m; i++) {
		for (size_t j = 0; j < n-1; j++) {
			os << out.get(i, j) << ", ";
		}
		os << out.get(i, n - 1) << std::endl << " "
	}
	os << " ]";

	return os;
}

template<typename T, size_t _m, size_t _n>
class Matrix {
	static_assert(std::is_floating_point<T>::value,
			      "Martix Error: Type is not of floating point derivitie");
	static_assert(_m > 0,
				  "Matrix Error: size m must be at least 1");
	static_assert(_n > 0,
				  "Matrix Error: size m must be at least 1");
private:
	std::array<T, _m*_n> items;

	/* Takes in a set of coordanates m, n and returns m*n+t */
	size_t mn_t(size_t mi, size_t ni) const {
		return mi*_m + ni;
	}

	void zeroarr() const {
		this->items.empty();
	}

public:
	Matrix() : items() {}
	Matrix(std::array<T, _m*_n> values) : items(values) {}
	
	~Matrix() {}

	Matrix(const Matrix &other) {
		items = other.arr();
	}

	Matrix(const Matrix &&other) {
		if (this != &other) {
			items.empty();
			items = other.arr();

			other.zeroarr();
			
		}
	}

	Matrix &operator= (const Matrix &other) {
		std::swap(items, other.arr());
		return *this;
	}

	std::array<T, _m*_n> arr() const {
		return items;
	}

	size_t nRows() const {
		return _m;
	}

	size_t nColumns() const {
		return _n;
	}

	T get(size_t mi, size_t ni) const {
		return this[mn_t(mi, ni)];
	}

	std::array<T, _m> getRow(size_t n) const {
		std::array<T, _m> out;
		for (size_t i = 0; i < _m; i++) out[i] = items[mn_t(i, n)];
		return out;
	}

	Vector<T, _m> getRowVector(size_t n) const {
		return Vector<T, _m>(getRow(n));
	}

	std::array<T, _n> getColumn(size_t m) const {
		std::array<T, _m> out;
		for (size_t i = 0; i < _n; i++) out[i] = items[mn_t(m, i)];
		return out;
	}

	Vector<T, _n> getColumnVector(size_t n) const {
		return Vector(getRow(n));
	}
};

#endif // __MATRIX_H__
