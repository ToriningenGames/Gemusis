AM_CPPFLAGS = @SDL2_CFLAGS@ -I../Nuklear -I../inc

bin_PROGRAMS = gemusis

gemusis_SOURCES = 	src/main.c\
			src/renderloop.c\
			src/render/options.c
		
gemusis_LDADD = @SDL2_LIBS@ -lm

EXTRA_DIST = ProggyClean.ttf
add_fonts:
	$(AM_V_at)$(MKDIR_P) $(builddir)
	$(AM_V_at)cp $(srcdir)/fonts/ProggyClean.ttf $(builddir)/ProggyClean.ttf
all-local: add_fonts
