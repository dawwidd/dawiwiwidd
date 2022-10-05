LIBS=-lGL -lglfw -lGLEW
HEADERS=allmodels.h  constants.h  cube.h  lodepng.h  model.h  shaderprogram.h  sphere.h  teapot.h  torus.h
FILES=cube.cpp  lodepng.cpp  main_file.cpp  model.cpp  shaderprogram.cpp  sphere.cpp  teapot.cpp  torus.cpp

main_file: $(FILES) $(HEADERS)
	g++ -o main_file $(FILES)  $(LIBS) -I.
