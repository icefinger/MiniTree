#ifndef __minitree_leaffactory__
#define __minitree_leaffactory__

#include <Leaf.hh>

namespace icedcode
{
  class LeafFactory
  {
  public:
    static LeafFactory* GetIt ();

    Leaf** CreateDaugherLeafs (const DataMgr::RawData& aRawData);
    Leaf** GetParameterBestLeaf (size_t aPositionInEntries, const DataMgr::RawData& aRawData);

    void SetMinimumChi2(float aChi2) {fMinimumChi2=aChi2;}
    float GetMinimumChi2() const {return fMinimumChi2;}

    void SetMinimumNumberOfParameters(float aNumberOfParameters) {fMinimumNumberOfParameters=aNumberOfParameters;}
    float GetMinimumNumberOfParameters() const {return fMinimumNumberOfParameters;}

  private:
    LeafFactory ();
    ~LeafFactory ();

    DataMgr::RawData** __GenerateRawData (const DataMgr::RawData& aRawData, size_t aMotherParPosition, float aCutValue);
    float __Chi2Calculator (const DataMgr::RawData& aRawData, size_t aPositionInEntries, float aCutValue);

    size_t fMinimumNumberOfParameters = 2;
    size_t fMinimumChi2 = 0;


    static LeafFactory* fInstance;

  };
}

#endif
