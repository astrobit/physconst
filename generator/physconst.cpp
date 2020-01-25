#include <xastro.h>
#include <string>
#include <cstdio>
#include <vector>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <cmath>
#include <map>

class Constant
{
public:
	enum class units {uNone,uSI,uCGS,uEV};
	enum class precision {pNone,pShort,pFull};

	double 		m_fValue;
	units 		m_eUnits;
	precision 	m_ePrecision;
	size_t		m_nPrint_Precision;
	std::string m_sDescription;
	std::string m_sUnits;
	std::string m_sSource;

	std::string m_sMacroname;
	std::vector<std::string> m_vDescription;

	Constant(double i_fValue, units i_eUnits, precision i_ePrecision, size_t i_nPrint_Precision, const char * i_psName, const char * i_psDescription, const char * i_psSource, const char * i_pUnits)
	{
		std::ostringstream sMacroname;

		sMacroname << "k";
		switch (i_eUnits)
		{
		case units::uSI:
			sMacroname << "@SI";
			break;
		case units::uCGS:
			sMacroname << "@cgs";
			break;
		case units::uEV:
			sMacroname << "@eV";
			break;
		}
		switch (i_ePrecision)
		{
		case precision::pShort:
			sMacroname << "@short";
			break;
		case precision::pFull:
			sMacroname << "@full";
			break;
		}
		sMacroname << "@" << i_psName;
		m_sMacroname = sMacroname.str();

		m_fValue = i_fValue;
		m_eUnits = i_eUnits;
		m_ePrecision = i_ePrecision;
		m_nPrint_Precision = i_nPrint_Precision;
		m_sDescription = i_psDescription;
		m_sUnits = i_pUnits;
		m_sSource = i_psSource;

		const char * psCursorLast;
		const char * psCursor = m_sDescription.c_str();
		//bypass any leading whitespace
		while (psCursor != nullptr && psCursor[0] != 0 && (psCursor[0] == ' ' || psCursor[0] == '\t'))
		{
			psCursor++;
		}
		psCursorLast = psCursor;

		while (psCursor != nullptr && psCursor[0] != 0)
		{
			while (psCursor != nullptr && psCursor[0] != 0 && psCursor[0] != ' ' && psCursor[0] != '\t')
			{
				psCursor++;
			}
			std::string sCurr;
			while (psCursorLast != psCursor)
			{
				sCurr += psCursorLast[0];
				psCursorLast++;
			}
			m_vDescription.push_back(sCurr);
			while (psCursor != nullptr && psCursor[0] != 0 && (psCursor[0] == ' ' || psCursor[0] == '\t'))
			{
				psCursor++;
			}
			psCursorLast = psCursor;
		}
		switch (m_eUnits)
		{
		case units::uSI:
			m_vDescription.push_back(std::string("in"));
			m_vDescription.push_back(std::string("SI"));
			m_vDescription.push_back(std::string("units"));
			break;
		case units::uCGS:
			m_vDescription.push_back(std::string("in"));
			m_vDescription.push_back(std::string("cgs"));
			m_vDescription.push_back(std::string("units"));
			break;
		case units::uEV:
			m_vDescription.push_back(std::string("in"));
			m_vDescription.push_back(std::string("eV"));
			break;
		}
		switch (m_ePrecision)
		{
		case precision::pShort:
			m_nPrint_Precision = 2; // ignroe the User's specified value
			m_vDescription.push_back(std::string("with"));
			m_vDescription.push_back(std::string("reduced"));
			m_vDescription.push_back(std::string("precision"));
			break;
		case precision::pFull:
			m_vDescription.push_back(std::string("with"));
			m_vDescription.push_back(std::string("full"));
			m_vDescription.push_back(std::string("precision"));
			break;
		}
	}

	void DescribeMacro(FILE * io_fOut) const
	{

		fprintf(io_fOut,"%% \\DescribeMacro{\\%s}\n",m_sMacroname.c_str());
		fprintf(io_fOut,"%% |\\%s| is",m_sMacroname.c_str());

		size_t nCharaters_On_Line = 8 + m_sMacroname.size();
		for (auto iterI = m_vDescription.begin(); iterI != m_vDescription.end(); iterI++)
		{
			if ((iterI->size() + nCharaters_On_Line + 1) > 79)
			{
				fprintf(io_fOut,"\n%%");
				nCharaters_On_Line = 1;
			}
			fprintf(io_fOut," %s",iterI->c_str());
			nCharaters_On_Line += (1 + iterI->size());
		}
		fprintf(io_fOut,".\n");


		fprintf(io_fOut,"%% (%s)\n%%\n",m_sSource.c_str());
		fprintf(io_fOut,"%% The macro can be invoked by (e.g.)\n%% \\begin{mdframed}[backgroundcolor=orange!25]%%\n%% {\\small\\texttt{\\textbackslash makeatletter\\\\ The value is\n%% \\textbackslash %s\\\\\n%% \\textbackslash makeatother}}\\end{mdframed}\n",m_sMacroname.c_str());
		fprintf(io_fOut,"%% \\makeatletter\n");
		fprintf(io_fOut,"%% Resulting in \n%% \\begin{mdframed}[backgroundcolor=blue!25]%%\n%% {The value is \\%s}\\end{mdframed}\n",m_sMacroname.c_str());
		fprintf(io_fOut,"%% \\makeatother\n%%\n");
	}
	void CodeMacro(FILE * io_fOut) const
	{
		fprintf(io_fOut,"%% \\begin{macro}{\\%s}\n",m_sMacroname.c_str());
		fprintf(io_fOut,"%% |\\%s| is",m_sMacroname.c_str());

		size_t nCharaters_On_Line = 8 + m_sMacroname.size();
		for (auto iterI = m_vDescription.begin(); iterI != m_vDescription.end(); iterI++)
		{
			if ((iterI->size() + nCharaters_On_Line + 1) > 79)
			{
				fprintf(io_fOut,"\n%%");
				nCharaters_On_Line = 1;
			}
			fprintf(io_fOut," %s",iterI->c_str());
			nCharaters_On_Line += (1 + iterI->size());
		}
		fprintf(io_fOut,".\n");


		fprintf(io_fOut,"%% Source: %s\n%%\n%%    \\begin{macrocode}\n",m_sSource.c_str());
	//	fprintf(io_fOut,"%% Source: %s"\n,i_psSource);
		int iExponent = (int)(std::floor(std::log10(std::fabs(m_fValue))));
		std::ostringstream osValue;
		osValue << std::scientific << std::setprecision(m_nPrint_Precision) << m_fValue;
		std::string sValue = osValue.str();
		fprintf(io_fOut,"\\DeclareRobustCommand{\\%s}{\\ensuremath{%%\n",m_sMacroname.c_str());

		const char * pValue_String = sValue.c_str();
		while (pValue_String != nullptr && pValue_String[0] != 0 && pValue_String[0] != '.')
		{
			fprintf(io_fOut,"%c",pValue_String[0]);
			pValue_String++;
		}
		fprintf(io_fOut,".");
		if (pValue_String != nullptr && pValue_String[0] != 0)
		{
			pValue_String++; // bypass decimal point
			size_t nCount = 0;
			while (pValue_String != nullptr && pValue_String[0] != 0 && pValue_String[0] != 'e' && pValue_String[0] != 'E' && pValue_String[0] != 'd' && pValue_String[0] != 'D')
			{
				if (nCount == 3)
				{
					fprintf(io_fOut,"\\expandafter\\physconst@decimalsseparator%%\n");
					nCount = 0;
				}
				fprintf(io_fOut,"%c",pValue_String[0]);
				pValue_String++;
				nCount++;
			}
		}
		if (iExponent != 0)
			fprintf(io_fOut,"%%\n\\times 10^{%i}",iExponent);
		fprintf(io_fOut,"%s}}\n",m_sUnits.c_str());

		fprintf(io_fOut,"%%    \\end{macrocode}\n%% \\end{macro}\n%%\n");
	}
};



