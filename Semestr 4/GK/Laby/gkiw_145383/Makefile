LIBS=-lGL -lglfw -lGLEW -lassimp
HEADERS=camera.h lodepng.h  mesh.h shaderprogram.h
FILES=camera.cpp lodepng.cpp  main.cpp shaderprogram.cpp
main_file: $(FILES) $(HEADERS)
	g++ -o main_file $(FILES)  $(LIBS) -I.
