#include <BasicDataMgr.hh>
#include <Tree.hh>

#include <fstream>
#include <iostream>
#include <string>

using namespace std;
using namespace icedcode;

int main (int argc, char **argv)
{
  string InputFileName;

  if (argc < 2) {
    cerr << "give at least a data file name." << endl;
    return 0;
  }

  for (int i = 1; i<argc; i++) {
    if (!InputFileName.size ())
      InputFileName = argv [i];
  }

  Tree* theTree = Tree::CreateTreeFromFile (InputFileName, new BasicDataMgr);
  theTree->Dump ();

 return 0;

}
