#include "../svc/LogSvc.h"
#include "../svc/CfgSvc.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;


CfgSvc::CfgSvc(string name, string parentDebugInfo):IInterface(name) {
  debugInfo = parentDebugInfo + ", " + name;
}

CfgSvc::CfgSvc(string configFile, char** envp):IInterface("CfgSvc") {
  while (envp && *envp) {
    string envEntry = *envp;
    size_t pos = envEntry.find('=');
    if (pos != string::npos) {
      string name = envEntry.substr(0, pos);
      string value = envEntry.substr(pos+1, string::npos);
      envSymbols[name] = value;
      //logDebug(cout << "environment symbol: '" << name << "' = '" << value << "'" << endl);
    }
    ++envp;
  }

  debugInfo = configFile;
  groupStack.push_front(this);

  FILE* in = fopen(configFile.c_str(), "r");
  if (!in) {
    cerr << "CfgSvcure file '" << configFile << "' don't exist !!" << endl;
    exit(2);
  }

  char buff[1024];
  while (fgets(buff, 1024, in)) {

    string line=buff;
    if ( (line.length() > 2) && (line[0] != '#') && (line.find(')') == string::npos) ) {
      string name;
      string value;
      split(line, name, value, '=');

      if (value == "(") {
	//logDebug(cout << "   config: new group '" << name << "'" << endl);
	CfgSvc* newGroup = new CfgSvc(name, debugInfo);
	groupStack.front()->groups[name] = newGroup;
	groupStack.push_front(newGroup);
      } else {
	for (std::list<CfgSvc*>::reverse_iterator i = groupStack.rbegin(); i != groupStack.rend(); ++i) {
	  (*i)->symbolExpand(value);
	}
	envSymbolExpand(value);
	//logDebug(cout << "   config: name = '" << name << "', value = '" << value << "'" << endl);
	groupStack.front()->add(name, value);
      }
    }
    if ( (line.length() > 0) && (line[0] != '#') && (line.find(')') != string::npos) ) {
      //logDebug(cout << "   end of group" << endl);
      groupStack.pop_front();
    }
  }

  fclose(in);
}

CfgSvc::~CfgSvc() {
  for (map<string, CfgSvc*>::iterator i = groups.begin(); i != groups.end(); ++i) {
    delete i->second;
  }
}

void CfgSvc::add(string name, string value) {
  symbols[name] = value;
}

void CfgSvc::split(string in, string& left, string& right, char c) {
  size_t pos = in.find_first_of(c);
  if(pos == string::npos) {
    left = in;
    trim(left);
    right = "";
  } else if (pos <= 1) {
    left = "";
    right = in.substr(pos+1, string::npos);
    trim(right);
  } else {
    left = in.substr(0, pos-1);
    trim(left);
    right = in.substr(pos+1, string::npos);
    trim(right);
  }
}

void CfgSvc::trim(string& s) {
  while ( (s.length() > 1) && ( (s[0] == ' ') || (s[0] =='\t') ) ) {
    s = s.substr(1, string::npos);
  }
  while ( (s.length() > 1) &&
      ( (s[s.length()-1] == ' ') ||
	(s[s.length()-1] == '\t') || 
	(s[s.length()-1] == '\n') || 
	(s[s.length()-1] == '\r') ) ) {
    s = s.substr(0, s.length()-1);
  }
  if ( (s.length() > 1) && (s[0] == '"') ) {
    s = s.substr(1, string::npos);
  }
  if ( (s.length() > 1) && (s[s.length()-1] == '"') ) {
    s = s.substr(0, s.length()-1);
  }
}

void CfgSvc::symbolExpand(string& s) {
  symbolExpand(symbols, s);
}

void CfgSvc::envSymbolExpand(string& s) {
  symbolExpand(envSymbols, s);
}

void CfgSvc::symbolExpand(map<string, string>& symbols, string& s) {
  bool expanded;
  do {
    expanded = false;
    for (map<string, string>::iterator i = symbols.begin(); i != symbols.end(); ++i) {
      string search = "%" + i->first + "%";
      string replace = i->second;
      size_t pos = s.find(search);
      if (pos != string::npos) {
	expanded = true;
	s.replace(pos, search.length(), replace);
      }
    }
  } while (expanded);
}

string CfgSvc::pString(string name) {
  map<string, string>::iterator i = symbols.find(name);
  if (i == symbols.end()) {
    //logError(cout << "The property '" << name << "' is not defined in '" << debugInfo << "'" << endl);
    exit(4);
  }
  return i->second;
}

bool CfgSvc::pBool(string name) {
  string val = pString(name);

  if ( (val == "yes") ||
      (val == "Yes") ||
      (val == "YES") ||
      (val == "true") ||
      (val == "True") ||
      (val == "TRUE"))
  {
    return true;
  }

  return false;
}

double CfgSvc::pDouble(string name) {
  string val = pString(name);

  return atof(val.c_str());
}

int CfgSvc::pInt(string name) {
  string val = pString(name);

  return atoi(val.c_str());
}
