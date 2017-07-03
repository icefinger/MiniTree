#ifndef __minitree_basicdatamgr__
#define __minitree_basicdatamgr__
#include <DataMgr.hh>

namespace icedcode
{
  class BasicDataMgr: public DataMgr
  {
  public:
    BasicDataMgr ();
    ~BasicDataMgr ();

    virtual bool CheckFile () {return fInputFstream.is_open ();}
    virtual bool ReadData ();

  };

}



#endif
