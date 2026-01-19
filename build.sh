gcc main.c lib/draw.c -o engine $(pkg-config --cflags --libs raylib) -lm && ./engine
