# compiler
cc := g++

# source code
cli_src := src/main-cli.cc src/text-client.cc src/shared-memory-manager.cc
srv_src := src/main-srv.cc src/text-server.cc src/shared-memory-manager.cc

# final executables
cli_exe := text-client
srv_exe := text-server

# compile flags
flags := -std=c++17 
linker_libs = -L/lib -lpthread -lrt

# compile command
compile.cc = $(cc) $(flags) $^ -o $@ $(linker_libs)

# make
$(cli_exe): $(cli_src)
	$(compile.cc)

$(srv_exe): $(srv_src)
	$(compile.cc)

clean:
	rm -r $(cli_exe) $(srv_exe)