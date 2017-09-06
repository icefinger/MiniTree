#include <BasicDataMgr.hh>
#include <LeafFactory.hh>

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

  BasicDataMgr bdm;
  bdm.OpenFile (InputFileName.data ());
  bdm.ReadData ();
  bdm.Dump ();

  Leaf** LeafColl = LeafFactory::GetIt ()->CreateDaugherLeafs (bdm.GetRootRawData ());
  cout << "Leafs chi2 " << LeafColl[0]->GetChi2 () << endl;
  LeafColl[0]->GetRawData ().Dump ();
  LeafColl[1]->GetRawData ().Dump ();
  cout << "-----------------------------"<< endl;
  Leaf** FirstLeafDauther = LeafFactory::GetIt ()->CreateDaugherLeafs (LeafColl[1]->GetRawData());
  cout << LeafColl[1]->GetChi2() << endl;
  cout << FirstLeafDauther[1]->GetChi2() << endl;
  FirstLeafDauther[0]->GetRawData ().Dump ();
  FirstLeafDauther[1]->GetRawData ().Dump ();
 return 0;

}
