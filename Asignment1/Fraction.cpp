/*
* @author  <Alejandro Toledano>
* @version <1.0>
*

* @section Academic Integrity
*  I certify that this work is solely my own and complies with
*  NBCC Academic Integrity Policy (policy 1111)
*
*
* @section DESCRIPTION
*  < ====================================================================== >
*
*
* @section LICENSE
*  <any necessary attributions>
*
*  Copyright 2019
*  Permission to use, copy, modify, and/or distribute this software for
*  any purpose with or without fee is hereby granted, provided that the
*  above copyright notice and this permission notice appear in all copies.
*
*  THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
*  WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
*  MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
*  ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
*  WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
*  ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
*  OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*
*/

#include "pch.h"
#include "Fraction.h"
#include <algorithm>
#include <numeric>

//Constructors overloading

Fraction::Fraction() :_numerator(1), _denominator(1) //Default constructor
{
}

Fraction::Fraction(int numerator) :_numerator(numerator), _denominator(1)	//1 arg constructor, denominator=1, simplifies
{
	int g = std::gcd(_numerator, _denominator);
	_numerator /= g;
	_denominator /= g;
	if (_denominator < 0) {
		_denominator *= -1;
		_numerator *= -1;
	}
}

Fraction::Fraction(int numerator, int denominator) :_numerator(numerator), _denominator(denominator) //2 arg constructor, simplifies
{
	int g = std::gcd(_numerator, _denominator);
	_numerator /= g;
	_denominator /= g;
	if (_denominator < 0) {
		_denominator *= -1;
		_numerator *= -1;
	}
	if (denominator == 0) {// exception if denominator is 0
		throw std::out_of_range("INVALID ENTRY");
	}
}

//Logical operators overloading inside class

bool Fraction::operator==(const Fraction& rhs) const
{
	return (this->_numerator * rhs._denominator == this->_denominator * rhs._numerator);
}

bool Fraction::operator!=(const Fraction& rhs) const
{
	return !(this->_numerator * rhs._denominator == this->_denominator * rhs._numerator);
}

bool Fraction::operator>(const Fraction& rhs) const
{
	return (this->_numerator * rhs._denominator > this->_denominator* rhs._numerator);
}

bool Fraction::operator>=(const Fraction& rhs) const
{
	return (this->_numerator * rhs._denominator >= this->_denominator * rhs._numerator);
}

bool Fraction::operator<(const Fraction& rhs) const
{
	return (this->_numerator * rhs._denominator < this->_denominator * rhs._numerator);
}

bool Fraction::operator<=(const Fraction& rhs) const
{
	return (this->_numerator * rhs._denominator <= this->_denominator * rhs._numerator);
}

//Arithmetic operators overloading inside class

Fraction& Fraction::operator+(Fraction& rhs)
{
	_numerator = _numerator * rhs._denominator + rhs._numerator * _denominator;
	_denominator = _denominator * rhs._denominator;
	Fraction* tmp = this;
	return *tmp;
}

Fraction& Fraction::operator-(Fraction& rhs)
{
	_numerator = _numerator * rhs._denominator - rhs._numerator * _denominator;
	_denominator = _denominator * rhs._denominator;
	Fraction* tmp = this;
	return *tmp;
}

Fraction& Fraction::operator*(Fraction& rhs)
{
	this->_numerator = _numerator * rhs._numerator;
	this->_denominator = _denominator * rhs._denominator;
	Fraction* tmp = this;
	return *tmp;
}

Fraction& Fraction::operator/(Fraction& rhs)
{
	Fraction tmp(rhs);
	rhs._numerator = rhs._denominator;
	rhs._denominator = tmp._numerator;
	this->_numerator = this->_numerator * rhs._numerator;
	this->_denominator = this->_denominator * rhs._denominator;
	return *this;
}

Fraction& Fraction::operator+=(Fraction& rhs)
{
	_numerator = _numerator * rhs._denominator + rhs._numerator * _denominator;
	_denominator = _denominator * rhs._denominator;
	Fraction* tmp = this;
	return *tmp;
}

Fraction& Fraction::operator-=(Fraction& rhs)
{
	_numerator = _numerator * rhs._denominator - rhs._numerator * _denominator;
	_denominator = _denominator * rhs._denominator;
	Fraction* tmp = this;
	return *tmp;
}

