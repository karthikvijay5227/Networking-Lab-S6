## UDP Program

To run:Create two terminal windows and type following commands

Server:

    gcc udps.c -o s
    ./s 2050
 
Client:

    gcc udpc.c -o c
    ./c localhost 2050
