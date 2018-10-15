``b3-23`` is a console application simulating Elektronika B3-23
calculator. This application uses semi-interactive mode of
communication with the user. Each time it is ready to accept the user
entry, it prints the prompt. The user has to enter one or more
keystrokes as they would be pressed on the simulated calculator
keyboard and confirm them with the ENTER key. The application will
process them one-by-one, print interim and the final state of the
simulated machine and print the prompt awaiting for new commands.

This application supports also the pipelined mode of operation. It is
able to accept input from another process or a file. In this mode
application does not print greetings and the user prompt. The output
may be redirected to a file or pipelined to another process in the
chain. It may be used for automated tests.

Application consists of three modules: the target machine simulator
module, the host system specific module implementing the main loop,
and the adapter module in the middle. The simulator module may be
imported into another project as-is. For example, it may be used in a
dedicated hardware simulator. In such case a custom main loop module
shall be provided, and the adapter module as well.

Best regards, Alexander A. Strelets <streletsaa@gmail.com>
