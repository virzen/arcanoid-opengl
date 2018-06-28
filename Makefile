LIBS=-lGL -lglfw -lGLEW
FILES=main_file.cpp game.cpp errors.cpp models/model.cpp models/paddle/paddle.cpp models/brick/brick.cpp shader/shader.cpp
 
main_file: $(FILES)
	g++ -o main_file $(FILES)  $(LIBS)
