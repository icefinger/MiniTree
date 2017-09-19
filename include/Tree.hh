#ifndef __minitree_tree__
#define __minitree_tree__

#include <string>
#include <vector>

namespace icedcode
{
  class DataMgr;
  class Leaf;

  class Tree
  {
  private:
    Tree ();
  public:
    typedef std::vector<std::vector<Leaf*>> LeafMatrix_t;

    ~Tree ();

    static Tree* CreateTreeFromFile (std::string aFileName, DataMgr* aDataManager=0);
    void SetDataManager (DataMgr* aDataManager) {fDataManager = aDataManager;}
    const DataMgr* GetDataManager () {return fDataManager;}

    void Dump ();

  private:
    void CreateRootLeafs ();
    void GenerateFullTree ();
  protected:
    DataMgr* fDataManager=0;

    LeafMatrix_t fLeafMatrix; //[level][parameter]

  };


}


#endif
