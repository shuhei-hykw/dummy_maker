/**
 *  file: DetectorManager.hh
 *  date: 2016.01.28
 *
 */

#include "DetectorManager.hh"

#include <iostream>

DetectorManager *DetectorManager::m_detector_manager = 0;

static const std::string class_name("DetectorManager");

//_____________________________________________________________________
DetectorManager::DetectorManager( void )
{
}

//_____________________________________________________________________
DetectorManager::~DetectorManager( void )
{
}

//_____________________________________________________________________
DetectorManager&
DetectorManager::GetInstance( void )
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");
  if( !m_detector_manager )
    m_detector_manager = new DetectorManager;
  return *m_detector_manager;
}

//_____________________________________________________________________
bool
DetectorManager::Initialize( void )
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");

  std::cout << "#D " << func_name << std::endl;

  m_detector_list.clear();

  double e; // energy resolution
  double t; // time resolution

  RegisterDetector( new Detector( "SDC1", e=0., t=0. ) );
  RegisterDetector( new Detector( "SDC2", e=0., t=0. ) );
  RegisterDetector( new Detector( "SDC3", e=0., t=0. ) );
  RegisterDetector( new Detector( "TOF",  e=0., t=0. ) );

  PrintDetectorList();

  return true;
}

//_____________________________________________________________________
Detector*
DetectorManager::GetDetector( const std::string& name )
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");

  if( m_detector_list.count( name ) ){
    return m_detector_list[name];
  }else{
    std::cout << "#W " << func_name << " "
	      << "cannot find detector : " << name << std::endl;
    return 0;
  }
}

//_____________________________________________________________________
bool
DetectorManager::RegisterDetector( Detector* detector )
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");

  std::string detector_name = detector->GetDetectorName();

  if( m_detector_list.count( detector_name ) ){
    std::cout << "#W " << func_name << " "
	      << " already added : " << detector_name << std::endl;
    return false;
  }

  m_detector_list[detector_name] = detector;
  return true;
}

//_____________________________________________________________________
void
DetectorManager::PrintDetectorList( void )
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");

  // std::cout << "#D " << func_name << std::endl;
  std::cout //<< "   \t\t     Resolutions" << std::endl
	    << "   [name]\t[MeV]\t[ns]" << std::endl;
  for( DetectorListIterator itr=m_detector_list.begin(),
	 itr_end=m_detector_list.end(); itr!=itr_end; ++itr ){
    std::cout << "   " << itr->second->GetDetectorName() << "   \t"
	      << itr->second->GetEnergyResolution() << "\t"
	      << itr->second->GetTimeResolution() << "\t" << std::endl;
  }
}

