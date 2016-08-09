/**
 *  file: DetectorManager.hh
 *  date: 2016.02.01
 *
 */

#ifndef DETECTOR_MANAGER_HH
#define DETECTOR_MANAGER_HH

#include "TypeDef.hh"

#include <iterator>
#include <map>
#include <string>
#include <vector>

class Detector;

//_____________________________________________________________________
class Detector
{
public:
  Detector( const std::string& name,
	    double energy_resolution = 0.,
	    double time_resolution   = 0. )
    : m_detector_name(name),
      m_energy_resolution(energy_resolution),
      m_time_resolution(time_resolution)
  {
  }
  ~Detector( void )
  {
  }

private:
  std::string m_detector_name;
  double      m_energy_resolution;
  double      m_time_resolution;

public:
  std::string GetDetectorName( void )     const { return m_detector_name; }
  double      GetEnergyResolution( void ) const { return m_energy_resolution; }
  double      GetTimeResolution( void )   const { return m_time_resolution; }
};

//_____________________________________________________________________
class DetectorManager
{
public:
  static DetectorManager& GetInstance( void );
  ~DetectorManager( void );

private:
  explicit DetectorManager( void );
  DetectorManager( const DetectorManager& );
  DetectorManager& operator =( const DetectorManager& );

private:
  static DetectorManager *m_detector_manager;
  DetectorList            m_detector_list;

public:
  bool      Initialize( void );
  Detector* GetDetector( const std::string& name );
  bool      RegisterDetector( Detector* detector );
  void      PrintDetectorList( void );

};

#endif
