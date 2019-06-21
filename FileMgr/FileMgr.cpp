/////////////////////////////////////////////////////////////////////////////////////////
// FileMgr.cpp - Find all files on specified path or tree matching specified patterns  //
//                                                                                     //
// Application:   Project #1, CSE687 - Object Oriented Design, Spring 2014             //
// Platform:      Dell XPS 2720, Win 8.1, Visual Studio 2013                           //
// Author:        Jim Fawcett, CST 4-187, Syracuse University                          //
//                (315) 443-3948, jfawcett@twcny.rr.com                                //
/////////////////////////////////////////////////////////////////////////////////////////

#include "FileMgr.h"
#include "FileSystem.h"
//#include "../DataStore/DataStore.h"
#define STATIC_LIB
#include "../Utilities/Utilities.h"
#include <iostream>
#include <string>

FileMgr::FileMgr(const std::string& path, DataStore& ds) : path_(path), store_(ds)
{
  patterns_.push_back("*.*");
}

bool FileMgr::changePath(const std::string& path)
{
  if (FileSystem::Directory::exists(path))
  {
    path_ = path;
    return true;
  }
  return false;
}

void FileMgr::addPattern(const std::string& patt)
{
  if (patterns_.size() == 1 && patterns_[0] == "*.*")
    patterns_.pop_back();
  patterns_.push_back(patt);
}

void FileMgr::search(bool recurse)
{
  std::string fullPath = FileSystem::Path::getFullFileSpec(path_);
  if (recurse)
    find(fullPath);
  else
  {
    for (auto patt : patterns_)
    {
      std::vector<std::string> files = FileSystem::Directory::getFiles(fullPath, patt);
      for (auto file : files)
      {
        store_.save(file, fullPath);
      }
    }
  }
}

void FileMgr::find(const std::string& path)
{
  //std::cout << "\n-- finding on path " << path;
  for (auto patt : patterns_)
  {
    std::vector<std::string> files = FileSystem::Directory::getFiles(path, patt);
    for (auto f : files)
    {
      //std::cout << "\n  -- saving file: " << f << ", on path: " << path;
      std::string fileSpec = path + "\\" + f;
      FileSystem::FileInfo fi(fileSpec);
      std::string date = fi.date();
      store_.save(f, path);
    }
  }
  std::vector<std::string> subdirs = FileSystem::Directory::getDirectories(path);
  for (auto d : subdirs)
  {
    if (d != "." && d != "..")
    {
      //std::cout << "\n  -- found dir: " << d;
      find(path + "\\" + d);
    }
  }
}

#ifdef TEST_FILEMGR

int main()
{
  title("Testing FileMgr", '=');
  std::cout << "\n";

  DataStore ds;
  FileMgr fm("../..", ds);

  title("Non-recursive search");
  fm.search();
  for (auto fs : ds)
  {
    std::string file = fs.first;
    std::cout << "\n  " << file;
    DataStore::PathCollection pc = ds.getPaths(file);
    for (auto path : pc)
    {
      std::cout << "\n    " << path;
    }
    ///////////////////////////////////
    // This works too:
    //  for (auto iter : fs.second)
    //  {
    //    std::cout << "\n    " << *iter;
    //  }
  }
  std::cout << "\n";

  title("Recursive search");
  fm.search(true);
  for (auto fs : ds)
  {
    std::string file = fs.first;
    std::cout << "\n  " << file;
    DataStore::PathCollection pc = ds.getPaths(file);
    for (auto path : pc)
    {
      std::cout << "\n    " << path;
    }
  }
  std::cout << "\n\n";
  return 0;
}

#endif
