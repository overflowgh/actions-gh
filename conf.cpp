hPif : src/main.o src/fann_utils.o src/hashes.o src/config.o # added the config part
    g++ src/main.o src/fann_utils.o src/hashes.o src/config.o -lfann -L/usr/local/lib -o hPif

config.o : src/config.cpp src/config.h
    g++ -c src/config.cpp
main.o: src/main.cpp src/config.h src/main.h src/hashes.h
    g++ -c src/main.cpp
