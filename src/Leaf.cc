#include <Leaf.hh>

namespace icedcode
{
  RootLeaf::RootLeaf (Tree* aTree, const RawData& aRawData)
  {
    fTree = aTree;
    fLeafRemainingData = aRawData;
  }

  Leaf::Leaf (const Leaf* aMotherLeaf, Tree *aTree, const RawData& aRawData): RootLeaf (aTree,aRawData)
  {

  }

  void Leaf::GetDaugtherLeafs (const Leaf* aLowLeaf, const Leaf* aHighLeaf)
  {
    aLowleaf=fLowDautherLeaf;
    aHighLeaf=fHighDautherLeaf;
  }

  void Leaf::SetDaugtherLeafs (const Leaf* aLowLeaf, const Leaf* aHighLeaf)
  {
    fLowDautherLeaf = aLowleaf;
    fHighDautherLea = aHighLeaf;
  }


}
