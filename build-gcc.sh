rm -f jump-ray
gcc -std=c99 jump-ray.c -o jump-ray -I raylib/src -L raylib/src -lraylib -framework OpenGL -framework CoreFoundation -framework CoreGraphics -framework IOKit -framework AppKit -Wall -Wextra -Wno-missing-field-initializers -g

./jump-ray
