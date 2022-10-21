# minitalk
A chat between a server and a client.
## Allowed functions
- write
- ft_printf and any equivalent YOU coded
- signal
- sigemptyset
- sigaddset
- sigaction
- kill
- getpid
- malloc
- free
- pause
- sleep
- usleep
- exit
## How it is implemented
The server starts by writing it PID on the standard output; as soon as it is displayed, the user can start the client with the PID of the server.
Both processes change information via SIGUSR1 AND SIGUSR2, for the client sending to the server SIGUSR1 means sending bit 0 whereas SIGUSR2 means 1. The server works in an infinite loop where it can be suspended until a signal is arised. The client will send each caracter by sending each of their bits and waiting for the server to acknowledge via SIGUSR1 that it was received and by SIGUSR2 as the end of the connection. For this synchronization the client has a global variable which is updated as the acknolewdge is received, unlocking the client to send another signal.
## Unicode charcters 🅰
The characters can be sent in any kind of format as they are just considered to be bytes of memory.

