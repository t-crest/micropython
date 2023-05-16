Patmos port
=
First mpy-cross must be built to be able to generate bytecode from .py files. Navigate to /mpy-cross and run:
`make`
Then in the /ports/patmos folder run:
`make mpy`
To compile all .py to .mpy files in the /py folder.

Before building the Patmos port of micropython look in `mpconfigport.h` and set the options to what is preferred:  
To build it with a python REPL, set `MICROPY_HELPER_REPL` to `1`  
To build it with support for exception handling on FPGA, set `FPGA` to `1`

When the options are set run:
`make`

In any case to run the built Patmos file run:
`make run`  
Or if it is to be run on a FPGA type:
`make fpga`
