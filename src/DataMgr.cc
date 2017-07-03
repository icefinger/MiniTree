#include <DataMgr.hh>

namespace icedcode
{

  DataMgr::DataMgr () {}
  DataMgr::~DataMgr () {}

  bool DataMgr::OpenFile (const char* aFile)
  {
    fInputFstream.open (aFile);
    return fInputFstream.is_open ();
  }

  void DataMgr::RawData::GetParameterValuesFromEntry (size_t aEntryNb, vector<float>& aValueList)
  {
    aValueList.clear ();
    aValueList.resize (fValueEntrySize);
    size_t position = aEntryNb*(fValueEntrySize-1);
    memcpy(&(aValueList[0]), &(fParametersValues[position]), fValueEntrySize*sizeof (float));

    return toreturn;
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
