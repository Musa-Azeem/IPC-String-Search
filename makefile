text-client: src/* inc/*
	g++ -L/lib -std=c++17 src/maincli.cc src/shared-memory-manager.cc src/text-client.cc -o text-client -lpthread -lrt
text-server: src/* inc/*
	g++ -L/lib -std=c++17 src/mainsrv.cc src/shared-memory-manager.cc src/text-server.cc -o text-server -lpthread -lrt
all: text-client text-server    
