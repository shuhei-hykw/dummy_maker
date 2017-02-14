/**
 *  file: DCGeomMan.hh
 *  date: 2017.01.16
 *
 */

#ifndef DC_GEOM_MAN_HH
#define DC_GEOM_MAN_HH

#include "ThreeVector.hh"
#include <string>
#include <vector>
#include <map>

class DCGeomRecord;

//_____________________________________________________________________
class DCGeomMan
{
public:
  ~DCGeomMan( void );
  static DCGeomMan& GetInstance( void );

private:
  DCGeomMan( void );

private:
  typedef std::map <int, DCGeomRecord *> DCGeomContainer;
  static DCGeomMan*       m_geom_manager;
  std::string             m_file_name;
  mutable DCGeomContainer m_geom_container;

public:
  void                SetFileName( const char *file_name );
  void                SetFileName( const std::string &file_name );
  bool                Initialize( void );
  bool                Initialize( const char *file_name );
  bool                Initialize( const std::string& file_name );
  double              GetLocalZ( int lnum ) const;
  double              GetLocalZ( const std::string& det_name ) const;
  double              GetResolution( int lnum ) const;
  double              GetResolution( const std::string& det_name ) const;
  double              GetTiltAngle( int lnum ) const;
  double              GetTiltAngle( const std::string& det_name ) const;
  double              GetRotAngle1( int lnum ) const;
  double              GetRotAngle1( const std::string& det_name ) const;
  double              GetRotAngle2( int lnum ) const;
  double              GetRotAngle2( const std::string& det_name ) const;
  const ThreeVector&  GetGlobalPosition( int lnum ) const;
  const ThreeVector&  GetGlobalPosition( const std::string& det_name ) const;
  ThreeVector         NormalVector( int lnum ) const;
  ThreeVector         NormalVector( const std::string& det_name ) const;
  ThreeVector         UnitVector( int lnum ) const;
  ThreeVector         UnitVector( const std::string& det_name ) const;
  const DCGeomRecord* GetRecord( int lnum ) const;
  const DCGeomRecord* GetRecord( const std::string& det_name ) const;
  ThreeVector         Local2GlobalPos( int lnum, const ThreeVector &in ) const;
  ThreeVector         Local2GlobalPos( const std::string& det_name, const ThreeVector &in ) const;
  ThreeVector         Global2LocalPos( int lnum, const ThreeVector &in ) const;
  ThreeVector         Global2LocalPos( const std::string& det_name, const ThreeVector &in ) const;
  ThreeVector         Local2GlobalDir( int lnum, const ThreeVector &in ) const;
  ThreeVector         Local2GlobalDir( const std::string& det_name, const ThreeVector &in ) const;
  ThreeVector         Global2LocalDir( int lnum, const ThreeVector &in ) const;
  ThreeVector         Global2LocalDir( const std::string& det_name, const ThreeVector &in ) const;
  double              CalcWirePosition( int lnum, double wire ) const;
  double              CalcWirePosition( const std::string& det_name, double wire ) const;
  int                 CalcWireNumber( int lnum, double position ) const;
  int                 CalcWireNumber( const std::string& det_name, double position ) const;
  std::vector<int>    GetDetectorIDList( void ) const;
  int                 GetDetectorId( const std::string &det_name ) const;
  // Do not use this method except for special cases
  void                SetResolution( int lnum, double res ) const;
  void                SetResolution( const std::string& det_name, double res ) const;
  //

private:
  void ClearElements( void );
};

#endif
