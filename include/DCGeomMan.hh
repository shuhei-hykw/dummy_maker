/*
 *  DCGeomMan.hh
 */

#ifndef DC_GEOM_MAN_HH
#define DC_GEOM_MAN_HH

#include "ThreeVector.hh"
#include <string>
#include <vector>
#include <map>

class DCGeomRecord;

//______________________________________________________________________________
class DCGeomMan 
{
private:
  DCGeomMan();
public:
  ~DCGeomMan();

private:
  typedef std::map <int, DCGeomRecord *> DCGeomContainer;

  enum e_default_id { k_tof_id=51, k_lc_id=54 };
  static DCGeomMan*       m_geom_manager;
  std::string             m_file_name;
  mutable DCGeomContainer m_geom_container;
  int                     m_tof_id;
  int                     m_lc_id;

public:
  void                SetFileName( const char *file_name );
  void                SetFileName( const std::string &file_name );
  bool                Initialize( void );
  bool                Initialize( const char *file_name );
  bool                Initialize( const std::string& file_name );
  static DCGeomMan&   GetInstance( void );
  double              GetLocalZ( int lnum ) const;
  double              GetResolution( int lnum ) const;
  // Do not use this method except for special cases
  void                SetResolution( int lnum, double res ) const;
  //
  double              GetTiltAngle( int lnum ) const;
  double              GetRotAngle1( int lnum ) const;
  double              GetRotAngle2( int lnum ) const;
  double              GetdXdW( int lnum ) const;
  const ThreeVector&  GetGlobalPosition( int lnum ) const;
  ThreeVector         NormalVector( int lnum ) const;
  ThreeVector         UnitVector( int lnum ) const;
  const DCGeomRecord* GetRecord( int lnum ) const;

  ThreeVector         Local2GlobalPos( int lnum, const ThreeVector &in ) const;
  ThreeVector         Global2LocalPos( int lnum, const ThreeVector &in ) const;
  ThreeVector         Local2GlobalDir( int lnum, const ThreeVector &in ) const;
  ThreeVector         Global2LocalDir( int lnum, const ThreeVector &in ) const;

  double              calcWirePosition( int lnum, double wire ) const;
  int                 calcWireNumber( int lnum, double position ) const;
  std::vector<int>    GetDetectorIDList( void ) const;
  int                 GetTofId( void ) const { return m_tof_id; }
  int                 GetLcId( void ) const { return m_lc_id; }
  int                 GetDetectorId( const std::string &detName ) const;

private:
  void clearElements( void );
};

#endif
