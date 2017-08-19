#include <DataMgr.hh>

#include <cstring>
#include <limits>
#include <iostream>

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

  size_t DataMgr::RawData::GetPositionInEntry (const string& aParName) const
  {
    for (size_t i=0; i<fParametersNames.size (); i++)
      if (fParametersNames [i] == aParName)
        return i;
    return string::npos;
  }

  size_t DataMgr::RawData::GetNumberOfEntries () const
  {
    return fParametersValues.size () / fParametersNames.size ();
  }

  size_t DataMgr::RawData::GetNumberOfParameters () const
  {
    return fParametersNames.size ();
  }

  void DataMgr::RawData::GetParameterValuesFromEntry (size_t aEntryNb, vector <float>& aValueList) const
  {
    aValueList.clear ();
    size_t position = aEntryNb*(GetNumberOfParameters ());
    auto iter = fParametersValues.begin () + position;
    aValueList.assign (iter, iter+GetNumberOfParameters());
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

  float DataMgr::RawData::GetValueInEntry (const std::string& aParName, size_t aEntryNb) const
  {
    size_t PosInEntry = GetPositionInEntry (aParName);
    size_t AbsolutePos = PosInEntry * aEntryNb;
    return GetValueInEntry (AbsolutePos, aEntryNb);
  }

  float DataMgr::RawData::GetValueInEntry (size_t aPositionInEntries, size_t aEntryNb) const
  {
    size_t AbsolutePos = aPositionInEntries * aEntryNb;
    if (AbsolutePos < fParametersValues.size ())
        return fParametersValues [AbsolutePos];
    return numeric_limits<float>::min();
    return fParametersValues [aEntryNb];
  }

  void DataMgr::RawData::SetParameterNames (const vector <string>& aParNameList)
  {
    fParametersNames = aParNameList;
  }

  void DataMgr::RawData::AddEntry (const vector <float>& aValueList)
  {
    fParametersValues.insert (fParametersValues.end (), aValueList.begin (), aValueList.end ());
  }

  void DataMgr::RawData::Dump () const
  {
    for (const auto& sit: fParametersNames)
      cout << sit <<" ";
    int counter=0;
    for (auto fit: fParametersValues) {
      if (counter++ % GetNumberOfParameters () == 0)
        cout << endl;
      cout << fit << " ";
    }
    cout << endl;
  }

}
