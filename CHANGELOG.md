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
- Update README to have clearer build, distribute, install, and uninstall instructions.
- Distribute with .dtx instead of .sty
- Reordered build, install, distribute, and uninstall sections of the README
- Pulled build up one level of headings in the README
- fix some typos in README


