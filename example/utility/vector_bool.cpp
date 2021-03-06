/* --------------------------------------------------------------------------
CppAD: C++ Algorithmic Differentiation: Copyright (C) 2003-17 Bradley M. Bell

CppAD is distributed under multiple licenses. This distribution is under
the terms of the
                    Eclipse Public License Version 1.0.

A copy of this license is included in the COPYING file of this distribution.
Please visit http://www.coin-or.org/CppAD/ for information on other licenses.
-------------------------------------------------------------------------- */

/*
$begin vector_bool.cpp$$
$spell
	Cpp
	bool
$$

$section CppAD::vectorBool Class: Example and Test$$
$mindex bool vectorBool CppAD$$


$code
$srcfile%example/utility/vector_bool.cpp%0%// BEGIN C++%// END C++%1%$$
$$

$end
*/
// BEGIN C++

# include <cppad/utility/vector.hpp>
# include <cppad/utility/check_simple_vector.hpp>
# include <sstream> // sstream and string are used to test output operation
# include <string>

bool vectorBool(void)
{	bool ok = true;
	using CppAD::vectorBool;

	vectorBool x;          // default constructor
	ok &= (x.size() == 0);

	x.resize(2);             // resize and set element assignment to bool
	ok &= (x.size() == 2);
	x[0] = false;
	x[1] = true;

	vectorBool y(2);       // sizing constructor
	ok &= (y.size() == 2);

	const vectorBool z(x); // copy constructor and const element access
	ok &= (z.size() == 2);
	ok &= ( (z[0] == false) && (z[1] == true) );

	x[0] = true;           // modify, assignment changes x
	ok &= (x[0] == true);

	// resize x to zero and check that vector assignment works for both
	// size zero and mathching sizes
	x.resize(0);
	ok &= (x.size() == 0);
	ok &= (y.size() == z.size());
	//
	x = y = z;
	ok &= ( (x[0] == false) && (x[1] == true) );
	ok &= ( (y[0] == false) && (y[1] == true) );
	ok &= ( (z[0] == false) && (z[1] == true) );

	// test of push_vector
	y.push_vector(z);
	ok &= y.size() == 4;
	ok &= ( (y[0] == false) && (y[1] == true) );
	ok &= ( (y[2] == false) && (y[3] == true) );

	y[1] = false;           // element assignment to another element
	x[0] = y[1];
	ok &= (x[0] == false);

	// test of output
	std::string        correct= "01";
	std::string        str;
	std::ostringstream buf;
	buf << z;
	str = buf.str();
	ok &= (str == correct);

	// test resize(0), capacity, and clear
	size_t i = x.capacity();
	ok      &= i > 0;
	x.resize(0);
	ok      &= i == x.capacity();
	x.clear();
	ok      &= 0 == x.capacity();

	// test of push_back element
	for(i = 0; i < 100; i++)
		x.push_back( (i % 3) != 0 );
	ok &= (x.size() == 100);
	for(i = 0; i < 100; i++)
		ok &= ( x[i] == ((i % 3) != 0) );

	// is that boolvector is
	// a simple vector class with elements of type bool
	CppAD::CheckSimpleVector< bool, vectorBool >();

	return ok;
}

// END C++
