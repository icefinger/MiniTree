#ifndef __minitree_leaffactory__
#define __minitree_leaffactory__

#include <Leaf.hh>

namespace icedcode
{
  class LeafFactory
  {
  public:
    LeafFactory* GetIt ();

  private:
    LeafFactory ();
    ~LeafFactory ();

    float __Chi2Calculator (const RawData DataMgr::aRawData, float aCutValue);

    static LeafFactory* fInstance;

  };
}

#endif
