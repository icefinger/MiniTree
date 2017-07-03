#include <DataMgr.hh>
#include <cstring>

using namespace std;

namespace icedcode
{

  DataMgr::DataMgr () {}
  DataMgr::~DataMgr () {}

  bool DataMgr::OpenFile (const char* aFile)
  {
    fInputFstream.open (aFile);
    return fInputFstream.is_open ();
  }

  void DataMgr::RawData::GetParameterValuesFromEntry (size_t aEntryNb, vector <float>& aValueList) const
  {
    aValueList.clear ();
    aValueList.resize (fValueEntrySize);
    size_t position = aEntryNb*(fValueEntrySize-1);
    memcpy(&(aValueList[0]), &(fParametersValues[position]), fValueEntrySize*sizeof (float));
  }

  list <float> DataMgr::RawData::GetOrderedParametersValues (size_t aPositionInEntries) const
  {
    list <float> toreturn;
    for (size_t it = aPositionInEntries; it < fParametersValues.size (); it+=GetNumberOfParameters ())
      {
        toreturn.push_back (fParametersValues[it]);
      }
    toreturn.sort ();
    return toreturn;
  }

}
