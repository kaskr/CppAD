# ifndef CppADRombergOneIncluded
# define CppADRombergOneIncluded

/* -----------------------------------------------------------------------
CppAD: C++ Algorithmic Differentiation: Copyright (C) 2003-06 Bradley M. Bell

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
------------------------------------------------------------------------ */
/*
$begin RombergOne$$
$spell
	bool
	const
	Cpp
	RombergOne
$$

$section One DimensionalRomberg Integration$$

$index integrate, Romberg$$
$index Romberg, Integrate$$

$head Syntax$$
$code # include <CppAD/RombergOne.h>$$
$pre
$$
$syntax%%r% = RombergOne(%F%, %a%, %b%, %n%, %e%)%$$


$head Description$$
Returns the Romberg integration estimate
$latex r$$ for a one dimensional integral
$latex \[
r = \int_a^b F(x) {\bf d} x + O \left[ (b - a) / 2^{n-1} \right]^{2(p+1)}
\] $$

$head Include$$
The file $code CppAD/RombergOne.h$$ is included by $code CppAD/CppAD.h$$
but it can also be included separately with out the rest of 
the $code CppAD$$ routines.

$head r$$
The return value $italic r$$ has prototype
$syntax%
	%Float% %r%
%$$ 
It is the estimate computed by $code RombergOne$$ for the integral above.

$head F$$
The object $italic F$$ can be of any type, but it must support 
the operation
$syntax%
	%F%(%x%)
%$$
The argument $italic x$$ to $italic F$$ has prototype
$syntax%
	const %Float% &%x%
%$$
The return value of $italic F$$ is a $italic Float$$ object
(see description of $xref/RombergOne/Float/Float/$$ below). 

$head a$$
The argument $italic a$$ has prototype
$syntax%
	const %Float% &%a%
%$$ 
It specifies the lower limit for the integration.

$head b$$
The argument $italic b$$ has prototype
$syntax%
	const %Float% &%b%
%$$ 
It specifies the upper limit for the integration.

$head n$$
The argument $italic n$$ has prototype
$syntax%
	size_t %n%
%$$ 
A total number of $latex 2^{n-1} + 1$$ evaluations of $syntax%%F%(%x%)%$$
are used to estimate the integral.

$head p$$
The argument $italic p$$ has prototype
$syntax%
	size_t %p%
%$$ 
It must be less than or equal $latex n$$
and determines the accuracy order in the approximation for the integral
that is returned by $code RombergOne$$. 
To be specific
$latex \[
r = \int_a^b F(x) {\bf d} x + O \left[ (b - a) / 2^{n-1} \right]^{2(p+1)}
\] $$


$head e$$
The argument $italic e$$ has prototype
$syntax%
	%Float% &%e%
%$$ 
The input value of $italic e$$ does not matter
and its output value is an approximation for the error in 
the integral estimates; i.e.,
$latex \[
	e \approx \left| r - \int_a^b F(x) {\bf d} x \right|
\] $$

$head Float$$
The type $italic Float$$ must satisfy the conditions
for a $xref/NumericType/$$ type.
The routine $xref/CheckNumericType/$$ will generate an error message
if this is not the case.
In addition, if $italic x$$ and $italic y$$ are $italic Float$$ objects,
$syntax%
	%x% < %y%
%$$     
returns the $code bool$$ value true if $italic x$$ is less than 
$italic y$$ and false otherwise.

$children%
	Example/RombergOne.cpp
%$$
$head Example$$
$comment%
	Example/RombergOne.cpp
%$$
The file
$xref/RombergOne.cpp/$$
contains an example and test a test of using this routine.
It returns true if it succeeds and false otherwise.

$head Source Code$$
The source code for this routine is in the file
$code CppAD/RombergOne.h$$.

$end
*/

# include <CppAD/CheckNumericType.h>
# include <CppAD/local/CppADError.h>
# include <CppAD/CppAD_vector.h>

namespace CppAD { // BEGIN CppAD namespace

template <class Fun, class Float>
Float RombergOne(
	Fun           &F , 
	const Float   &a , 
	const Float   &b , 
	size_t         n , 
	size_t         p ,
	Float         &e )
{
	size_t i, k;
	Float pow2, sum, x; 

	size_t ipow2 = 1;
	Float  zero  = Float(0);
	Float  two   = Float(2);

	// check specifications for a NumericType
	CheckNumericType<Float>();

	CppADUsageError(
		n >= 2,
		"RombergOne: n must be greater than or equal 2"
	);
	CppAD::vector<Float> r(n);

	//  set r[i] = trapazoidal rule with 2^i intervals in [a, b]
	r[0]  = ( F(a) + F(b) ) * (b - a) / two; 
	for(i = 1; i < n; i++)
	{	ipow2 *= 2;
		pow2   = Float(ipow2);
		sum    = zero;
		for(k = 1; k < ipow2; k += 2)
		{	// start = a + (b-a)/pow2, increment = 2*(b-a)/pow2
			x    = ( (pow2 - k) * a + k * b ) / pow2;
			sum  = sum + F(x);
		}
		// combine function evaluations in sum with those in T[i-1]
		r[i] = r[i-1] / two + sum * (b - a) / pow2;
	}

	// now compute the higher order estimates
	size_t ipow4    = 1;   // order of accuract for previous estimate
	Float pow4, pow4minus;
	for(i = 0; i < p; i++)
	{	// compute estimate accurate to O[ step^(2*(i+1)) ]
		// put resutls in r[n-1], r[n-2], ... , r[n-i+1]
		ipow4    *= 4;
		pow4      = Float(ipow4);
		pow4minus = Float(ipow4-1);
		for(k = n-1; k > i; k--)
			r[k] = ( pow4 * r[k] - r[k-1] ) / pow4minus;
	}

	// error estimate for r[n]
	e = r[n-1] - r[n-2];
	if( e < zero )
		e = - e;
	return r[n-1];
}

} // END CppAD namespace

# endif
