mkdir -p web
emcc -o web/index.html jump-ray.cpp -I../raylib/src -L../raylib/build-web/raylib -lraylib -s USE_GLFW=3 -s USE_WEBGL2=1 -s FULL_ES3=1 -s ASSERTIONS=1 -Wall -Wextra -Wno-missing-field-initializers
