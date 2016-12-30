divert(-1)
# -----------------------------------------------------------------------------
# CppAD: C++ Algorithmic Differentiation: Copyright (C) 2003-16 Bradley M. Bell
#
# CppAD is distributed under multiple licenses. This distribution is under
# the terms of the
#                     Eclipse Public License Version 1.0.
#
# A copy of this license is included in the COPYING file of this distribution.
# Please visit http://www.coin-or.org/CppAD/ for information on other licenses.
# -----------------------------------------------------------------------------

# some simple constants
define(ext_, m)
define(module_, m_cppad)
define(true_, true)
define(false_, false)
define(and_, &&)
define(end_, end)
define(c_, `%')

# generate_output_file_(example)
define(generate_output_file_,
`%' This file can be automatically generaeted using the following command
`%' m4 ../octave.m4 ../xam/$1.m4 > $1.ext_)


# begin_bool_fun_0_(name, return_variable)
define(begin_bool_fun_0_,
function $1 = $2()
	c_
	c_ load the cppad swig library
	module_
	c_
	c_ initialize return variable
	$1 = true_;)

# module_fun_1_(fun_name, argument)
define(module_fun_1_, module_.$1($2))

# var_(variable)
define(var_, $1)

# new_var_(variable, value)
define(new_var_, $1 = $2;)

# new_var_new_(variable, value)
define(new_var_new_, $1 = $2;)

# assign_(variable, value)
define(assign_, $1 = $2;)

# and_assign_(variable, value)
define(and_assign_, $1 = $1 and_ $2;)

# member_fun_1_(variable, member_fun, argument)
define(member_fun_1_, $1.$2($3))

# vec_set_(vector, index, value)
define(vec_set_, $1($2) = $3;)

# vec_get_(vector, index)
define(vec_get_, $1($2))

# begin_for_(variable, upper)
define(begin_for_, for $1 = [ 0 :($2-1) ])

# print_text_(text)
define(print_text_, printf('$1\n'))

# return_(expression)
define(return_, return;)

divert