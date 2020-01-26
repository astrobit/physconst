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
- Modified the .cpp so that every \DeclareRobustCommand starts a new line right away
- Added a newline in the middle of the title declaration (in .cpp)
- Added a newline in the middle of the \DoNotIndex declaration (in .cpp)
- Added dependency on imakeidx and changed the index to 2 column.
- fixed makefile install options to correctly find TEXMF path
### Removed
- Removed unnecessary packages (tikz, float) from the code for the documentation


