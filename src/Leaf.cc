#include <Leaf.hh>

namespace icedcode
{
  RootLeaf::RootLeaf (const Tree* aTree, const DataMgr::RawData& aRawData)
  {
    fTree = aTree;
    fLeafRemainingData = aRawData;
  }

  void RootLeaf::GetDaugtherLeafs (const Leaf*& aLowLeaf, const Leaf*& aHighLeaf) const
  {
    aLowLeaf=fLowDautherLeaf;
    aHighLeaf=fHighDautherLeaf;
  }

  void RootLeaf::SetDaugtherLeafs (const Leaf* aLowLeaf, const Leaf* aHighLeaf)
  {
    fLowDautherLeaf = aLowLeaf;
    fHighDautherLeaf = aHighLeaf;
  }


  Leaf::Leaf (const Leaf* aMotherLeaf, const Tree *aTree, const DataMgr::RawData& aRawData): RootLeaf (aTree,aRawData)
  {
    fMotherLeaf = aMotherLeaf;
  }

  Leaf::Leaf () {}

}
