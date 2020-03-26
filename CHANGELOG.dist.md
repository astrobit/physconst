# Changes
## [1.0.0] - 2020/01/25
- Initial version
## [1.0.1] - 2020/01/25
### Added
- A changelog
- A readme
- Code for changelog into physconst.cpp
- `make dist` to create distributable tarball and zip
- Documentation for options
- line in .ins to force generation of the .sty
- nicer index entries (and some associated code in .cpp to generate them)
- added localuninstall and distuninstall targets to the makefile
### Changed
- Modified the makefile to split up generation of the .sty, .dtx, and .pdf
- Modified the .cpp so that every \DeclareRobustCommand starts a new line right 
away
- Added a newline in the middle of the title declaration (in .cpp)
- Added a newline in the middle of the \DoNotIndex declaration (in .cpp)
- Added dependency on imakeidx and changed the index to 2 column.
- fixed makefile install options to correctly find TEXMF path
### Removed
- Removed unnecessary packages (tikz, float) from the code for the documentation
## [1.0.2] - 2020/01/25
### Changed
- Switch compression of tarball to gzip to match requirement for CTAN
## [1.0.2.a] - 2020/01/25
- Same as 1.0.2
## [1.0.2.b] - 2020/01/25
### Added
- Add changelog to distribution
- Add disribution specific readme
- Add disribution specific makefile
### Changed
- Update README to have clearer build, distribute, install, and uninstall 
instructions.
- Distribute with .dtx instead of .sty
- Reordered build, install, distribute, and uninstall sections of the README
- Pulled build up one level of headings in the README
- fix some typos in README
## [1.1.0] - 2020/02/03
### Added
- macro for Earth's mass
- macro for Jupiter's mass
- macro for Earth's radius
- macro for Jupiter's radius
- distribution specific change log
- Numeric variant of each constant for use with e.g. tikz
### Changes
- Colomb constant in SI units had an incorrect magnitude; fixed to 10^9 instead 
of 10^14
- Vacuum permeability was incorrectly a duplicate of the permittivity.
Premeability is now the correct value.
- Mass of particles in eV was being computed incorrectly. Fixed values.
- Order of magnitude of Newton's Gravity, Boltzmann, Planck, and 
Stefan-Boltzmann constants were incorrect.
- Acceleration due to gravity on Earth was accidentally a copy of G instead of g
- Acceleration due to gravity on Earth had the wrong units
- Corrected formatting of README file.
- Fixed sections of macros - the individual macros were unintentionally
subsections of the Naming Conversion
## [1.1.1] - 2020/03/26
### Added
- Acknowledgements section of documentation
- Bug reporting section of documentation
- Prerequisites / Dependencies section of documentation
### Changes
- The shortconst option was having the opposite of the intended effect. When
not specified, constants were appearing with reduced precision, and when 
specified, constants had full precision. Fixed operation to be as intended.
- Corrected changelog (in the .pdf) and overall version of the file to 
correctly be 1.1.x instead of 1.0.2
- Upgraded macros subsection to section (this was a prior bug).
- Corrected the description of the source of astronomical constants within the
introduction.

