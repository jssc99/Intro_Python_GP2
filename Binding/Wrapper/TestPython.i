
%module(threads="1") TestPython

%{
	#include "../source/include/Core/Python/TestPython.h"
%}


%include "std_string.i"

%include "../source/include/Core/Python/TestPython.h"
%feature("nothreadallow");
