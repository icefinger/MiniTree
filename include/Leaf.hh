#ifndef __minitree_leaf__
#define __minitree_leaf__

#include <BasicDataMgr.hh>

namespace icedcode
{
  class Tree;

  class RootLeaf
  {
  public:
    Leaf (const Tree* aTree, const RawData& aRawData);
    ~Leaf () {}

    const Tree* GetTree () const {return fTree;}
    const RawData& GetRawData () const {return fLeafRemainingData;}

  protected:
    const Tree* fTree;
    RawData fLeafRemainingData;
  };

  class Leaf: public RootLeaf
  {
  public:
    Leaf (const Leaf* aMotherLeaf, const Tree* aTree, const RawData& aRawData);
    ~Leaf () {}

    const Leaf* GetMotherLeaf () const {return fMotherLeaf;}
    void GetDaugtherLeafs (const Leaf* aLowLeaf, const Leaf* aHighLeaf) const;
    void SetDaugtherLeafs (const Leaf* aLowLeaf, const Leaf* aHighLeaf);
    float GetChi2 () const {return fChi2;}

  protected:
    const Leaf* fMotherLeaf = 0;
    const Leaf* fLowDautherLeaf = 0;
    const Leaf* fHighDautherLeaf = 0;

    float fCutValue;
    float fChi2=-1;
  };

}
#endif
