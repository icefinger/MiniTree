#ifndef __minitree_leaffactory__
#define __minitree_leaffactory__

#include <Leaf.hh>

namespace icedcode
{
  class LeafFactory
  {
  public:
    LeafFactory* GetIt ();

    Leaf** CreateDaugherLeafs (const DataMgr::RawData& aRawData);
    Leaf** GetParameterBestLeaf (size_t aPositionInEntries, const DataMgr::RawData& aRawData);

  private:
    LeafFactory ();
    ~LeafFactory ();

    void __GenerateRawData (const DataMgr::RawData& aRawData, size_t aParPosition, float aCutValue, DataMgr::RawData* newRawDatas);
    float __Chi2Calculator (const DataMgr::RawData& aRawData, size_t aPositionInEntries, float aCutValue);

    static LeafFactory* fInstance;

  };
}

#endif
