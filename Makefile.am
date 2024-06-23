AM_CPPFLAGS = @SDL2_CFLAGS@ -I../inc -g -Wall -Wextra -Wpedantic

bin_PROGRAMS = gemusis

gemusis_SOURCES = 	src/main.c\
			src/renderloop.c\
			src/render/options.c\
			src/render/tv.c\
			src/render/nuklear.c\
			src/render/window.c\
			src/render/motodebug.c
		
gemusis_LDADD = @SDL2_LIBS@ -lm

EXTRA_DIST = 	fonts/ProggyClean.ttf\
		inc/gemusiscore.h\
		inc/nkwrapper.h\
		inc/options.h\
		inc/tv.h\
		inc/motodebug.h\
		inc/window.h\
		inc/nuklear_sdl_renderer.h\
		inc/nuklear.h

$(builddir)/ProggyClean.ttf:
	$(AM_V_at)$(MKDIR_P) $(builddir)
	$(AM_V_at)cp $(srcdir)/fonts/ProggyClean.ttf $(builddir)/ProggyClean.ttf
all-local: $(builddir)/ProggyClean.ttf
