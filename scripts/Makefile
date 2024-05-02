
FLAGS:=-std=c++11 -Iinclude

build:
	g++ src/confswap.cpp include/gpiocb1.cpp $(FLAGS) -o bin/confswap
	g++ src/minifab_daemon.cpp include/gpiocb1.cpp $(FLAGS) -o bin/minifab_daemon
	g++ src/gpiocb1exp.cpp include/gpiocb1.cpp $(FLAGS) -o bin/gpiocb1
