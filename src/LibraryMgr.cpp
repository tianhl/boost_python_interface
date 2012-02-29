#include <iostream>

#include "../inc/LibraryMgr.h"

#include <Poco/Path.h>
#include <Poco/File.h>
#include <Poco/DirectoryIterator.h>
#include <boost/algorithm/string.hpp>

const std::string DllOpen::LIB_PREFIX = "lib";
const std::string DllOpen::LIB_POSTFIX = ".so";
const std::string DllOpen::PATH_SEPERATOR = "/";

void* DllOpen::OpenDll(const std::string& libName)
{
  std::string str = LIB_PREFIX + libName + LIB_POSTFIX;
  return OpenDllImpl(str);
}

void* DllOpen::OpenDll(const std::string& libName, const std::string& filePath)
{
  std::string str = filePath + PATH_SEPERATOR + LIB_PREFIX + libName
    + LIB_POSTFIX;
  return OpenDllImpl(str);
}


const std::string DllOpen::ConvertToLibName(const std::string& fileName)
{
  std::string retVal = fileName;
  if ((retVal.find(LIB_PREFIX) == 0 ) && (retVal.find(PATH_SEPERATOR) == std::string::npos)) 
    retVal = retVal.substr(LIB_PREFIX.size(), retVal.size() - LIB_PREFIX.size());
  else return "";

  std::string::size_type pos = retVal.rfind(LIB_POSTFIX);
  if ( pos != std::string::npos && pos == (retVal.size()-LIB_POSTFIX.size()) )
    retVal = retVal.substr(0, retVal.size()-LIB_POSTFIX.size());
  else return "";

  return retVal;
}

void* DllOpen::OpenDllImpl(const std::string& filePath)
{
  void* handle = dlopen(filePath.c_str(), RTLD_NOW | RTLD_GLOBAL);
  if (!handle) std::cout << "Could not open library " << filePath <<  ": " << dlerror()<< std::endl;
  return handle;
}



/** Opens all suitable DLLs on a given path.
 *  @param filePath :: The filepath to the directory where the libraries are.
 *  @param isRecursive :: Whether to search subdirectories.
 *  @return The number of libraries opened.
 */
int LibraryMgr::OpenAllLibraries(const std::string& filePath)
{
  int libCount = 0;
  //validate inputs
  Poco::File libPath = Poco::File(filePath);

  if ( libPath.exists() && libPath.isDirectory() ) {
    DllOpen::addSearchDirectory(filePath);
    // Iteratate over the available files
    Poco::DirectoryIterator end_itr;
    for (Poco::DirectoryIterator itr(libPath); itr != end_itr; ++itr) {
      const Poco::Path & item = itr.path();
      if (( !item.isDirectory() )&& ( loadLibrary(item.toString())))  {
	++libCount;
      }
    }
  }
  else {
    std::cout << "In OpenAllLibraries: " <<  filePath << " must be a directory."<< std::endl;
  }

  return libCount;
}

//-------------------------------------------------------------------------
// Private members
//-------------------------------------------------------------------------
/** 
 * Load a library
 * @param filepath :: The full path to a library as a string
 */
bool LibraryMgr::loadLibrary(const std::string & filepath)
{
  // Get the name of the library.
  std::string libName = DllOpen::ConvertToLibName(Poco::Path(filepath).getFileName());
  if( libName.empty() ) return false;
  // The wrapper will unload the library when it is deleted
  boost::shared_ptr<LibraryWrapper> dlwrap(new LibraryWrapper);
  std::string libNameLower = boost::algorithm::to_lower_copy(libName);

  //Check that a libray with this name has not already been loaded
  if (libs_map.find(libNameLower) == libs_map.end()) {
    Poco::Path directory(filepath);
    directory.makeParent();
    //Try to open the library
    if (dlwrap->OpenLibrary(libName, directory.toString())) {
      //Successfully opened, so add to map
      libs_map.insert(std::pair< std::string, boost::shared_ptr<LibraryWrapper> >(libName, dlwrap) );
      return true;
    }
    else {
      return false;
    }
  }
  else {
    std::cout << libName << " already opened, skipping load\n" << std::endl;
  }
  return false;
}



/** Opens a DLL.
 *  @param libName :: The name of the file to open (not including the lib/so/dll).
 *  @return True if DLL is opened or already open.
 */
bool LibraryWrapper::OpenLibrary(const std::string& libName)
{
  if (!module) {
    module = DllOpen::OpenDll(libName);
    if (!module) {
      return false;
    }
  }
  return true;
}

/** Opens a DLL.
 *  @param libName :: The name of the file to open (not including the lib/so/dll).
 *  @param filePath :: The filepath to the directory where the library is.
 *  @return True if DLL is opened or already open
 */
bool LibraryWrapper::OpenLibrary(const std::string& libName,
    const std::string& filePath)
{
  if (!module) {
    module = DllOpen::OpenDll(libName, filePath);
    if (!module) {
      return false;
    }
  }
  return true;
}


