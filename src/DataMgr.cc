#include <DataMgr.hh>

namespace icedcode
{

  bool DataMgr::OpenFile (const char* aFile)
  {
    fInputFstream.open (aFile);
    return fInputFstream.is_open ();
  }


  list <float> DataMgr::RawData::GetOrderedParametersValues (size_t aPositionInEntries)
  {
    list <float> toreturn;
    for (size_t it = 0; it < fParametersValues.size (); fParametersValues+=fParametersNames.size  ())
      {
        toreturn.push_back (fParametersValues[it]);
      }
    toreturn.sort ();
    return toreturn;
  }

}
