gcc main.c -o engine $(pkg-config --cflags --libs raylib) -lm && ./engine
