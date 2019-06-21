#ifndef DISPLAY_H
#define DISPLAY_H
///////////////////////////////////////////////////////////////////////////////
// Display.h - Build catalog of files, show results                          //
//                                                                           //
// Application:   Project #1, CSE687 - Object Oriented Design, Spring 2014   //
// Platform:      Dell XPS 2720, Win 8.1, Visual Studio 2013                 //
// Author:        Jim Fawcett, CST 4-187, Syracuse University                //
//                (315) 443-3948, jfawcett@twcny.rr.com                      //
///////////////////////////////////////////////////////////////////////////////
/*
* Package Operations:
* -------------------
* Display uses the services of Catalog and FileSystem directly and also indirectly
* depends on DataStore, FileMgr, and Utilities.
* - Parses commandline, passed by Executive, and sets patterns and path in Catalog.
* - Builds a catalog of file information from a directory tree rooted at a specified path,
*   using the Catalog package.
* - Displays filenames and paths of duplicate files found in the catalog.
* - Finds all files in the catalog containing a specified text string.
* - Supports repeated queries for files containing specified text after building catalog.
*
* User Interface:
* - Display.exe path [/s][/a][/d][/f<text>][/q][/c][/h][/?]
*   s, // recurse into subdirectories
*   a, // show all files
*   d, // report duplicates
*   f, // find text
*   q, // query for text at end of execution
*   c, // display commandline arguments - used for testing
*   h  // display usage message
*   ?  // display usage message
*
* Required Files:
* ---------------
* Display.h, Display.cpp, Catalog.h, Catalog.cpp, FileSystem.h, FileSystem.cpp
* DataStore.h, DataStore.cpp, FileMgr.h, FileMgr.cpp, 
* Utilities.h, Utilities.cpp
*
* Build Process:
* --------------
* From the Visual Studio Developer's Command Prompt:
* devenv VSHelp.sln /rebuild debug
*
* Maintenance History:
* --------------------
* - Ver 1.0 : 1 Mar 2015
*   first release
*/

#include "../Catalog/Catalog.h"
#include <map>
#include <vector>
#include <string>

class Display
{
public:
  enum Option {
    s, // recurse into subdirectories
    a, // show all files
    d, // report duplicates
    f, // find text
    q, // query for text at end of execution
    c, // display commandline arguments - used for testing
    h  // display usage message
  };
  Display(int argc, char* argv[], Catalog& cat);
  void showCommandLine(bool vertical=true);
  bool parseCommandLine();
  void showResults();
  void showUsage();
  bool optionEnabled(enum Option opt);
  void textQuery(const std::string& query);
  std::string& searchText();
  std::vector<std::string> getPatterns();
private:
  bool parseError;
  int argc_;
  char** argv_;
  Catalog& cat_;
  std::map<Option, bool> optionState_;
  std::vector<std::string> patterns_;
  std::string path_;
  std::string searchText_;
};

inline std::string& Display::searchText()
{
  return searchText_;
}

inline std::vector<std::string> Display::getPatterns()
{
  return patterns_;
}
#endif
