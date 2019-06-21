///////////////////////////////////////////////////////////////////////////////
// Executive.cpp - Entry point for Project #1 Demo                           //
// Ver 1.1                                                                   //
// Application:   Project #1, CSE687 - Object Oriented Design, Spring 2014   //
// Platform:      Dell XPS 2720, Win 8.1, Visual Studio 2013                 //
// Author:        Jim Fawcett, CST 4-187, Syracuse University                //
//                (315) 443-3948, jfawcett@twcny.rr.com                      //
///////////////////////////////////////////////////////////////////////////////
/*
 * Package Operations:
 * -------------------
 * - Builds a catalog of file information from a directory tree rooted at a specified path.
 * - Stores each filename and path only once.
 * - Displays filenames and paths of duplicate files found in the catalog.
 * - Finds all files in the catalog containing a specified text string.
 * - Supports repeated queries for files containing specified text after building catalog.
 *
 * User Interface:
 * - Executive.exe path [/s][/a][/d][/f<text>][/q][/c][/h][/?]
 *   s, // recurse into subdirectories
 *   a, // show all files
 *   d, // report duplicates
 *   f, // find text
 *   q, // query for text at end of execution
 *   c, // display commandline arguments - used for testing
 *   h  // display usage message
 *   ?  // display usage message
 * Note: path must be first argument on command line.  There are no other placement constraints.
 *
 * Typical usage: "../.." *.h /s /f"#define" *.cpp /a /d /h /q
 *
 * Required Files:
 * ---------------
 * Executive.cpp, Catalog.h, Catalog.cpp, DataStore.h, DataStore.cpp, Display.h, Display.cpp,
 * FileMgr.h, FileMgr.cpp, FileSystem.h, FileSystem.cpp, Utilities.h, Utilities.cpp
 *
 * Build Process:
 * --------------
 * From the Visual Studio Developer's Command Prompt:
 * devenv VSHelp.sln
 * Note:
 *   Most of these packages use the Utilities built as a static library or dll.
 *   You may have to run devenv VSHelp.sln twice to successfully build the 
 *   Executive.
 *
 * Maintenance History:
 * --------------------
 * Ver 1.1 : 04 Aug 2018
 * - added reporting file date to display
 *   required mods to Catalog and DataStore
 * Ver 1.0 : 01 Mar 2015
 * - first release
 */
#include "../Catalog/Catalog.h"
#include "../Display/Display.h"
#include <iostream>
#include <memory>

class Executive
{
public:
  Executive(int argc, char** argv);
  Executive(const Executive& ex) = delete;
  Executive& operator=(const Executive& ex) = delete;
  void processCommands();
private:
  std::unique_ptr<Catalog> pCatalog_ = nullptr;
  std::unique_ptr<Display> pDisplay_ = nullptr;
};

Executive::Executive(int argc, char** argv)
{
  std::string path;
  if (argc > 1 && argv[1][0] != '/')
    path = argv[1];
  else
    path = ".";

  pCatalog_ = std::unique_ptr<Catalog>(new Catalog(path));
  pDisplay_ = std::unique_ptr<Display>(new Display(argc, argv, *pCatalog_));
}

void Executive::processCommands()
{
  bool verticalArrangement = false;
  pDisplay_->showCommandLine(verticalArrangement);
  if (pDisplay_->parseCommandLine())
    std::cout << "\n  commandline parse succeeded";
  std::cout << "\n";

  pCatalog_->buildCatalog(pDisplay_->optionEnabled(pDisplay_->s));
  title("Showing results based on commandline arguments:");
  pDisplay_->showResults();
  std::cout << "\n\n";
}

int main(int argc, char* argv[])
{
  title("Project #1 Demonstration:", '=');
  std::cout << "\n";

  Executive exec(argc, argv);
  exec.processCommands();
}