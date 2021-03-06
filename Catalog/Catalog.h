#ifndef CATALOG_H
#define CATALOG_H
///////////////////////////////////////////////////////////////////////////////
// Catalog.h - Build catalog of files, show results                          //
// Ver 1.1                                                                   //
// Application:   Project #1, CSE687 - Object Oriented Design, Spring 2014   //
// Platform:      Dell XPS 2720, Win 8.1, Visual Studio 2013                 //
// Author:        Jim Fawcett, CST 4-187, Syracuse University                //
//                (315) 443-3948, jfawcett@twcny.rr.com                      //
///////////////////////////////////////////////////////////////////////////////
/*
 * Package Operations:
 * -------------------
 * Catalog uses the services of DataStore, FileMgr, and FileSystem to efficiently
 * build a catalog of file and directory information.
 * - Builds a catalog of file information from a directory tree rooted at a specified path.
 * - Stores each filename and path only once.
 * - Displays filenames and paths of duplicate files found in the catalog.
 * - Finds all files in the catalog containing a specified text string.
 * - Supports repeated queries for files containing specified text after building catalog.
 *
 * User Interface:
 * - Catalog.exe path [/s][/a][/d][/f<text>][/q][/c][/h][/?]
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
 * Catalog.h, Catalog.cpp, DataStore.h, DataStore.cpp, 
 * FileMgr.h, FileMgr.cpp, FileSystem.h, FileSystem.cpp, 
 * Utilities.h, Utilities.cpp
 *
 * Build Process:
 * --------------
 * From the Visual Studio Developer's Command Prompt:
 * devenv VSHelp.sln /rebuild debug
 *
 * Maintenance History:
 * --------------------
 * Ver 1.1 : 08 Aug 2018
 * - added date to DataStore map, which changed showDuplicates and showSearchResults
 * Ver 1.0 : 01 Mar 2015
 * - first release
 */

#include "../DataStore/DataStore.h"
#include "../FileMgr/FileMgr.h"
#define STATIC_LIB  // comment this statement if you build Utilities as a DLL
#include "../Utilities/Utilities.h"

class Catalog
{
public:
  Catalog(const std::string& path=".") : path_(path), store_(DataStore()), fileManager_(path, store_) {}
  bool changePath(const std::string& path);
  void addPattern(const std::string& pattern);
  void buildCatalog(bool recurse=false);
  void showFiles();
  void showDuplicates();
  void showSearchResults(const std::string& searchString);
  void showSummary();
private:
  std::string path_;
  std::string searchString_ = "";
  DataStore store_;
  FileMgr fileManager_;
  bool textSearch(const std::string& filespec, const std::string& text);
};

inline void Catalog::addPattern(const std::string& pattern)
{
  fileManager_.addPattern(pattern);
}
#endif