class ConstantSet
{
public:
	std::vector<Constant> m_vSet;
	std::string m_sName;
	std::vector<std::string> m_vDescription;
	std::string m_sSource;
	bool		m_bUnit_Independent;
	bool		m_bHas_eV;

	ConstantSet(double i_fValue_SI, 
				double i_fValue_cgs, 
				double i_fValue_eV, 
				size_t i_nPrint_Precision,
				bool		i_bUnit_Independent,
				const char * i_psName,
				const char * i_psDescription,
				const char * i_psSource,
				const char * i_pUnitsSI,
				const char * i_pUnitsCGS,
				const char * i_pUnitsEV)
	{
		m_sName = i_psName;
		m_sSource = i_psSource;
		m_bUnit_Independent = i_bUnit_Independent;
		m_bHas_eV = false;

		const char * psCursorLast;
		const char * psCursor = i_psDescription;
		//bypass any leading whitespace
		while (psCursor != nullptr && psCursor[0] != 0 && (psCursor[0] == ' ' || psCursor[0] == '\t'))
		{
			psCursor++;
		}
		psCursorLast = psCursor;

		while (psCursor != nullptr && psCursor[0] != 0)
		{
			while (psCursor != nullptr && psCursor[0] != 0 && psCursor[0] != ' ' && psCursor[0] != '\t')
			{
				psCursor++;
			}
			std::string sCurr;
			while (psCursorLast != psCursor)
			{
				sCurr += psCursorLast[0];
				psCursorLast++;
			}
			m_vDescription.push_back(sCurr);
			while (psCursor != nullptr && psCursor[0] != 0 && (psCursor[0] == ' ' || psCursor[0] == '\t'))
			{
				psCursor++;
			}
			psCursorLast = psCursor;
		}
		if (m_bUnit_Independent)
		{
			m_vSet.push_back(Constant(i_fValue_SI,Constant::units::uNone,Constant::precision::pShort,i_nPrint_Precision,i_psName,i_psDescription,i_psSource,i_pUnitsSI));
			m_vSet.push_back(Constant(i_fValue_SI,Constant::units::uNone,Constant::precision::pFull,i_nPrint_Precision,i_psName,i_psDescription,i_psSource,i_pUnitsSI));
		}
		else
		{
			m_vSet.push_back(Constant(i_fValue_SI,Constant::units::uSI,Constant::precision::pShort,i_nPrint_Precision,i_psName,i_psDescription,i_psSource,i_pUnitsSI));
			m_vSet.push_back(Constant(i_fValue_SI,Constant::units::uSI,Constant::precision::pFull,i_nPrint_Precision,i_psName,i_psDescription,i_psSource,i_pUnitsSI));

			m_vSet.push_back(Constant(i_fValue_cgs,Constant::units::uCGS,Constant::precision::pShort,i_nPrint_Precision,i_psName,i_psDescription,i_psSource,i_pUnitsCGS));
			m_vSet.push_back(Constant(i_fValue_cgs,Constant::units::uCGS,Constant::precision::pFull,i_nPrint_Precision,i_psName,i_psDescription,i_psSource,i_pUnitsCGS));
			if (i_fValue_eV != 0.0)
			{
				m_bHas_eV = true;
				m_vSet.push_back(Constant(i_fValue_eV,Constant::units::uEV,Constant::precision::pShort,i_nPrint_Precision,i_psName,i_psDescription,i_psSource,i_pUnitsEV));
				m_vSet.push_back(Constant(i_fValue_eV,Constant::units::uEV,Constant::precision::pFull,i_nPrint_Precision,i_psName,i_psDescription,i_psSource,i_pUnitsEV));
			}
		}
	}
	void DescribeMacro(FILE * io_fOut) const
	{
		for (auto iterI = m_vSet.begin(); iterI != m_vSet.end(); iterI++)
		{
			iterI->DescribeMacro(io_fOut);
		}
	}
	void DescribeUsefulMacro(FILE * io_fOut) const
	{
		fprintf(io_fOut,"%% \\DescribeMacro{\\k%s}\n",m_sName.c_str());
		fprintf(io_fOut,"%% |\\k%s| is",m_sName.c_str());

		size_t nCharaters_On_Line = 9 + m_sName.size();
		for (auto iterI = m_vDescription.begin(); iterI != m_vDescription.end(); iterI++)
		{
			if ((iterI->size() + nCharaters_On_Line + 1) > 79)
			{
				fprintf(io_fOut,"\n%%");
				nCharaters_On_Line = 1;
			}
			fprintf(io_fOut," %s",iterI->c_str());
			nCharaters_On_Line += (1 + iterI->size());
		}
		fprintf(io_fOut,".\n%%\n");

		if (m_bHas_eV)
		{
			fprintf(io_fOut,"%% \\DescribeMacro{\\keV%s}\n",m_sName.c_str());
			fprintf(io_fOut,"%% |\\keV%s| is",m_sName.c_str());

			size_t nCharaters_On_Line = 11 + m_sName.size();
			for (auto iterI = m_vDescription.begin(); iterI != m_vDescription.end(); iterI++)
			{
				if ((iterI->size() + nCharaters_On_Line + 1) > 79)
				{
					fprintf(io_fOut,"\n%%");
					nCharaters_On_Line = 1;
				}
				fprintf(io_fOut," %s",iterI->c_str());
				nCharaters_On_Line += (1 + iterI->size());
			}
			fprintf(io_fOut,".\n%%\n");
		}
	}
	void CodeMacro(FILE * io_fOut) const
	{
		for (auto iterI = m_vSet.begin(); iterI != m_vSet.end(); iterI++)
		{
			iterI->CodeMacro(io_fOut);
		}

		if (m_bUnit_Independent)
		{
			fprintf(io_fOut,"%% \\begin{macro}{\\k%s}\n",m_sName.c_str());
			fprintf(io_fOut,"%% |\\k%s| is",m_sName.c_str());

			size_t nCharaters_On_Line = 9 + m_sName.size();
			for (auto iterI = m_vDescription.begin(); iterI != m_vDescription.end(); iterI++)
			{
				if ((iterI->size() + nCharaters_On_Line + 1) > 79)
				{
					fprintf(io_fOut,"\n%%");
					nCharaters_On_Line = 1;
				}
				fprintf(io_fOut," %s",iterI->c_str());
				nCharaters_On_Line += (1 + iterI->size());
			}
			fprintf(io_fOut,".\n%%\n%%    \\begin{macrocode}\n");
			fprintf(io_fOut,"\\ifx\\shortconst\\undefined\n\\DeclareRobustCommand {\\k%s}",m_sName.c_str());
			fprintf(io_fOut,"{\\k@short@%s}\n",m_sName.c_str());
			fprintf(io_fOut,"\\else\n\\DeclareRobustCommand {\\k%s}",m_sName.c_str());
			fprintf(io_fOut,"{\\k@full@%s}\n",m_sName.c_str());
			fprintf(io_fOut,"\\fi\n");

			fprintf(io_fOut,"%%    \\end{macrocode}\n%% \\end{macro}\n%%\n");
		}
		else
		{
			fprintf(io_fOut,"%% \\begin{macro}{\\k%s}\n",m_sName.c_str());
			fprintf(io_fOut,"%% |\\k%s| is",m_sName.c_str());

			size_t nCharaters_On_Line = 9 + m_sName.size();
			for (auto iterI = m_vDescription.begin(); iterI != m_vDescription.end(); iterI++)
			{
				if ((iterI->size() + nCharaters_On_Line + 1) > 79)
				{
					fprintf(io_fOut,"\n%%");
					nCharaters_On_Line = 1;
				}
				fprintf(io_fOut," %s",iterI->c_str());
				nCharaters_On_Line += (1 + iterI->size());
			}
			fprintf(io_fOut,".\n%%\n%%    \\begin{macrocode}\n");
			fprintf(io_fOut,"\\ifx\\cgsunits\\undefined\n\\ifx\\shortconst\\undefined\n\\DeclareRobustCommand {\\k%s}",m_sName.c_str());
			fprintf(io_fOut,"{\\k@SI@short@%s}\n",m_sName.c_str());
			fprintf(io_fOut,"\\else\n\\DeclareRobustCommand {\\k%s}",m_sName.c_str());
			fprintf(io_fOut,"{\\k@SI@full@%s}\n",m_sName.c_str());
			fprintf(io_fOut,"\\fi\n\\else\n\\ifx\\shortconst\\undefined\n\\DeclareRobustCommand {\\k%s}",m_sName.c_str());
			fprintf(io_fOut,"{\\k@cgs@short@%s}\n",m_sName.c_str());
			fprintf(io_fOut,"\\else\n\\DeclareRobustCommand {\\k%s}",m_sName.c_str());
			fprintf(io_fOut,"{\\k@cgs@full@%s}\n",m_sName.c_str());
			fprintf(io_fOut,"\\fi\n\\fi\n");

			fprintf(io_fOut,"%%    \\end{macrocode}\n%% \\end{macro}\n%%\n");

			if (m_bHas_eV)
			{
				fprintf(io_fOut,"%% \\begin{macro}{\\keV%s}\n",m_sName.c_str());
				fprintf(io_fOut,"%% |\\keV%s| is",m_sName.c_str());

				size_t nCharaters_On_Line = 11 + m_sName.size();
				for (auto iterI = m_vDescription.begin(); iterI != m_vDescription.end(); iterI++)
				{
					if ((iterI->size() + nCharaters_On_Line + 1) > 79)
					{
						fprintf(io_fOut,"\n%%");
						nCharaters_On_Line = 1;
					}
					fprintf(io_fOut," %s",iterI->c_str());
					nCharaters_On_Line += (1 + iterI->size());
				}
				fprintf(io_fOut,".\n%%\n%%    \\begin{macrocode}\n");
				fprintf(io_fOut,"\\ifx\\shortconst\\undefined\n\\DeclareRobustCommand {\\keV%s}",m_sName.c_str());
				fprintf(io_fOut,"{\\k@eV@short@%s}\n",m_sName.c_str());
				fprintf(io_fOut,"\\else\n\\DeclareRobustCommand {\\keV%s}",m_sName.c_str());
				fprintf(io_fOut,"{\\k@eV@full@%s}\n",m_sName.c_str());
				fprintf(io_fOut,"\\fi\n");

				fprintf(io_fOut,"%%    \\end{macrocode}\n%% \\end{macro}\n%%\n");
			}
		}
	}
};

