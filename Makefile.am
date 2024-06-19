AM_CPPFLAGS = @SDL2_CFLAGS@ -I../Nuklear -I../inc -g -Wall -Wextra -Wpedantic

bin_PROGRAMS = gemusis

gemusis_SOURCES = 	src/main.c\
			src/renderloop.c\
			src/render/options.c\
			src/render/tv.c\
			src/render/nuklear.c\
			src/render/window.c
		
gemusis_LDADD = @SDL2_LIBS@ -lm

EXTRA_DIST = ProggyClean.ttf
add_fonts:
	$(AM_V_at)$(MKDIR_P) $(builddir)
	$(AM_V_at)cp $(srcdir)/fonts/ProggyClean.ttf $(builddir)/ProggyClean.ttf
all-local: add_fonts
