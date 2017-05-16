
#ifndef MATRIX_HPP
#define MATRIX_HPP




#include <utility>
#include <iostream>
#include <vector>

#include "errors.hpp"


template <class T>
class Vec2 {
	public:
	
	std::vector<T> v;
	bool col = 1;
	bool row = 0;
	
	
	Vec2(){
		v.push_back(0);
		v.push_back(0);
	}

	//constructor from two numbers
    Vec2(const T& vx, const T& vy) {
		v.push_back(vx);
		v.push_back(vy);		
	}
	
	//constructor from pair
	Vec2(const std::pair<T,T>& a ){
		v.push_back(a.first);
		v.push_back(a.second);
	}	
	
	//desttuctor
	~Vec2(){}
	
	//acces operator
	const double& operator[](int i) const{
		if(i < 0 or i >= v.size()){
			throw IndexOutOfBoundsError;
		}
		return v[i];
	}
	
	//non-const access
	double& operator[](int i){
		if(i < 0 or i >= v.size()){
			throw IndexOutOfBoundsError;
		}
		return v[i];
	}
	
	 Vec2 operator-() const { return Vec2(-v[0], -v[1]); }
	
	Vec2& operator+=(const Vec2& vec) { v[0] += vec[0]; v[1] += vec[1]; return *this; }
    Vec2& operator-=(const Vec2& vec) { v[0] -= vec[0]; v[1] -= vec[1]; return *this; }
    Vec2& operator*=(const Vec2& vec) { v[0] *= vec[0]; v[1] *= vec[1]; return *this; }
	
	Vec2& operator*=(const double& n) { v[0] *= n; v[1] *= n; return *this; }
	Vec2& operator*=(const int& n) { v[0] *= n; v[1] *= n; return *this; }
	Vec2& operator/=(const double& n) { v[0] /= n; v[1] /= n; return *this; }
	Vec2& operator/=(const int& n) { v[0] /= n; v[1] /= n; return *this; }
	
	
	//Check if the Vectors have the same values (uses pairwise comparison of `std::tuple` on the x,y values of L and R.
    friend bool operator==(const Vec2& L, const Vec2& R) { return L[0] == R[0] and L[1] ==R[1]; }
    friend bool operator!=(const Vec2& L, const Vec2& R) { return !(L == R); }
	
	
	
	//output overloading
	friend std::ostream& operator<<(std::ostream &os,const  Vec2 &vec){
		std::cout << "[" << vec[0] << "," << vec[1] << "]" << std::endl;
	}
	
		
	
};

template<class T> Vec2<T> operator+(const Vec2<T>& L, const Vec2<T>& R) { return Vec2<T>(L) += R; }
template<class T> Vec2<T> operator-(const Vec2<T>& L, const Vec2<T>& R) { return Vec2<T>(L) -= R; }
template<class T> Vec2<T> operator*(const Vec2<T>& L, const Vec2<T>& R) { return Vec2<T>(L) *= R; }
template<class T> Vec2<T> operator/(const Vec2<T>& L, const Vec2<T>& R) { return Vec2<T>(L) /= R; }

template<class T> Vec2<T> operator*(const T& s, const Vec2<T>& v) { return Vec2<T>(v) *= s; }
template<class T> Vec2<T> operator*(const Vec2<T>& v, const T& s) { return Vec2<T>(v) *= s; }
template<class T> Vec2<T> operator/(const T& s, const Vec2<T>& v) { return Vec2<T>(v) /= s; }
template<class T> Vec2<T> operator/(const Vec2<T>& v, const T& s) { return Vec2<T>(v) /= s; }




#endif