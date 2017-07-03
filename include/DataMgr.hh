#ifndef __minitree_datamgr__
#define __minitree_datamgr__

#include <map>
#include <list>
#include <utility>
#include <fstream>
#include <vector>
#include <fstream>

namespace icedcode
{
  class DataMgr
  {
  public:
    class RawData
    {
    public:
      RawData () {}
      ~RawData () {}

      size_t GetAbsolutePosition (const std::string& aParName) const;
      size_t GetPositionInEntry (const std::string& aParName) const;
      size_t GetNumberOfEntries () const;
      size_t GetNumberOfParameters () const;
      std::pair <float,float> GetValueLimitsOfParamater (const std::string& aParName, size_t aEntryNb) const;
      std::pair <float,float> GetValueLimitsOfParamater (size_t aPositionInEntries, size_t aEntryNb) const;

      float GetValueInEntry (const std::string& aParName, size_t aEntryNb) const;
      float GetValueInEntry (size_t aPositionInEntries, size_t aEntryNb) const;

      void SetParameterNames (const std::vector <std::string>& aParNameList);
      void AddEntry (const std::vector <float>& aValueList);

      std::list <float> GetOrderedParametersValues (size_t aPositionInEntries) const;

      const std::vector<std::string>& GetParameterNames () const {return fParametersNames;}
      const std::vector<float>& GetParameterValues () const {return fParametersValues;}
      void GetParameterValuesFromEntry (size_t aEntryNb, std::vector <float>& aValueList) const;

    protected:
      std::vector <std::string> fParametersNames;
      std::vector <float>  fParametersValues;
      std::vector <std::pair <float, float>> fParametersValuesLimits;

      size_t fValueEntrySize =1;
    };

      DataMgr ();
    ~DataMgr ();

     virtual bool OpenFile (const char* aFile);
     virtual bool CheckFile () = 0;
     virtual bool ReadData () = 0;

  protected:
    std::ifstream fInputFstream;
    RawData fRootRawData;
  };





}





#endif
