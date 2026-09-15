# Tictac
This game is from an 80s book on Apple ][e programming in basic.  It's focus was on AI, and this is a game that is supposed to be able to match the opponent by learning the best moves from playing over a period of time.

The environment used is Raylib's w64devkit so that debugging can be done with gdb.  VSCode was chosen because of its extensibility, and it is lighter weight than Visual Studio.

Functions have been separated out into the tictac.h file.

There are bugs, like the game not ending after the computer has finished its final move, whether it is a win or loss or draw.

There is more to do and clean up.  Maybe updating it with a different design pattern would help.
