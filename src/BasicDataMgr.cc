#include <BasicDataMgr.hh>

using namespace std;

namespace icedcode
{

  //TODO optimize the reading
  bool BasicDataMgr::ReadData ()
  {
    if (!CheckFile ())
      return false;

    size_t nb_param;
    //the first line should give the number of parameters
    fInputFstream >> nb_param;
    //the next line contains the parameter titles
    int counter=0;
    string paramname;
    while (counter++ < nb_param && fInputFstream >> paramname)
      {
        fParametersNames.push_back (paramname);
      }
    fParametersNames.push_back ("outcome");

    //then filling it
    counter = 0;
    float tmp;
    while (fInputFstream >> tmp)
      {
        fParametersValues.push_back (tmp);
      }

    if (fParametersValues.size () % fParametersNames.size ())
      return false;
    return true;
  }


}
