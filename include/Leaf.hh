#ifndef __minitree_leaf__
#define __minitree_leaf__

#include <BasicDataMgr.hh>
#include <DataMgr.hh>
#include <limits>

namespace icedcode
{
  class Tree;
  class Leaf;

  class RootLeaf
  {
  public:
    RootLeaf ();
    RootLeaf (const Tree* aTree, const DataMgr::RawData& aRawData);
    ~RootLeaf () {}

    const Tree* GetTree () const {return fTree;}
    const DataMgr::RawData& GetRawData () const {return fLeafRemainingData;}

    void SetRawData (const DataMgr::RawData& aRawData) {fLeafRemainingData=aRawData;}

    void GetDaugtherLeafs (const Leaf*& aLowLeaf, const Leaf*& aHighLeaf) const;
    void SetDaugtherLeafs (const Leaf* aLowLeaf, const Leaf* aHighLeaf);

  protected:
    const Tree* fTree;
    DataMgr::RawData fLeafRemainingData;

    const Leaf* fLowDautherLeaf = 0;
    const Leaf* fHighDautherLeaf = 0;

  };

  class Leaf: public RootLeaf
  {
  public:
    Leaf (const Leaf* aMotherLeaf, const Tree* aTree, const DataMgr::RawData& aRawData);
    Leaf ();
    ~Leaf () {}

    const Leaf* GetMotherLeaf () const {return fMotherLeaf;}
    void SetChi2 (float aChi2) {fChi2=aChi2;}
    float GetChi2 () const {return fChi2;}

    void SetCutValue (float aCut) {fCut=aCut;}
    float GetCutValue () const {return fCut;}

    size_t GetCuttedParameterPosition () {return fCuttedPar;}
    void SetCuttedParameterPosition (size_t aCuttedPar) {fCuttedPar = aCuttedPar;}

    const std::string& GetCuttedParameterName () {return fCuttedName;}
    void SetCuttedParameterName   (const std::string& aCuttedName) {fCuttedName = aCuttedName;}

  protected:
    const Leaf* fMotherLeaf = 0;

    float fMotherLeafCuttedParameter;
    float fMotherLeafCutValue;
    float fChi2=-1;
    float fCut=std::numeric_limits<float>::min();
    size_t fCuttedPar=-1;
    std::string fCuttedName;
  };

}
#endif