Fraction& Fraction::operator*=(Fraction& rhs)
{
	this->_numerator *= rhs._numerator;
	this->_denominator *= rhs._denominator;
	Fraction* tmp = this;
	return *tmp;
}

Fraction& Fraction::operator/=(Fraction& rhs)
{
	Fraction tmp(rhs._denominator, rhs._numerator);
	this->_numerator *= tmp._numerator;
	this->_denominator *= tmp._denominator;
	if (this->_numerator < 0 && this->_denominator < 0) {
		this->_numerator *= -1;
		this->_denominator *= -1;
	}
	return *this;
}

//Friend stream manipulation functions

std::ostream& operator<<(std::ostream& os, const Fraction& fra)
{
	Fraction tmp(fra);
	os << tmp._numerator << "/" << tmp._denominator;
	return os;
}

std::istream& operator>>(std::istream& is, Fraction& fra)
{
	char D;
	is >> fra._numerator >> D >> fra._denominator;
	return is;
}

//Friend Logical operators overloading outside class

bool operator>(int x, Fraction& rhs)
{
	return (x > rhs._numerator / rhs._denominator);
}

bool operator<(int x, Fraction& rhs)
{
	return (x < rhs._numerator / rhs._denominator);
}

//Friend Arithmetic operators overloading outside class

Fraction operator+(int x, Fraction& rhs)
{
	Fraction tmp{ rhs };
	tmp._numerator = x * tmp._denominator + tmp._numerator;
	return rhs;
}

Fraction operator+=(int x, Fraction& rhs)
{
	rhs._numerator = x * rhs._denominator + rhs._numerator;
	return rhs;
}

Fraction operator+=(Fraction& rhs, int x)
{
	rhs._numerator += x * rhs._denominator;
	return rhs;
}

Fraction operator+(Fraction& rhs, int x)
{
	rhs._numerator += x * rhs._denominator;
	return rhs;
}

Fraction operator-(int x, Fraction& rhs)
{
	Fraction tmp(x);
	tmp._numerator = (rhs._denominator * tmp._numerator) - rhs._numerator;
	tmp._denominator *= rhs._denominator;
	return tmp;
}

Fraction operator-(Fraction& rhs, int x)
{
	rhs._numerator = (rhs._numerator - (x * rhs._denominator));
	return rhs;

}

Fraction operator-=(int x, Fraction& rhs)
{
	Fraction tmp(x);
	tmp._numerator = (rhs._denominator * tmp._numerator) - rhs._numerator;
	tmp._denominator *= rhs._denominator;
	return tmp;
}

Fraction operator-=(Fraction& rhs, int x)
{
	rhs._numerator = (rhs._numerator - (x * rhs._denominator));
	return rhs;
}

Fraction operator*(int x, Fraction& rhs)
{
	Fraction tmp(x);
	tmp._denominator = tmp._denominator * rhs._denominator;
	tmp._numerator = tmp._numerator * rhs._numerator;
	return tmp;
}

Fraction operator*(Fraction& rhs, int x)
{
	Fraction tmp(x);
	tmp._denominator = tmp._denominator * rhs._denominator;
	tmp._numerator = tmp._numerator * rhs._numerator;
	return tmp;
}

Fraction operator*=(int x, Fraction& rhs)
{
	rhs._numerator *= x;
	rhs._denominator = 1;
	return rhs;
}

Fraction operator*=(Fraction& rhs, int x)
{
	rhs._numerator *= x;
	rhs._denominator *= 1;
	return rhs;
}

Fraction operator/(int x, Fraction& rhs)
{
	Fraction tmp;
	tmp._denominator = 1 * rhs._numerator;
	tmp._numerator = x * rhs._denominator;
	return tmp;
}

Fraction operator/(Fraction& rhs, int x)
{
	Fraction tmp(x);
	tmp._numerator = tmp._denominator * rhs._numerator;
	tmp._denominator = x * rhs._denominator;
	return tmp;

}

Fraction operator/=(int x, Fraction& rhs)
{
	rhs._numerator = rhs._numerator * 1;
	rhs._denominator = x * rhs._denominator;
	return rhs;
}

Fraction operator/=(Fraction& rhs, int x)
{
	rhs._numerator = rhs._numerator * 1;
	rhs._denominator = x * rhs._denominator;
	return rhs;
}