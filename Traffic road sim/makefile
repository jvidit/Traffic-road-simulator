CC=g++
CFLAGS=-g -Wall -Wno-deprecated
RM=/bin/rm -f

all:	task2
Road.o: Road.h Road.cpp
	${CC} ${CFLAGS} -c Road.cpp
Vehicle.o: Vehicle.h Vehicle.cpp
	${CC} ${CFLAGS} -c Vehicle.cpp
Specifications.o: Specifications.h Specifications.cpp
	${CC} ${CFLAGS} -c Specifications.cpp
TrafficLight.o: TrafficLight.h TrafficLight.cpp
	${CC} ${CFLAGS} -c TrafficLight.cpp
VehiclePosition.o: VehiclePosition.h VehiclePosition.cpp
	${CC} ${CFLAGS} -c VehiclePosition.cpp
AddVehicleEvent.o: AddVehicleEvent.h AddVehicleEvent.cpp
	${CC} ${CFLAGS} -c AddVehicleEvent.cpp
Constants.o: Constants.h Constants.cpp
	${CC} ${CFLAGS} -c Constants.cpp
main.o: main.cpp
	${CC} ${CFLAGS} -c main.cpp
task2:main.o Road.o Vehicle.o Specifications.o TrafficLight.o VehiclePosition.o AddVehicleEvent.o Constants.o

	${CC} ${CFLAGS} -o task2 main.o Road.o Vehicle.o Specifications.o TrafficLight.o VehiclePosition.o AddVehicleEvent.o Constants.o -framework GLUT -framework OpenGL -framework Cocoa
clean:
	${RM} *.o task2