del main.exe
gcc -c main.c -o main.o -O1 -Wall -std=c99 -Wno-missing-braces -I raylib/ -L raylib/ -lraylib -lopengl32 -lgdi32 -lwinmm
gcc -o main.exe main.o -O1 -Wall -std=c99 -Wno-missing-braces -I raylib/ -L raylib/ -lraylib -lopengl32 -lgdi32 -lwinmm -Wl,--subsystem,windows
main.exe