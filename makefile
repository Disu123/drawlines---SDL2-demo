
drawlines: drawlines.c
	gcc -o drawlines drawlines.c `sdl2-config --cflags --libs`

.PHONY: clean
clean:
	rm -f drawlines
