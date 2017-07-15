#include <BasicDataMgr.hh>

using namespace std;

namespace icedcode
{
  BasicDataMgr::BasicDataMgr () {}
  BasicDataMgr::~BasicDataMgr () {}


  //TODO optimize the reading
  bool BasicDataMgr::ReadData ()
  {
    if (!CheckFile ())
      return false;

    size_t nb_param;
    //the first line should give the number of parameters
    fInputFstream >> nb_param;
    //the next line contains the parameter titles
    size_t counter=0;
    string paramname;
    vector <string> ParametersNames;
    while (counter++ < nb_param && fInputFstream >> paramname)
      {
        ParametersNames.push_back (paramname);
      }
    //adding the title for the result of each line
    ParametersNames.push_back ("outcome");

    fRootRawData.SetParameterNames (ParametersNames);
    //then filling it
    counter = 0;
    float tmp;
    vector <float> Entry;
    while (fInputFstream >> tmp)
      {
        Entry.push_back (tmp);
        if (Entry.size () % fRootRawData.GetNumberOfParameters () == 0)
          {
            fRootRawData.AddEntry (Entry);
            Entry.clear ();
          }
      }

    if (Entry.size ())
      return false;

    return true;
  }


}
