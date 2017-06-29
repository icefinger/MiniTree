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

  Leaf* LeafFactory::CreateALeaf (const RawData& aRawData)
  {
    Leaf* overallBestLeaf = 0;
    for (size_t it=0 ; it<aRawData.GetNumberOfParameters () ; it++)
      {
        Leaf* bestLeaf = GetParameterBestLeaf (it, aRawData);
        if (overallBestLeaf == 0 || overallBestLeaf->GetChi2 () < bestLeaf.GetChi2 ())
          {
            if (overallBestLeaf == 0)
              delete overallBestLeaf;
            overallBestLeaf = bestLeaf;
          }
        else
          delete bestLeaf;
      }
  }

  Leaf* LeafFactory::GetParameterBestLeaf (size_t aPositionInEntries, const DataMgr::RawData& aRawData)
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

    DataMgr::RawData LeafRawData = aRawData;
    LeafRawData.RemoveParameter (aPositionInEntries);
    Leaf* toreturn = new Leaf(LeafRawData);
    toreturn->SetChi2 (maxchi2);
    toreturn->SetCut (maxcut);
    return toreturn;

  }

  float LeafFactory::__Chi2Calculator  (const DataMgr::RawData aRawData, const string& aParName, float aCutValue)
  {
    size_t ParPosition = aRawData.GetPosition (aParName);
    if (aRawData.GetPosition (aParName) == 0xffffffffffffffff)
      return 0;


    float n11=0;
    float n12=0;
    for (size_t it=0 ; it<aRawData.GetNumberOfEntries () ; it++)
      {
        float value = aRawData.GetValueInEntry (ParPosition, it);
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
