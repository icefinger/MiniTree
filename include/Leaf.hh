#ifndef __minitree_leaf__
#define __minitree_leaf__

#include <BasicDataMgr.hh>

namespace icedcode
{
  class Tree;
  class Leaf;

  class RootLeaf
  {
  public:
    Leaf ();
    Leaf (const Tree* aTree, const RawData& aRawData);
    ~Leaf () {}

    const Tree* GetTree () const {return fTree;}
    const RawData& GetRawData () const {return fLeafRemainingData;}

    void SetRawData (const RawData& aRawData) {fLeafRemainingData=aRawData;}

    void GetDaugtherLeafs (const Leaf* aLowLeaf, const Leaf* aHighLeaf) const;
    void SetDaugtherLeafs (const Leaf* aLowLeaf, const Leaf* aHighLeaf);

  protected:
    const Tree* fTree;
    RawData fLeafRemainingData;

    const Leaf* fLowDautherLeaf = 0;
    const Leaf* fHighDautherLeaf = 0;

  };

  class Leaf: public RootLeaf
  {
  public:
    Leaf (const Leaf* aMotherLeaf, const Tree* aTree, const RawData& aRawData);
    ~Leaf () {}

    const Leaf* GetMotherLeaf () const {return fMotherLeaf;}
    float GetChi2 () const {return fChi2;}

  protected:
    const Leaf* fMotherLeaf = 0;

    float fMotherLeafCuttedParameter;
    float fMotherLeafCutValue;
    float fChi2=-1;
  };

}
#endif
