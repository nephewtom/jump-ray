rm -f jump-ray
gcc jump-ray.c -o jump-ray -I raylib/src -L raylib/src -lraylib -lm -Wextra -Wno-missing-field-initializers -g
./jump-ray
