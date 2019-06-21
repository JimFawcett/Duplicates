///////////////////////////////////////////////////////////////////////////////
// DataStore.cpp - Efficiently store file and path information from Dir tree //
// Ver 1.1                                                                   //
// Application:   Project #1, CSE687 - Object Oriented Design, Spring 2014   //
// Platform:      Dell XPS 2720, Win 8.1, Visual Studio 2013                 //
// Author:        Jim Fawcett, CST 4-187, Syracuse University                //
//                (315) 443-3948, jfawcett@twcny.rr.com                      //
///////////////////////////////////////////////////////////////////////////////

#include "DataStore.h"
// comment out the definition below to use utilities dll instead of static lib
#define STATIC_LIB
#include "../FileMgr/FileSystem.h"
#include "../Utilities/Utilities.h"
#include <iostream>

void DataStore::save(const std::string& fileSpec)
{
  /* not implemented yet */
}
//----< save filename and its path in DataStore >----------------------------

void DataStore::save(const std::string& filename, const std::string& path)
{
  PathIter iter = paths.find(path);
  if (iter == paths.end())
    iter = paths.insert(path).first;

  std::string fileSpec = path + "\\" + filename;
  FileSystem::FileInfo fi(fileSpec);
  std::string date = fi.date();
  Item item = { iter, date };

  if (store.find(filename) != store.end())
  {
    store[filename].push_back(item);
  }
  else
  {
    ListOfItems list;
    list.push_back(item);
    store[filename] = list;
  }
}
//----< return set of paths on which files were found >----------------------

DataStore::PathCollection DataStore::getPaths(const File& file)
{
  PathCollection paths;
  DataStore::iterator iter = store.find(file);
  if (iter == store.end())
    return paths;
  ListOfItems items = store[file];
  for (auto item : items)
    paths.push_back(*item.first);
  return paths;
}
//----< test stub >----------------------------------------------------------

#ifdef TEST_DATASTORE

#include "../Utilities/Utilities.h"

int main()
{
  title("Testing DataStore");

  DataStore ds;
  ds.save("firstFile","firstPath");
  ds.save("secondFile", "firstPath");
  ds.save("secondFile", "secondPath");

  std::cout << "\n  " << ds.numberOfFiles() << " Files in " << ds.numberOfPaths() << " directories\n";

  for (auto item : ds)
  {
    std::cout << "\n  " << (item).first.c_str()/* << " on " << (item).second.c_str()*/;
    DataStore::PathCollection paths = ds.getPaths(item.first);
    for (auto path : paths)
      std::cout << "\n    " << path;
  }
  std::cout << "\n\n";
}

#endif
