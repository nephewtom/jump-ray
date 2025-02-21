del jump-ray.exe
:: g++ jump-ray.cpp -o jump-ray.exe -I raylib/src -L raylib/src -lraylib -lopengl32 -lgdi32 -lwinmm -Wall -Wextra -Wno-missing-field-initializers -g
gcc jump-ray.c -o jump-ray.exe -I raylib/src -L raylib/src -lraylib -lopengl32 -lgdi32 -lwinmm -Wall -Wextra -Wno-missing-field-initializers -g
.\jump-ray.exe
