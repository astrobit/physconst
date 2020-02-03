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
- [`physunits` package](https://github.com/astrobit/physunits) also available 
at [CTAN](https://ctan.org)

# Build Dependencies
- the `xastro-1` library (part of [xlibs][https://github.com/astrobit/xlibs])
- some LaTeX distribution with `xelatex`.
- `pkg-config` (if using linux or mac)
- A c++ compiler (`g++`) with at least c++11
- `hyperref` package for LaTeX
- `xcolor` package for LaTeX
- `mdframed` package for LaTeX
- `imakeidx` package for LaTeX
- GNU `make` (if using linux or mac)

# Files
```
    README.md               This file.
    README.dist.md          A readme better suited for the distribution.
    CHANGELOG.md            List of changes
    physconst.ins           The installer file
    makefile                GNU makefile to create and install the package
    generator/makefile      GNU makefile to create the generator
    generator/physconst.cpp c++ source code that will generate the .dtx for the
                            package
    makefile.dist           GNU makefile for packaging with the distribution
```

# Distributable Files
The following distributable files can be created as described below.
```
    physconst.tar.gz        Tarball containing package, documentation, and 
                            this README
    physconst.zip           Zip file containing package, documentation, and 
                            this README
```
The distributables contain the following:
```
    README.md               A readme with instructions for building and 
                            installation
    makefile                A makefile to simplify building and installation on 
                            linux/mac
    physconst.ins           The installer file
    physconst.dtx           The package code and documentation
    physconst.pdf           Usage documentation
```

# Building the package
## Linux / mac
1. `make` to generate the package
## Windows or if make doesn't work

Instructions that might help can be for windows can be found at 
[this post on StackExchange](https://tex.stackexchange.com/questions/369921/loading-packages-with-ins-and-dtx-files).
1. Compile the `.cpp` file into an executable. For this you will need a c++ 
compiler such as gnu-c++ or Microsoft Visual C++. Note the dependency on 
`xastro-1`.
1. Generate the `.dtx` file using the executable you just created.
1. Run `latex` on physunits.ins
1. Run `latex` of some form (e.g. `xelatex`) on `physunits.dtx`
1. Run `makeindex -s gind.ist -o physunits.ind physunits.idx`
1. Run `makeindex -s gglo.ist -o $(pkgname).gls $(pkgname).glo`
1. Run `latex` of some form (e.g. `xelatex`) on `physunits.dtx` to create the
index
1. Run `latex` of some form (e.g. `xelatex`) on `physunits.dtx` to get the right
links and labels.

# Installation
## Linux / mac
### For a single project
1. Build the package as described above.
1. Copy the `physunits.sty` into your project where your `.tex` files are 
located.
### for all users and projects
1. Build the package as described above.
1. `make localinstall` to generate the package.


## Windows or if the above doesn't work for linux/max
1. Build the package as described above.
1. Instructions that might help can be for windows can be found at 
[this post on StackExchange](https://tex.stackexchange.com/questions/369921/loading-packages-with-ins-and-dtx-files).
1. Figure out where your LaTeX local packages are installed.
1. Create a directory named `physunits` in that location.
1. Copy `physunits.sty` into the new directory.
1. Figure out where your LaTeX local package documentation is installed.
1. Create a directory named `physunits` in that location.
1. Copy `physunits.pdf` into the new directory.
1. Run `texhash` or the equivalent to let latex know the package is there.

# Uninstallation

## Linux / mac
1. `sudo make localuninstall`

## Windows or if the above doesn't work for linux/max
1. Figure out where your LaTeX local packages are installed.
1. Delete the directory named `physunits` in that location.
1. Figure out where your LaTeX local package documentation is installed.
1. Delete the directory named `physunits` in that location.
1. Run `texhash` or the equivalent to let LaTeX know the package is gone.

# Creating distributions

## Linux / mac
To create a disribution on linux (or mac?)
1. Build the package as described above.
1. `make dist` to generate the distributable tarball and zip file

## Windows or if make doesn't work
1. Build the package as described above.
1. Create a directory named `physunits`
1. Copy `physunits.ins`, `physunits.dtx`, `physunits.pdf`, and `CHANGELOG.md` 
into the directory
1. Copy `README.dist.md` into the directory as `README.md`
1. Copy `makefile.dist` into the directory as `makefile`
1. Create a `.zip` file from the directory.


