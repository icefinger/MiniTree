#ifndef __minitree_datamgr__
#define __minitree_datamgr__

#include <map>
#include <fstream>
#include <vector>

namespace icedcode
{
  class DataMgr
  {
  public:
    class RawData
    {
    public:
      RawData () {}
      RawData () {}

      size_t GetAbsolutePosition (const string& aParName) const;
      size_t GetPositionInEntry (const string& aParName) const;
      size_t GetNumberOfEntries () const;
      size_t GetNumberOfParameters () const;
      pair <float,float> GetValueLimitsOfParamater (const string& aParName, size_t aEntryNb) const;
      pair <float,float> GetValueLimitsOfParamater (size_t aPositionInEntries, size_t aEntryNb) const;

      float GetValueInEntry (const string& aParName, size_t aEntryNb) const;
      float GetValueInEntry (size_t aPositionInEntries, size_t aEntryNb) const;

      void SetParameterNames (const vector <string>& aParNameList);
      void AddEntry (const vector <float>& aValueList);

      list <float> GetOrderedParametersValues (size_t aPositionInEntries);

      const vector<string>& GetParameterNames () const {return fParametersNames;}
      const vector<float>& GetParameterValues () const {return fParametersValues;}
      void GetParameterValuesFromEntry (size_t aEntryNb, vector <float>& aValueList) const;

    protected:
      vector <string> fParametersNames;
      vector <float>  fParametersValues;
      vector <pair <float, float> fParametersValuesLimits;

      size_t fValueEntrySize =1;
    }

      DataMgr ();
    ~DataMgr ();

     virtual bool OpenFile (const char* aFile);
     virtual bool CheckFile () = 0;
     virtual bool ReadData () = 0;

  protected:
    ifstream fInputFstream;
    RawData fRawData;
  };





}





#endif
