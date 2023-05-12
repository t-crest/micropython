Patmos port
=
First mpy-cross must be built to be able to generate bytecode from .py files. Navigate to /mpy-cross and run:
`make`
Then in the /ports/patmos folder run:
`make mpy`
To compile all .py to .mpy files in the /py folder.

Now the Patmos port of micropython can be built, to do so simply run:
`make`
To build it with a python REPL instead of bytecode, open `mpconfigport.h` and set `MICROPY_HELPER_REPL` to `1` and run:
`make FROZEN=0`

In any case to run the built Patmos file run:
`make patmosRun`

