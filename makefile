# compiler
cc := g++

# source code
cli_src := src/maincli.cc src/text-client.cc src/shared-memory-manager.cc
srv_src := src/mainsrv.cc src/text-server.cc src/shared-memory-manager.cc

# final executables
cli_exe := text-client
srv-exe := text-server

# compile flags
flags := -std=c++17 
linker_libs = -L/lib -lpthread -lrt

# compile command
compile.cc := $(cc) $(flags) $< -o $@ $(linker_libs)

# make
$(cli_exe): $(cli_src)
	$(compile.cc)

$(srv_exe): $(srv_src)
	$(compile.cc)

clean:
	rm -r $(cli_exe) $(srv_exe)

# text-client: src/* inc/*
#	g++ -L/lib -std=c++17 src/maincli.cc src/shared-memory-manager.cc src/text-client.cc -o text-client -lpthread -lrt
# text-server: src/* inc/*
#	g++ -L/lib -std=c++17 src/mainsrv.cc src/shared-memory-manager.cc src/text-server.cc -o text-server -lpthread -lrt
# all: text-client text-server    
