//******************************************************************************
// This file is part of AmpTools, a package for performing Amplitude Analysis
// 
// Copyright Trustees of Indiana University 2010, all rights reserved
// 
// This software written by Matthew Shepherd, Ryan Mitchell, and 
//                  Hrayr Matevosyan at Indiana University, Bloomington
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
// 1. Redistributions of source code must retain the above copyright
//    notice and author attribution, this list of conditions and the
//    following disclaimer. 
// 2. Redistributions in binary form must reproduce the above copyright
//    notice and author attribution, this list of conditions and the
//    following disclaimer in the documentation and/or other materials
//    provided with the distribution.
// 3. Neither the name of the University nor the names of its contributors
//    may be used to endorse or promote products derived from this software
//    without specific prior written permission.
// 
// Creation of derivative forms of this software for commercial
// utilization may be subject to restriction; written permission may be
// obtained from the Trustees of Indiana University.
// 
// INDIANA UNIVERSITY AND THE AUTHORS MAKE NO REPRESENTATIONS OR WARRANTIES, 
// EXPRESS OR IMPLIED.  By way of example, but not limitation, INDIANA 
// UNIVERSITY MAKES NO REPRESENTATIONS OR WARRANTIES OF MERCANTABILITY OR 
// FITNESS FOR ANY PARTICULAR PURPOSE OR THAT THE USE OF THIS SOFTWARE OR 
// DOCUMENTATION WILL NOT INFRINGE ANY PATENTS, COPYRIGHTS, TRADEMARKS, 
// OR OTHER RIGHTS.  Neither Indiana University nor the authors shall be 
// held liable for any liability with respect to any claim by the user or 
// any other party arising from use of the program.
//******************************************************************************


//****************************************************************
//
// ConfigFileParser Class:
//
//   This class parses config files that follow these rules:
//
// #####################################
// ####    THIS IS A CONFIG FILE    ####
// #####################################
// ##
// ##  Blank lines or lines beginning with a "#" are ignored.
// ##
// ##  Double colons (::) are treated like a space.
// ##	  This is sometimes useful for grouping (for example,
// ##     grouping strings like "reaction::sum::amplitudeName")
// ##
// ##  All non-comment lines must begin with one of the following keywords.
// ##
// ##  (note:  <word> means necessary 
// ##	       (word) means optional)
// ##
// ##  include       <file>
// ##  define	     <word> (defn1) (defn2) (defn3) ...
// ##  fit           <fitname>
// ##  keyword       <keyword> <min arguments> <max arguments>
// ##  reaction      <reaction> <particle1> <particle2> (particle3) ...
// ##  datafile      <reaction> <file> (file2) (file3) ...
// ##  genmcfile     <reaction> <file> (file2) (file3) ...
// ##  accmcfile     <reaction> <file> (file2) (file3) ...
// ##  normintfile   <reaction> <file>
// ##  sum	     <reaction> <sum> (sum2) (sum3) ...
// ##  amplitude     <reaction> <sum> <amp> <class> (arg1) (arg2) ([par]) ... 
// ##  initialize    <reaction> <sum> <amp> <"events"/"polar"/"cartesian">
// ##		       <value1> <value2> ("fixed"/"real")
// ##  constrain     <reaction1> <sum1> <amp1> <reaction2> <sum2> <amp2> ...
// ##  permute       <reaction> <sum> <amp> <index1> <index2> ...
// ##  parameter     <par> <value> ("fixed"/"bounded"/"gaussian") 
// ##		       (lower/central) (upper/error)
// ##
// #####################################
//
//****************************************************************


#if !defined(CONFIGFILEPARSER)
#define CONFIGFILEPARSER

#include <utility>
#include <string>
#include <vector>
#include <map>
#include <complex>
#include "IUAmpTools/ConfigurationInfo.h"

using namespace std;

class ConfigFileLine;



class ConfigFileParser
{

  public:


    ConfigFileParser(const string& configFile, bool verboseParsing = false);

    ~ConfigFileParser();


      // Return the ConfigurationInfo object for this configFile

    ConfigurationInfo* getConfigurationInfo();


      // Get the ConfigFileLines for a specified configFile
      //   ("include" and "define" statements are NOT expanded)

    vector<ConfigFileLine> getConfigFileLines(const string& configFile) const;


      // Get the ConfigFileLines for the main configFile (given in the constructor)
      //   ("include" and "define" statements are expanded)

    vector<ConfigFileLine> getConfigFileLines();


      // Display all the lines of the main configFile

    void displayConfigFile() const;



  private:

    ConfigFileParser(); // disable default


      // Do checks on the syntax, check keywords, etc.

    void checkSyntax() const;


      // Do the setup for each keyword

    void doFit           (const ConfigFileLine& line);
    void doReaction      (const ConfigFileLine& line);
    void doParameter     (const ConfigFileLine& line);
    void doFileName      (const ConfigFileLine& line);
    void doSum           (const ConfigFileLine& line);
    void doAmplitude     (const ConfigFileLine& line);
    void doInitialize    (const ConfigFileLine& line);
    void doPermute       (const ConfigFileLine& line);
    void doConstrain     (const ConfigFileLine& line);
    void doScale         (const ConfigFileLine& line);


      // Member data

    string                  m_fitName;
    string                  m_configFile;
    bool                    m_verboseParsing;
    vector<ConfigFileLine>  m_configFileLines;
    ConfigurationInfo*      m_configurationInfo;


};





//  **********************************************************************
//
//  class ConfigFileLine:  A class to hold a line of a parsed config file.
//
//    a line of the config file has the form:
//
//        keyword  argument1  argument2  argument3 .....
//
//    comment() = true for lines starting with # or empty lines
//
//  **********************************************************************

class ConfigFileLine
{

  public:

    ConfigFileLine(const string& fileName, int lineNumber, const string& line);

    string          line()           const {return m_line;}
    string          fileName()       const {return m_fileName;}
    int             lineNumber()     const {return m_lineNumber;}
    string          keyword()        const {return m_keyword;}
    vector<string>  arguments()      const {return m_arguments;}
    bool            comment()        const {return m_comment;}

    void            printLine()      const {cout << "(" << m_lineNumber << ") " << 
                                                    m_fileName   << " >>   " << 
                                                    m_line       << endl;}

    void            printArguments() const {cout << "KEYWORD:  " << m_keyword << endl;
                                            cout << "ARGUMENTS: " << endl;
                                            for ( unsigned int i = 0; i < m_arguments.size(); i++){
                                              cout << m_arguments[i] << endl;}}

    void            flushDefinition(const string& word, const vector<string>& definition);

  private:

    string          m_line;
    string          m_fileName;
    int             m_lineNumber;
    string          m_keyword;
    vector<string>  m_arguments;
    bool            m_comment;

};


#endif
