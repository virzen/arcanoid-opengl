LIBS=-lGL -lglfw -lGLEW
FILES=main_file.cpp window.cpp errors.cpp

main_file: $(FILES)
	g++ -o main_file $(FILES)  $(LIBS)
