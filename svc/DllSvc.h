#ifndef LIBRARY_MANAGER_H
#define LIBRARY_MANAGER_H

//----------------------------------------------------------------------
// Includes
//----------------------------------------------------------------------
#include <string>
#include <map>
#include <boost/shared_ptr.hpp>

#include <string>
#include <iostream>

#include <dlfcn.h>

#include "../inc/SingletionHolder.h"
#include "../inc/IInterface.h"

#define UNUSED_ARG(x) (void)x

class DllOpen {
  public:
    /// Static method for opening the shared library
    static void* OpenDll(const std::string&);

    /// Static method for opening the shared library
    static void* OpenDll(const std::string&, const std::string&);

    /// Static method for retrieving a function pointer
    static void* GetFunction(void* libName, const std::string& funcName){
      return GetFunctionImpl(libName, funcName);
    };

    /// Static method for closing the shared library
    static void CloseDll(void* libName){ CloseDllImpl(libName);};

    /// Static method for converting a filename to a libName (without lib___.so or ___.dll)
    static const std::string ConvertToLibName(const std::string&);

    /// Adds a directiry to the dll search path.
    static void addSearchDirectory(const std::string& dir){addSearchDirectoryImpl(dir);};

  private:
    /// Constructor private as not needed
    DllOpen() {};
    /// Copy operator private as not needed
    DllOpen(const DllOpen &) {};
    ///Destructor private as not needed	
    ~DllOpen() {};

    //private functions specific to implementation
    /// Implementation specifc static method for opening a shared library
    static void* OpenDllImpl(const std::string&);

    /// Implementation specifc static method for retrieving a function pointer
    static void* GetFunctionImpl(void* libName, const std::string& funcName){ 
      return dlsym(libName, funcName.c_str());
    };

    /// Implementation specifc static method for closing a shared library
    static void CloseDllImpl(void* libName){UNUSED_ARG(libName);};
    // Commented out for now due to a potential bug in glibc
    //{dlclose(libName);};

    /// Implementation specifc static method for adding a directiry to the dll search path.
    static void addSearchDirectoryImpl(const std::string& dir){UNUSED_ARG(dir);};

    ///lib prefix
    static const std::string LIB_PREFIX;
    ///lib postfix
    static const std::string LIB_POSTFIX;
    ///path seperator 
    static const std::string PATH_SEPERATOR;
};


class LibraryWrapper {
public:
	LibraryWrapper():module(0){};
	virtual ~LibraryWrapper(){
	  if (module) {
	    DllOpen::CloseDll(module);
	    module = 0;
	  }
	};

	//Returns true if DLL is opened or already open
	bool OpenLibrary(const std::string&);

	bool OpenLibrary(const std::string&, const std::string&);

private:
	/** An untyped pointer to the loaded library.
	 * This is created and deleted by this class.
	 **/
	void* module;
};


class LibraryMgr:public IInterface {
  public:
    //opens all suitable libraries on a given path
    int OpenAllLibraries(const std::string&);
    string getName(){return name;};
  private:
    friend struct CreateUsingNew<LibraryMgr>;

    ///Private Constructor
    LibraryMgr():IInterface("LibMgr"){};
    ///// Private copy constructor - NO COPY ALLOWED
    //LibraryMgr(const LibraryMgr&);
    ///// Private assignment operator - NO ASSIGNMENT ALLOWED
    //LibraryManagerImpl& operator = (const LibraryManagerImpl&);
    /////Private Destructor
    //virtual ~LibraryManagerImpl();

    /// Load a given library
    bool loadLibrary(const std::string & filepath);
    ///Storage for the LibraryWrappers.
    std::map< const std::string, boost::shared_ptr<LibraryWrapper> > libs_map;

};

typedef SingletonHolder<LibraryMgr> LibMgr;


#endif //LIBRARY_MANAGER_H
