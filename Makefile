LIBS=-lGL -lglfw -lGLEW
FILES=cube.cpp  detailed_cube.cpp  main_file.cpp  model.cpp  sphere.cpp  teapot.cpp  torus.cpp

main_file: $(FILES)
	g++ -o main_file $(FILES)  $(LIBS)