class GroupContainer
{
public:
	std::string m_sGroup;
	std::vector<ConstantSet> m_vConstants;

	GroupContainer(std::string i_sGroup)
	{
		m_sGroup = i_sGroup;
	}
	void add(const ConstantSet & i_cConstantSet)
	{
		m_vConstants.push_back(i_cConstantSet);
	}
};
void Generate(const std::vector<GroupContainer > & i_vGroups)
{
	FILE * fileOut = fopen("physconst.dtx","wt");

	fprintf(fileOut,"%%	\\iffalse meta-comment\n");
	fprintf(fileOut,"%%\n");
	fprintf(fileOut,"%%	Copyright (C) 2020 by Brian W. Mulligan <bwmulligan@astronaos.com>\n");
	fprintf(fileOut,"%% -----------------------------------------------------------\n");
	fprintf(fileOut,"%%\n");
	fprintf(fileOut,"%% This file may be distributed and/or modified under the conditions of\n");
	fprintf(fileOut,"%% the LaTeX Project Public License, either version 1.3c of this license\n");
	fprintf(fileOut,"%% or (at your option) any later version. The latest version of this\n");
	fprintf(fileOut,"%% license is in:\n");
	fprintf(fileOut,"%%\n");
	fprintf(fileOut,"%% http://www.latex-project.org/lppl.txt\n");
	fprintf(fileOut,"%%\n");
	fprintf(fileOut,"%% and version 1.3c or later is part of all distributions of LaTeX\n");
	fprintf(fileOut,"%% version 2006/05/20 or later.\n");
	fprintf(fileOut,"%%\n");
	fprintf(fileOut,"%% \\fi\n");
	fprintf(fileOut,"%%\n");
	fprintf(fileOut,"%% \\iffalse\n");
	fprintf(fileOut,"%%<*driver>\n");
	fprintf(fileOut,"\\ProvidesFile{physconst.dtx}\n");
	fprintf(fileOut,"%%</driver>\n");
	fprintf(fileOut,"%%<package>\\NeedsTeXFormat{LaTeX2e}[1994/06/01]\n");
	fprintf(fileOut,"%%<package> \\ProvidesPackage{physconst}\n");
	fprintf(fileOut,"%%<*package>\n");
	fprintf(fileOut,"    [2020/01/25 v1.0 Physical constants package]\n");
	fprintf(fileOut,"%%</package>\n");
	fprintf(fileOut,"%%<package>\\RequirePackage{physunits}\n");
	fprintf(fileOut,"%%<package>\\DeclareOption{shortconst}{ \\typeout{physconst: reduced precision}%%\n");
	fprintf(fileOut,"%%<package> \\DeclareRobustCommand{\\shortconst}{1} }\n");
	fprintf(fileOut,"%%<package>\\DeclareOption{cgs}{ \\typeout{physconst: using cgs instead of SI}%%\n");
	fprintf(fileOut,"%%<package> \\DeclareRobustCommand{\\cgsunits}{1} }\n");
	fprintf(fileOut,"%%<package>\\DeclareOption{unseparatedecimals}{ \\typeout{physconst:%%\n");
	fprintf(fileOut,"%%<package> long decimals are printed as x.xxxxxx instead of x.xxx~xxx}%%\n");
	fprintf(fileOut,"%%<package> \\DeclareRobustCommand{\\unseparatedecimals}{1} }\n");
	fprintf(fileOut,"%%<package>\\ProcessOptions\\relax\n");
	fprintf(fileOut,"%%<*driver>\n");
	fprintf(fileOut,"\\documentclass{ltxdoc}\n");
	fprintf(fileOut,"\\usepackage{float}\n");
	fprintf(fileOut,"\\usepackage{tikz}\n");
	fprintf(fileOut,"\\usepackage{xcolor}\n");
	fprintf(fileOut,"\\usepackage{mdframed}\n");
	fprintf(fileOut,"\\usepackage{physconst}\n");
	fprintf(fileOut,"\\EnableCrossrefs\n");
	fprintf(fileOut,"\\CodelineIndex\n");
	fprintf(fileOut,"\\RecordChanges\n");
	fprintf(fileOut,"\\OnlyDescription\n");
	fprintf(fileOut,"\\begin{document}\n");
	fprintf(fileOut,"\\DocInput{physconst.dtx}\n");
	fprintf(fileOut,"\\PrintChanges\n");
	fprintf(fileOut,"\\PrintIndex\n");
	fprintf(fileOut,"\\end{document}\n");
	fprintf(fileOut,"%%</driver>\n");
	fprintf(fileOut,"%% \\fi\n");
	fprintf(fileOut,"%%\n");
	fprintf(fileOut,"%% \\CheckSum{0}\n");
	fprintf(fileOut,"%%\n");
	fprintf(fileOut,"%% \\CharacterTable\n");
	fprintf(fileOut,"%%  {Upper-case    \\A\\B\\C\\D\\E\\F\\G\\H\\I\\J\\K\\L\\M\\N\\O\\P\\Q\\R\\S\\T\\U\\V\\W\\X\\Y\\Z\n");
	fprintf(fileOut,"%%   Lower-case    \\a\\b\\c\\d\\e\\f\\g\\h\\i\\j\\k\\l\\m\\n\\o\\p\\q\\r\\s\\t\\u\\v\\w\\x\\y\\z\n");
	fprintf(fileOut,"%%   Digits        \\0\\1\\2\\3\\4\\5\\6\\7\\8\\9\n");
	fprintf(fileOut,"%%   Exclamation   \\!     Double quote  \\\"     Hash (number) \\#\n");
	fprintf(fileOut,"%%   Dollar        \\$     Percent       \\%%     Ampersand     \\&\n");
	fprintf(fileOut,"%%   Acute accent  \\'     Left paren    \\(     Right paren   \\)\n");
	fprintf(fileOut,"%%   Asterisk      \\*     Plus          \\+     Comma         \\,\n");
	fprintf(fileOut,"%%   Minus         \\-     Point         \\.     Solidus       \\/\n");
	fprintf(fileOut,"%%   Colon         \\:     Semicolon     \\;     Less than     \\<\n");
	fprintf(fileOut,"%%   Equals        \\=     Greater than  \\>     Question mark \\?\n");
	fprintf(fileOut,"%%   Commercial at \\@     Left bracket  \\[     Backslash     \\\\\n");
	fprintf(fileOut,"%%   Right bracket \\]     Circumflex    \\^     Underscore    \\_\n");
	fprintf(fileOut,"%%   Grave accent  \\`     Left brace    \\{     Vertical bar  \\|\n");
	fprintf(fileOut,"%%   Right brace   \\}     Tilde         \\~}\n");
	fprintf(fileOut,"%%\n");
	fprintf(fileOut,"%% \\changes{v1.0}{2020/01/25}{Initial version}\n");
	fprintf(fileOut,"%%\n");
	fprintf(fileOut,"%% \\GetFileInfo{physconst.dtx}\n");
	fprintf(fileOut,"%% \\def\\fileversion{v1.0}\n");
	fprintf(fileOut,"%% \\def\\filedate{2020/01/25}\n");
	fprintf(fileOut,"%%\n");
	fprintf(fileOut,"%% \\DoNotIndex{\\DeclareRobustCommand,\\newenvironment,\\DeclareRobustCommand,\\left,\\right,\\textbf,\\mathrm}\n");
	fprintf(fileOut,"%%\n");
	fprintf(fileOut,"%% \\title{The \\textsf{physconst} package\\thanks{This document corresponds to \\textsf{physconst}~\\fileversion, dated \\filedate.}}\n");
	fprintf(fileOut,"%% \\author{Brian W. Mulligan \\\\ \\texttt{bwmulligan@astronaos.com}}\n");
	fprintf(fileOut,"%%\n");
	fprintf(fileOut,"%% \\maketitle\n");
	fprintf(fileOut,"%%\n");
	fprintf(fileOut,"%% \\section{Introduction}\n");
	fprintf(fileOut,"%%\n");
	fprintf(fileOut,"%%\n"); 
	fprintf(fileOut,"%% This package consists of several macros that are shorthand for a variety of\n");
	fprintf(fileOut,"%% physical constants, e.g. the speed of light.\n");
	fprintf(fileOut,"%% The package developed out of physics and astronomy classes that I have\n"); 
	fprintf(fileOut,"%% taught and wanted to ensure that I had correct values for each constant\n");
	fprintf(fileOut,"%% and did not wish to retype them every time I use them.\n");
	fprintf(fileOut,"%% The constants can be used in two forms, the most accurate available values,\n");
	fprintf(fileOut,"%% or versions that are rounded to 3 significant digits for use in typical\n");
	fprintf(fileOut,"%% classroom settings, homework assignments, etc.\n");
	fprintf(fileOut,"%%\n");
	fprintf(fileOut,"%% Most constants are taken from CODATA 2018, with the exception of the\n"); 
	fprintf(fileOut,"%% astronomical objects, whose values are taken from their current wikipedia\n");
	fprintf(fileOut,"%% entries. If you have an interest and/or need for more reliable data, \n");
	fprintf(fileOut,"%% please contact me.\n");
	fprintf(fileOut,"%%\n%%\\subsection{Macros}\n%%\n");
	fprintf(fileOut,"%%\n%%\\subsection{Normal Macros}\n%%\n");
	fprintf(fileOut,"%% The normal macros are the ones that you will typically use, whose values are\n");
	fprintf(fileOut,"%% determined by the choice of options when the package is invoked.\n");
	fprintf(fileOut,"%%\n");
	fprintf(fileOut,"%% \\subsection{Naming Convention}\n");
	fprintf(fileOut,"%%\n");
	fprintf(fileOut,"%% Each macro starts with a lower case `k' to indicate that it is a constant.\n");
	fprintf(fileOut,"%% If the macro is of special units, e.g. eV, those units will be specified next.\n");
	fprintf(fileOut,"%% If the macro is part of a fundamental unit group, it then gets the name of the\n");
	fprintf(fileOut,"%% group, e.g. Mass, Charge, etc.\n");
	fprintf(fileOut,"%% Finally is the details or name of the constants, e.g. Proton, Planck, etc.\n");

	for (auto iterI = i_vGroups.cbegin(); iterI != i_vGroups.cend(); iterI++)
	{
		fprintf(fileOut,"%%\n%%\\subsubsection{%s}\n%%\n",iterI->m_sGroup.c_str());
		for (auto iterJ = iterI->m_vConstants.cbegin(); iterJ != iterI->m_vConstants.cend(); iterJ++)
		{
			iterJ->DescribeUsefulMacro(fileOut);
		}
	}

	fprintf(fileOut,"%%\n%%\\subsection{Detailed Macros}\n%%\n");
	fprintf(fileOut,"%% These macros are used to access the constants with specific units and \n");
	fprintf(fileOut,"%% precision. They require use of \\textbackslash makeatletter and\n");
	fprintf(fileOut,"%% \\textbackslash makeatother in order to be used. They are used internally\n");
	fprintf(fileOut,"%% by physconst to define the macros that are normally used (those described\n");
	fprintf(fileOut,"%% above.\n");
	fprintf(fileOut,"%%\n");
	fprintf(fileOut,"%% \\subsection{NamingConvention}\n");
	fprintf(fileOut,"%% The detailed macros are named like \\k@units@precision@name. The units\n");
	fprintf(fileOut,"%% specify which units the constant is in (SI, cgs, or eV). For constants that\n");
	fprintf(fileOut,"%% are independent of the unit system (e.g. Avogadro's number and the fine\n"); 
	fprintf(fileOut,"%% structure constant), the units are omitted. The precision is either `short'\n");
	fprintf(fileOut,"%% or `full' to indicate how much precision is included in the number. All short\n");
	fprintf(fileOut,"%% precision constants have 3 significant figures. The precision of full\n");
	fprintf(fileOut,"%% precision constants vary by their definition and/or inputs. Finally, the\n");
	fprintf(fileOut,"%% name or description of the constant appears.\n");

	for (auto iterI = i_vGroups.cbegin(); iterI != i_vGroups.cend(); iterI++)
	{
		fprintf(fileOut,"%%\n%%\\subsubsection{%s}\n%%\n",iterI->m_sGroup.c_str());
		for (auto iterJ = iterI->m_vConstants.cbegin(); iterJ != iterI->m_vConstants.cend(); iterJ++)
		{
			iterJ->DescribeMacro(fileOut);
		}
	}
	fprintf(fileOut,"%% \\StopEventually{}\n");
	fprintf(fileOut,"%%\n");
	fprintf(fileOut,"\\makeatletter\n");
	fprintf(fileOut,"%% \\section{Implementation}\n");
	fprintf(fileOut,"%%\n");
	fprintf(fileOut,"%% \\subsection{Special}\n");
	fprintf(fileOut,"%%\n");
	fprintf(fileOut,"%% \\begin{macro}{\\physconst@decimalsseparator}\n");
	fprintf(fileOut,"%% |\\physconst@decimalsseparator| is the a special macro used to separate digits\n");
	fprintf(fileOut,"%% in the decimal portion of the constants. If the option unseparatedecimals is\n"); 
	fprintf(fileOut,"%% not specified, decimals will be printed as 1.234\\,567\\,890. If the option\n");
	fprintf(fileOut,"%% is specified, decimals will be printed as 1.234567890. This macro should\n"); 
	fprintf(fileOut,"%% note be used outside of this package.\n");
	fprintf(fileOut,"%%\n");
	fprintf(fileOut,"%%    \\begin{macrocode}\n");
	fprintf(fileOut,"\\ifx\\unseparatedecimals\\undefined\n");
	fprintf(fileOut,"\\DeclareRobustCommand{\\physconst@decimalsseparator}{\\,}\n");
	fprintf(fileOut,"\\else\n");
	fprintf(fileOut,"\\DeclareRobustCommand{\\physconst@decimalsseparator}{ }\n");
	fprintf(fileOut,"\\fi\n");
	fprintf(fileOut,"%%    \\end{macrocode}\n");
	fprintf(fileOut,"%% \\end{macro}\n");

	for (auto iterI = i_vGroups.cbegin(); iterI != i_vGroups.cend(); iterI++)
	{
		fprintf(fileOut,"%%\n%%\\subsection{%s}\n%%\n",iterI->m_sGroup.c_str());
		for (auto iterJ = iterI->m_vConstants.cbegin(); iterJ != iterI->m_vConstants.cend(); iterJ++)
		{
			iterJ->CodeMacro(fileOut);
		}
	}


	fprintf(fileOut,"%% \\Finale\n");
	fprintf(fileOut,"\\makeatother\n");


	fclose(fileOut);
}


