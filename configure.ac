AC_INIT([Graph base reverse mode Automatic Differentiation (GrAD)], [0.1], cmoe@aqua.dtu.dk)
AC_COPYRIGHT([Copyright (C) 2016 Christoffer Moesgaard Albertsen])


AC_MSG_CHECKING([Cheking for C++ compiler])
AC_PROG_CXX
AC_SUBST(PROG_CXX,${CXX})

AS_IF([test [ -n "${STD}" ]],
	    [
	    AC_SUBST(PROG_STD,${STD})
	    AC_MSG_NOTICE([Using C++ version ${STD}])
	    ],
	    [
	    AC_SUBST(PROG_STD,"c++03")
	    AC_MSG_NOTICE([Using default C++ version c++03])
	    ])


AC_PREFIX_DEFAULT("/usr/local")
if test "$prefix" = "NONE"; then
   prefix=$ac_default_prefix
fi
AC_MSG_NOTICE([Using include directory ${prefix}/include])
AC_SUBST(includedir,${prefix}/include)


AS_IF([test [ -n "${EIGEN}" ]],
	    [
	    AC_SUBST(EIGEN_DIR,${EIGEN})
	    AC_MSG_NOTICE([Linking examples and comparison to ${EIGEN}/Eigen/Dense])
	    ],
	    [
	    AC_MSG_WARN([Eigen is needed for comparison and examples. If Eigen is not in PATH, please specify the directory by EIGEN=/path/to/])
	    ])

AS_IF([test [ -n "${CPPAD}" ]],
	    [
	    AC_SUBST(CPPAD_DIR,${CPPAD})
	    AC_MSG_NOTICE([Linking examples and comparison to ${CPPAD}/cppad/cppad.h])
	    ],
	    [
	    AC_MSG_WARN([CppAD is needed for compare and examples. If CppAD is not in PATH, please specify the directory by CPPAD=/path/to/])
	    ])



AC_CONFIG_FILES(Makefile)
AC_CONFIG_FILES(compare/Makefile)
AC_CONFIG_FILES(test/Makefile)
AC_CONFIG_FILES(examples/Makefile)
AC_OUTPUT
