/**
 *  file: TypeDef.hh
 *  date: 2016.02.01
 *
 */

#ifndef TYPE_DEF_HH
#define TYPE_DEF_HH

#include <iterator>
#include <map>
#include <vector>

class DAQNode;
class DAQModule;
class Detector;

typedef std::vector<DAQNode*>           NodeContainer;
typedef std::vector<DAQModule*>         ModuleContainer;
typedef std::vector<unsigned int>       DataWord;
typedef NodeContainer::const_iterator   NodeIterator;
typedef ModuleContainer::const_iterator ModuleIterator;
typedef DataWord::const_iterator        DataWordIterator;

typedef std::map<std::string, DAQNode*>   NodeList;
typedef std::map<std::string, DAQModule*> ModuleList;
typedef std::map<std::string, Detector*>  DetectorList;
typedef NodeList::const_iterator          NodeListIterator;
typedef ModuleList::const_iterator        ModuleListIterator;
typedef DetectorList::const_iterator      DetectorListIterator;

#endif
