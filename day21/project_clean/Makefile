CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

OBJS = main.o ecu_communication.o

ecu_simulator: $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o ecu_simulator

main.o: main.cpp ecu_communication.h
	$(CXX) $(CXXFLAGS) -c main.cpp

ecu_communication.o: ecu_communication.cpp ecu_communication.h
	$(CXX) $(CXXFLAGS) -c ecu_communication.cpp

clean:
	rm -f *.o ecu_simulator
