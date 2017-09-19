#include <Tree.hh>

#include <iostream>
#include <LeafFactory.hh>

using namespace std;

namespace icedcode
{
  Tree::Tree () {}
  Tree::~Tree () {}

  Tree* Tree::CreateTreeFromFile (string aFileName, DataMgr* aDataManager)
  {
    Tree* toreturn = new Tree;

    if (aDataManager != 0)
      {
        toreturn->fDataManager = aDataManager;
      }
    else if (toreturn->fDataManager == 0)
      {
        cerr << "Tree::LoadTreeFromFile:error: no datamanager in the tree!" << endl;
        return 0;
      }

    toreturn->fDataManager->OpenFile(aFileName.data ());

    toreturn->fDataManager->ReadData ();
    toreturn->CreateRootLeafs ();

    toreturn->GenerateFullTree ();

    return toreturn;
  }

  void Tree::CreateRootLeafs ()
  {
    if (!fDataManager || !fDataManager->FileIsOpen ())
      {
        cerr << "Tree::ReadRootData: error: no open file" << endl;
        return;
      }

    Leaf** RootLeafs = LeafFactory::GetIt ()->CreateDaugherLeafs (fDataManager->GetRootRawData ());
    vector<Leaf*> tmpLeafColl;
    tmpLeafColl.push_back (RootLeafs[0]);
    tmpLeafColl.push_back (RootLeafs[1]);
    fLeafMatrix.push_back (tmpLeafColl);
  }
  void Tree::GenerateFullTree ()
  {
    bool hadNoNullDaughters=true;
    while (hadNoNullDaughters)
      {
        vector <Leaf*>& lastLevel = fLeafMatrix.back ();
        vector<Leaf*> tmpLeafColl;
        hadNoNullDaughters=false;
        for (auto& leaf: lastLevel)
          {
            Leaf** daughters=LeafFactory::GetIt ()->CreateDaugherLeafs (leaf->GetRawData());
            if (daughters == 0)
              continue;
            hadNoNullDaughters=true;
            tmpLeafColl.push_back (daughters[0]);
            tmpLeafColl.push_back (daughters[1]);
          }
        if (hadNoNullDaughters)
          fLeafMatrix.push_back (tmpLeafColl);
      }
  }

  void Tree::Dump ()
  {
    size_t TreeNbOfLevels = fLeafMatrix.size ()-1;
    size_t TreeThickness = fLeafMatrix[TreeNbOfLevels].size ();

    for (const auto& Tlevel: fLeafMatrix)
      {
        for (const auto& Tpar: Tlevel)
          cout << Tpar->GetCuttedParameterName ()<< " " << Tpar->GetChi2 () << endl;
        cout << endl;
      }
  }

}