int main(void)
{
	GroupContainer gMass("Mass");
	GroupContainer gCharge("Charge");
	GroupContainer gLength("Distances and Lengths");
	GroupContainer gEnergy("Energy, Power, and Luminosity");
	GroupContainer gPressure("Pressure");
	GroupContainer gSpeed("Velocity, Speed and Acceleration");
	GroupContainer gOther("Other Constants");
///////////////////////////////////////////////////////////////////
//
//
//	Mass
//
//
///////////////////////////////////////////////////////////////////
	gMass.add(ConstantSet(g_XASTRO.k_dme * 1.0e-3,g_XASTRO.k_dme,g_XASTRO.k_dme * g_XASTRO.k_deV_erg,12,false,"MassElectron","the mass of an electron","CODATA~2018","\\kg","\\gm","\\eV\\,c^{-2}"));
	gMass.add(ConstantSet(g_XASTRO.k_dmp * 1.0e-3,g_XASTRO.k_dmp,g_XASTRO.k_dmp * g_XASTRO.k_deV_erg,12,false,"MassProton","the mass of a proton","CODATA~2018","\\kg","\\gm","\\eV\\,c^{-2}"));
	gMass.add(ConstantSet(g_XASTRO.k_dmh * 1.0e-3,g_XASTRO.k_dmh,g_XASTRO.k_dmh * g_XASTRO.k_deV_erg,12,false,"MassHydrogen","the mass of a neutral hydrogen atom","CODATA~2018","\\kg","\\gm","\\eV\\,c^{-2}"));
	gMass.add(ConstantSet(g_XASTRO.k_dMsun * 1.0e-3,g_XASTRO.k_dMsun,0.0,7,false,"MassSun","the mass of the Sun","IAU~Resolution~B3~2015","\\kg","\\gm","\\eV\\,c^{-2}"));
//	gMass.add(ConstantSet(g_XASTRO.k_dMearth * 1.0e-3,g_XASTRO.k_dMearth,0.0,12,true,"MassEarth","the mass of the Earth","IAU~Resolution~B3~2015","\\kg","\\gm","\\eV\\,c^{-2}"));
//	gMass.add(ConstantSet(g_XASTRO.k_dMmoon * 1.0e-3,g_XASTRO.k_dMmoon,0.0,12,true,"MassMoon","the mass of the Moon","IAU~Resolution~B3~2015","\\kg","\\gm","\\eV\\,c^{-2}"));
//	gMass.add(ConstantSet(g_XASTRO.k_dMjupiter * 1.0e-3,g_XASTRO.k_dMjupiter,0.0,12,true,"MassJupiter","the mass of Jupiter","IAU~Resolution~B3~2015","\\kg","\\gm","\\eV\\,c^{-2}"));
	gMass.add(ConstantSet(g_XASTRO.k_dAMU_gm * 1.0e-3,g_XASTRO.k_dAMU_gm,g_XASTRO.k_dAMU_gm * g_XASTRO.k_deV_erg,12,false,"MassAMU","the mass of an atomic mass unit","CODATA~2018","\\kg","\\gm","\\eV\\,c^{-2}"));

///////////////////////////////////////////////////////////////////
//
//
//	Charges
//
//
///////////////////////////////////////////////////////////////////
	gCharge.add(ConstantSet(g_XASTRO.k_dQe,g_XASTRO.k_de,0.0,9,false,"ChargeFundamental","the fundamental charge","CODATA~2018","\\Coulomb","\\esu",nullptr));
	gCharge.add(ConstantSet(-g_XASTRO.k_dQe,-g_XASTRO.k_de,0.0,9,false,"ChargeElectron","the charge of an electron","CODATA~2018","\\Coulomb","\\esu",nullptr));
	gCharge.add(ConstantSet(g_XASTRO.k_dQe,g_XASTRO.k_de,0.0,9,false,"ChargeProton","the charge of a proton","CODATA~2018","\\Coulomb","\\esu",nullptr));

///////////////////////////////////////////////////////////////////
//
//
//	Distances and Lengths
//
//
///////////////////////////////////////////////////////////////////
	gLength.add(ConstantSet(g_XASTRO.k_da0 * 1.0e-2,g_XASTRO.k_da0,0.0,8,false,"RadiusBohr","Bohr radius of an atom","Calculated","\\m","\\cm",nullptr));
	gLength.add(ConstantSet(g_XASTRO.k_dAU_cm * 1e-2,g_XASTRO.k_dAU_cm,0.0,9,false,"AstronomicalUnit","the astronomical unit (the average distance between the Earth and the Sun)","IAU~Resolution~B2~2012","\\m","\\cm",nullptr));
	gLength.add(ConstantSet(g_XASTRO.k_dpc_cm * 1e-2,g_XASTRO.k_dpc_cm,0.0,9,false,"Parsec","the length of a parsec ($\\frac{648000\\au}{\\pi}$)","Calculated","\\m","\\cm",nullptr));
	gLength.add(ConstantSet(g_XASTRO.k_dRsun * 1e-2,g_XASTRO.k_dRsun,0.0,3,false,"RadiusSun","the mean radius of the Sun","IAU~Resolution~B3~2015","\\m","\\cm",nullptr));
//	gLength.add(ConstantSet(g_XASTRO.k_dRearth * 1e-2,g_XASTRO.k_dRearth,0.0,12,true,"RadiusEarth","the mean radius of the Earth","IAU~Resolution~B3~2015","\\m","\\cm",nullptr));
//	gLength.add(ConstantSet(g_XASTRO.k_dRmoon * 1e-2,g_XASTRO.k_dRmoon,0.0,12,true,"RadiusMoon","the mean radius of the Moon","IAU~Resolution~B3~2015","\\m","\\cm",nullptr));
//	gLength.add(ConstantSet(g_XASTRO.k_dRjupiter * 1e-2,g_XASTRO.k_dRjupiter,0.0,12,true,"RadiusJupiter","the mean radius of Jupiter","IAU~Resolution~B3~2015","\\m","\\cm",nullptr));
//	gLength.add(ConstantSet(g_XASTRO.k_dDmoon * 1e-2,g_XASTRO.k_dDmoon,0.0,12,true,"DistanceMoon","the mean distance between the Earth and the Moon","IAU~Resolution~B3~2015","\\m","\\cm",nullptr));

///////////////////////////////////////////////////////////////////
//
//
//	Luminosity
//
//
///////////////////////////////////////////////////////////////////
	gEnergy.add(ConstantSet(g_XASTRO.k_dRy * 1e-7,g_XASTRO.k_dRy,g_XASTRO.k_dRy_eV,8,false,"Rydberg","the Rydberg energy (the binding energy of Hydrogen)","Calculated","\\Joule","\\erg","\\eV"));
	gEnergy.add(ConstantSet(g_XASTRO.k_dLsun * 1e-7,g_XASTRO.k_dLsun,0.0,3,false,"LuminositySun","the luminosity of the Sun","IAU~Resolution~B3~2015","\\Watt","\\erg\\Sec^{-1}",nullptr));

///////////////////////////////////////////////////////////////////
//
//
//	Pressure
//
//
///////////////////////////////////////////////////////////////////
	gPressure.add(ConstantSet(101325.0,1.01325,0.0,5,false,"PressureAtmosphere","the standard atmospheric pressure","CODATA~2018","\\Pa","\\barP[m]",nullptr));
	gPressure.add(ConstantSet(100000.0,1.0,0.0,5,false,"PressureStandard","the standard atmospheric pressure","CODATA~2018","\\Pa","\\barP[m]",nullptr));

///////////////////////////////////////////////////////////////////
//
//
//	Speed and Acceleration
//
//
///////////////////////////////////////////////////////////////////
	gSpeed.add(ConstantSet(g_XASTRO.k_dc * 1.0e-2,g_XASTRO.k_dc,0.0,8,false,"SpeedLight","the speed of light","CODATA 2018","\\m\\Sec^{-1}","\\cm\\Sec^{-1}",nullptr));
	gSpeed.add(ConstantSet(g_XASTRO.k_dG * 1.0e-3,g_XASTRO.k_dG,0.0,5,false,"AccelGravity","the accelertion due to gravity at the surface of the Earth","CODATA 2018","\\N\\kg^{-2}\\m^2","\\dyne\\gm^{-2}\\cm^2",nullptr));

///////////////////////////////////////////////////////////////////
//
//
//	Other
//
//
///////////////////////////////////////////////////////////////////
	gOther.add(ConstantSet(g_XASTRO.k_dc * g_XASTRO.k_dc * 1.0e-7,1.0,0.0,8,false,"Coulomb","the Coulomb constant ($\\frac{1}{4\\pi\\epsilon_0}$) ","Calculated","\\N\\m^2\\Coulomb^{-2}","",nullptr));
	gOther.add(ConstantSet(8.8541878128e-12,1.0 / (4.0 * g_XASTRO.k_dpi),0.0,10,false,"VacuumPermittivity","the electric permittivity of the vacuum","CODATA~2018","\\Farad\\m^{-1}","",nullptr));
	gOther.add(ConstantSet(8.8541878128e-12,4.0 * g_XASTRO.k_dpi,0.0,10,false,"VacuumPermeability","the magnetic permeability of the vacuum","CODATA~2018","\\N\\Amp^{-2}","",nullptr));
	gOther.add(ConstantSet(376.730313668,0.0,0.0,11,true,"VacuumImpedance","the characteristic impedance of the vacuum","CODATA~2018","\\Ohm","",nullptr));
	gOther.add(ConstantSet(g_XASTRO.k_dKb * 1.0e-7,g_XASTRO.k_dKb,g_XASTRO.k_dKb_eV,6,false,"Boltzmann","the Boltzmann constant","CODATA~2018","\\J\\K^{-1}","\\erg\\K^{-1}","\\eV\\K^{-1}"));
	gOther.add(ConstantSet(g_XASTRO.k_dh * 1.0e-7,g_XASTRO.k_dh,g_XASTRO.k_dh_eV,8,false,"Planck","the Planck constant","CODATA~2018","\\J\\Sec","\\erg\\Sec","\\eV\\Sec"));
	gOther.add(ConstantSet(g_XASTRO.k_dhbar * 1.0e-7,g_XASTRO.k_dhbar,g_XASTRO.k_dhbar_eV,8,false,"PlanckReduced","the Reduced Planck constant $\\left(\\frac{h}{2\\pi}\\right)$","Calculated","\\J\\Sec","\\erg\\Sec","\\eV\\Sec"));
	gOther.add(ConstantSet(g_XASTRO.k_dG * 1.0e-7,g_XASTRO.k_dG,0.0,5,false,"Gravity","Newton's gravitational constant","CODATA~2018","\\N\\kg^{-2}\\m^2","\\dyne\\gm^{-2}\\cm^2",nullptr));
	gOther.add(ConstantSet(g_XASTRO.k_dSigma_SB * 1.0e-1,g_XASTRO.k_dSigma_SB,0.0,6,false,"StefanBoltzmann","the Stefan-Boltzmann blackbody constant $\\left(\\frac{2\\pi^5k_\\mathrm{B}}{15h^3c^2}\\right)$","Calculated","\\J\\Kelvin^{-4}\\m^{-2}\\Sec^{-1}","\\erg\\Kelvin^{-4}\\cm^{-2}\\Sec^{-1}",nullptr));
//	gOther.add(ConstantSet(g_XASTRO.k_dSigma_Te * 1.0e-4,g_XASTRO.k_dSigma_Te,0.0,5,false,"ThomsonElectron","the Thomson cross-section of the electron $\\left(\\frac{8\\pi}{3}\\frac{q_e^4}{m^2}\\right)$","Calculated","\\m^{-2}","\\cm^{-2}",nullptr));
//	gOther.add(ConstantSet(g_XASTRO.k_dSigma_Tp * 1.0e-4,g_XASTRO.k_dSigma_Tp,0.0,5,false,"ThomsonProton","the Thomson cross-section of the proton","Calculated","\\m^{-2}","\\cm^{-2}",nullptr));
	gOther.add(ConstantSet(g_XASTRO.k_da * 1.0e-1,g_XASTRO.k_da,0.0,6,false,"Radiation","the radiation constant, $a \\left(\\frac{8\\pi^5k_\\mathrm{B}^4}{15c^3h^3}\\right)$","Calculated","\\Joule\\m^{-3}\\Kelvin^{-4}","\\erg\\cm^{-3}\\Kelvin^{-4}",nullptr));
	gOther.add(ConstantSet(g_XASTRO.k_dAlpha,0.0,0.0,8,true,"FineStructure","the fine structure constant","Calculated","",nullptr,nullptr));
	gOther.add(ConstantSet(1.0 / g_XASTRO.k_dAlpha,0.0,0.0,8,true,"FineStructureReciprocal","the reciprocal of the fine structure constant","Calculated","",nullptr,nullptr));
	gOther.add(ConstantSet(g_XASTRO.k_dAvogadro,0.0,0.0,8,true,"Avogadro","Avogadro's Number (the number of particles in a mole)","CODATA~2018","",nullptr,nullptr));





	std::vector<GroupContainer> vGroups;

	vGroups.push_back(gMass);
	vGroups.push_back(gCharge);
	vGroups.push_back(gLength);
	vGroups.push_back(gEnergy);
	vGroups.push_back(gPressure);
	vGroups.push_back(gSpeed);
	vGroups.push_back(gOther);


	Generate(vGroups);
	return 0;
}
