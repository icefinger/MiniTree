#include <LeafFactory.hh>

namespace icedcode
{
  LeafFactory* LeafFactory::fInstance = 0;

  LeafFactory::LeafFactory ()
  {
  }

  LeafFactory::~LeafFactory ()
  {
  }

  LeafFactory* LeafFactory::GetIt ()
  {
    if (!fInstance)
      fInstance = new LeafFactory;
    return fInstance;
  }

  Leaf** LeafFactory::CreateDaugherLeafs (const RawData& aRawData)
  {
    Leaf** overallBestLeafs = GetParameterBestLeaf (0, aRawData);

    for (size_t it=1 ; it<aRawData.GetNumberOfParameters () ; it++)
      {
        Leaf** bestLeaf = GetParameterBestLeaf (it, aRawData);
        if (overallBestLeaf != 0 || overallBestLeaf[0]->GetChi2 () < bestLeaf[0]->GetChi2 ())
          {
            delete overallBestLeaf[0];
            delete overallBestLeaf[1];
            delete overallBestLeaf;

            overallBestLeaf = bestLeaf;
          }
        else
          {
            delete bestLeaf[0];
            delete bestLeaf[1];
            delete bestLeaf;
          }

      }

    size_t cutParPos = overallBestLeafs[0]->GetCuttedParameterPositon ();
    float cutParVal  = overallBestLeafs[0]->GetCutValue ();

    DataMgr::RawData LeafRawDatas[2];
    __GenerateRawData (aRawData, curParPos, cutParVal, LeafRawDatas);
    overallBestLeafs[0]->SetRawData (LeafRawDatas[0]);
    overallBestLeafs[1]->SetRawData (LeafRawDatas[1]);

    return overallBestLeafs;

  }

  Leaf** LeafFactory::GetParameterBestLeaf (size_t aPositionInEntries, const DataMgr::RawData& aRawData)
  {
    pair <float, float> limits = aRawData.GetValueLimitsOfParamater (aPositionInEntries);
    list <float> orderedValues=aRawData.GetOrderedParametersValues (aPositionInEntries);
    float previous_value=std::numeric_limits<float>::min();

    float cut, chi2,
      maxcut=std::numeric_limits<float>::min(), maxchi2=std::numeric_limits<float>::min();

    for (auto val: orderedValues)
      {
        if (previous_value == std::numeric_limits<float>::min())
          continue;
        cut = (val-previous_value)/2;
        chi2=__Chi2Calculator (aPositionInEntries, aRawData,);
        if (chi2 > maxcut)
          {
            maxcut=cut;
            maxchi2 = chi2;
          }
        previous_value = val;
      }

    DataMgr::RawData LeafRawData[2];
    Leaf** toreturn = (Leaf**)(malloc (2*sizeof(Leaf**)));
    toreturn[0]=new Leaf ();
    toreturn[1]=new Leaf ();

    toreturn[0]->SetChi2 (maxchi2);
    toreturn[0]->SetCut (maxcut);
    toreturn[1]->SetChi2 (maxchi2);
    toreturn[1]->SetCut (maxcut);

    return toreturn;
  }

  void LeafFactory::__GenerateRawData (const DataMgr::RawData& aRawData, size_t aParPosition, float aCutValue, DataMgr::RawData* newRawDatas)
  {
    vector <string> paramNames = aRawData.GetParameterNames ();
    paramNames.erase (paramNames.begin () + aParPosition);
    newRawDatas[0].SetParameterNames (paramNames);
    newRawDatas[1].SetParameterNames (paramNames);

    vector <float> theEntryValues;

    for (size_t it=0 ; it<aRawData.GetNumberOfEntries () ; it++)
      {
        aRawData.GetParameterValuesFromEntry(aParPosition, theEntryValues);
        theEntryValues.erase (theEntryValues.begin ());

        float value = aRawData.GetValueInEntry (aParPosition, it);
        if (value < aCutValue)
          {
            newRawDatas[0].AddEntry (theEntryValues);
          }
        else
          {
            newRawDatas[1].AddEntry (theEntryValues);
          }
      }
  }

  float LeafFactory::__Chi2Calculator  (const DataMgr::RawData& aRawData, size_t aParPosition, float aCutValue)
  {

    float n11=0;
    float n12=0;
    for (size_t it=0 ; it<aRawData.GetNumberOfEntries () ; it++)
      {
        float value = aRawData.GetValueInEntry (aParPosition, it);
        if (value < aCutValue)
          n11+=value;
        else
          n21+=value;
      }
    float nproduct1 = 2*n11+n12;
    float nproduct2 = 2*n12+n11;
    float chi2 = pow (n11 - nproduct1, 2)/nproduct1 + pow (n12 - nproduct2)/nproduct2;
    chi2/=2*(n11+n21);
    return chi2;
  }
}
