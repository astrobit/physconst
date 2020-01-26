# physconst
A LaTeX package that includes macros for a variety of fundamental constants.

# License
Copyright (C) 2020 by Brian W. Mulligan <bwmulligan@astronaos.com>
-----------------------------------------------------------

This file may be distributed and/or modified under the conditions of
the LaTeX Project Public License, either version 1.3c of this license
or (at your option) any later version. The latest version of this
license is in:

http://www.latex-project.org/lppl.txt

and version 1.3c or later is part of all distributions of LaTeX
version 2006/05/20 or later.

# Dependencies
- [`physunits` package](https://github.com/astrobit/physunits)

# Build Dependencies
- the `xastro-1` library (part of [xlibs][https://github.com/astrobit/xlibs])
- some LaTeX distribution with `xelatex`. The makefile assumes you have texlive.
- `pkg-config`
- GNU c++ compiler (`g++`) with at least c++11
- `hyperref` package for LaTeX
- `xcolor` package for LaTeX
- `mdframed` package for LaTeX
- `imakeidx` package for LaTeX
- GNU `make`

# Files
```
    README.md               This file.
    CHANGELOG.md            List of changes
    physconst.ins           The installer file
    makefile                GNU makefile to create and install the package
    generator/makefile      GNU makefile to create the generator
	generator/physconst.cpp c++ source code that will generate the .dtx for the
                            package
```

# Distributable Files
The following distributable files can be created as described below.
```
	physconst.sty           The actual package
    physconst.pdf           Usage documentation
    physconst.tar.bz2       Tarball containing package, documentation, and 
                            this README
    physconst.zip           Zip file containing package, documentation, and 
                            this README
```
To create a disribution on linux (or mac?)
- `make dist`

# Installation
For linux, run `make` to generate the package (.sty file) and documentation.
If you are using texlive (most modern linux distributions use texlive), you may 
then run `sudo make localinstall` to install the package to your latex 
distribution. If you are not using texlive, you will need to manually
copy the .sty file into either the folder where your .tex files reside that
require the package, or manually install the package in your latex distribution.

For mac, the instructions above for linux might work. Otherwise you're sort of 
on your own. Most likely your latex disrubution is somewhere in /usr/share.
You will need to figure out the name and where the package files are stored, 
then run `texhash` so that latex knows that they are there.

For windows, you're kind of on your own. Instructions that might help can be
found at [this post on StackExchange](https://tex.stackexchange.com/questions/369921/loading-packages-with-ins-and-dtx-files).


