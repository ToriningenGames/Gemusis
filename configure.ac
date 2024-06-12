AC_INIT([gemusis], [0], [toriningengames@gmail.com], [https://www.toriningen.com/])
AM_INIT_AUTOMAKE([foreign subdir-objects])

AC_PROG_CC
PKG_CHECK_MODULES([SDL2], [sdl2 >= 2.0.0],
        [AC_DEFINE([HAVE_SDL2], [1], [goodsdl2text])],
        [AC_MSG_ERROR([sdl2text])])

AC_SUBST([SDL_CFLAGS])
AC_SUBST([SDL_LIBS])

AC_OUTPUT([Makefile])
