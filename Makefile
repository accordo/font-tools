# simple Makefile~

dump1: dump1.c
	gcc $< -L/usr/lib/x86_64-linux-gnu -lfreetype -lz -lpng12 -I/usr/include/freetype2 -lm -o $@


.PHONY: clean
clean:
	rm -f dump1 a.out

