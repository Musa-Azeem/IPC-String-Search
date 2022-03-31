# CSCE311 Project 2

## Directory Structure
```
├── makefile
├── README.md
├── inc
│   ├── shared-memory-manager.h
│   ├── shared-memory-struct.h
│   ├── text-server.h
│   ├── text-client.h
│   ├── thread-args.h
│   └── ipc-names.h
└── src
    ├── main-srv.cc
    ├── main-cli.cc
    ├── text-server.cc
    └── text-client.cc
```

## The following objects are defined in this directory:

    SharedMemoryManager
    SharedMemoryStruct
    ThreadArgs
    TextClient
    TextServer

The `inc` folder contains all headers for the classes

The `src` folder contains all source code, as well as the main methods for server and client

## Objects

### SharedMemoryManager
- This class serves as the parent class for TextServer and TextClient, defining the attribtues shared by both.
- This class is defined in the files `inc/shared-memory-manager.h`
- This class is included in `text-server.h` and `text-client.h`

### TextServer
- This class defines a Shared Memory server
- Clients connect to this server, providing a file path
- The server then opens the file and writes its content to shared memory opened by the client
- This class is defined in the files `inc/text-server.h` and `src/text-server.cc`
- This class is included in `main-srv.cc`

### TextClient
- This class defines a Shared Memory client
- Clients send the server a file path for the server to open and write to shared memory, and then searches for a string in the file lines it reads from shared memory
- This class is defined in the files `inc/text-client.h` and `src/text-client.cc`
- This class is included in `main-cli.cc`

### SmStruct
- This struct is the structure used to hold data in shared memory
- It holds a file path, a file path size, a buffer, and a buffer size
- This struct is defined in the file `inc/shared-memory-struct.h`
- This struct is included in `shared-memory-manager.h`

### ThreadArgs
- This struct is used to pass the necessary arguments to the threaded search function of TextClient
- This struct is defined in the file `inc/thread-args.h`
- This struct is included in `src/text-client.h`

## Main Methods

### Server Main Method
- This main method creates and runs a Shared Memory server using the `TextServer` class
- It is defined in the file `src/main-srv.cc`

### Client Main Method
- This main method creates and runs a Shared Memory client using the `TextClient` class
- It is given a file path and search string as command line arguments
- It is defined in the file `src/main-cli`

## Other files
- `inc/ipcnames.h` defines a name for a shared memory and named semaphore locations that are included in `main-srv.cc` and `main-cli.cc`