EXECUTABLE_NAME = WhereImpostor
CHECKS = -Wall -pedantic-errors
LIBS = -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system
NO_CONSOLE = -Wl,-subsystem,windows

default:
	windres resources.rc resources.o
	g++ -std=c++17 -O3 -c ../src/*.cpp -I ../include $(CHECKS)
	g++ ./*.o -o $(EXECUTABLE_NAME) $(LIBS) $(NO_CONSOLE)
	del *.o
# g++ -std=c++17 -O3 ../src/*.cpp -o $(EXECUTABLE_NAME) -I ../include $(CHECKS) $(LIBS) $(NO_CONSOLE)
