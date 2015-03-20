`Frak` is a small interpreter for the [brainf\*ck programming
language](http://en.wikipedia.org/wiki/Brainfuck), written in C++.
Its usefulness is debatable.

# Building `Frak`

`Frak` uses the excellent `CMake` build system. The following commands should be sufficient for
building `Frak`:

    $ mkdir build
    $ cd build
    $ cmake ../
    $ make

# Using `Frak`

`Frak` requires only a single command-line argument, viz. the brainf*ck code that is to be executed:

    $ ./frak Hello.f
    Hello World!

# Licence

`Frak` is released under the MIT licence.
