/**
 *  file: DCGeomMan.cc
 *  date: 2017.01.25
 *
 */

#include "DCGeomMan.hh"
#include "DCGeomRecord.hh"

#include <string>
#include <stdexcept>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>
#include <sstream>

static const std::string class_name("DCGeomMan");

DCGeomMan* DCGeomMan::m_geom_manager = 0;

//_____________________________________________________________________
DCGeomMan::DCGeomMan( void )
{
}

//_____________________________________________________________________
DCGeomMan::~DCGeomMan( void )
{
}

//_____________________________________________________________________
void
DCGeomMan::SetFileName( const char* file_name )
{
  m_file_name = file_name;
}

//_____________________________________________________________________
void
DCGeomMan::SetFileName( const std::string& file_name )
{
  m_file_name = file_name;
}

//_____________________________________________________________________
bool
DCGeomMan::Initialize( const char* file_name )
{
  m_file_name = file_name;
  return Initialize();
}

//_____________________________________________________________________
bool
DCGeomMan::Initialize( const std::string& file_name )
{
  m_file_name = file_name;
  return Initialize();
}

//_____________________________________________________________________
DCGeomMan&
DCGeomMan::GetInstance( void )
{
  if( !m_geom_manager )
    m_geom_manager = new DCGeomMan();
  return *m_geom_manager;
}

//_____________________________________________________________________
double
DCGeomMan::GetLocalZ( int lnum ) const
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");
  DCGeomRecord *geom_record = m_geom_container[lnum];
  if( geom_record ){
    return geom_record->Length();
  }else{
    std::cerr << func_name << ": No record. Layer#="
	      << lnum << std::endl;
    throw std::out_of_range(func_name+": No record" );
  }
}

//_____________________________________________________________________
double
DCGeomMan::GetLocalZ( const std::string& det_name ) const
{
  return GetLocalZ( GetDetectorId( det_name ) );
}

//_____________________________________________________________________
double
DCGeomMan::GetResolution( int lnum ) const
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");
  DCGeomRecord *geom_record = m_geom_container[lnum];
  if( geom_record ) return geom_record->Resolution();
  else{
    std::cerr << func_name << ": No record. Layer#="
	      << lnum << std::endl;
    throw std::out_of_range(func_name+": No record" );
  }
}

//_____________________________________________________________________
double
DCGeomMan::GetResolution( const std::string& det_name ) const
{
  return GetResolution( GetDetectorId( det_name ) );
}

//_____________________________________________________________________
double
DCGeomMan::GetTiltAngle( int lnum ) const
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");
  DCGeomRecord *geom_record = m_geom_container[lnum];
  if( geom_record ) return geom_record->TiltAngle();
  else{
    std::cerr << func_name << ": No record. Layer#="
	      << lnum << std::endl;
    throw std::out_of_range(func_name+": No record" );
  }
}

//_____________________________________________________________________
double
DCGeomMan::GetTiltAngle( const std::string& det_name ) const
{
  return GetTiltAngle( GetDetectorId( det_name ) );
}

//_____________________________________________________________________
double
DCGeomMan::GetRotAngle1( int lnum ) const
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");
  DCGeomRecord *geom_record = m_geom_container[lnum];
  if( geom_record ) return geom_record->RotationAngle1();
  else{
    std::cerr << func_name << ": No record. Layer#="
	      << lnum << std::endl;
    throw std::out_of_range(func_name+": No record" );
  }
}

//_____________________________________________________________________
double
DCGeomMan::GetRotAngle1( const std::string& det_name ) const
{
  return GetRotAngle1( GetDetectorId( det_name ) );
}

//_____________________________________________________________________
double
DCGeomMan::GetRotAngle2( int lnum ) const
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");
  DCGeomRecord *geom_record = m_geom_container[lnum];
  if( geom_record ) return geom_record->RotationAngle2();
  else{
    std::cerr << func_name << ": No record. Layer#="
	      << lnum << std::endl;
    throw std::out_of_range(func_name+": No record" );
  }
}

//_____________________________________________________________________
double
DCGeomMan::GetRotAngle2( const std::string& det_name ) const
{
  return GetRotAngle2( GetDetectorId( det_name ) );
}

//_____________________________________________________________________
const ThreeVector&
DCGeomMan::GetGlobalPosition( int lnum ) const
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");
  DCGeomRecord *geom_record = m_geom_container[lnum];
  if( geom_record ) return geom_record->Pos();
  else{
    std::cerr << func_name << ": No record. Layer#="
	      << lnum << std::endl;
    throw std::out_of_range(func_name+": No record" );
  }
}

//_____________________________________________________________________
const ThreeVector&
DCGeomMan::GetGlobalPosition( const std::string& det_name ) const
{
  return GetGlobalPosition( GetDetectorId( det_name ) );
}

//_____________________________________________________________________
ThreeVector
DCGeomMan::NormalVector( int lnum ) const
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");
  DCGeomRecord *geom_record = m_geom_container[lnum];
  if( geom_record ) return geom_record->NormalVector();
  else{
    std::cerr << func_name << ": No record. Layer#="
	      << lnum << std::endl;
    throw std::out_of_range(func_name+": No record" );
  }
}

//_____________________________________________________________________
ThreeVector
DCGeomMan::NormalVector( const std::string& det_name ) const
{
  return NormalVector( GetDetectorId( det_name ) );
}

//_____________________________________________________________________
ThreeVector
DCGeomMan::UnitVector( int lnum ) const
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");
  DCGeomRecord *geom_record = m_geom_container[lnum];
  if( geom_record ) return geom_record->UnitVector();
  else{
    std::cerr << func_name << ": No record. Layer#="
	      << lnum << std::endl;
    throw std::out_of_range(func_name+": No record" );
  }
}

//_____________________________________________________________________
ThreeVector
DCGeomMan::UnitVector( const std::string& det_name ) const
{
  return UnitVector( GetDetectorId( det_name ) );
}

//_____________________________________________________________________
const DCGeomRecord*
DCGeomMan::GetRecord( int lnum ) const
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");
  DCGeomRecord *geom_record = m_geom_container[lnum];
  if( geom_record ) return geom_record;
  else{
    std::cerr << func_name << ": No record. Layer#="
	      << lnum << std::endl;
    throw std::out_of_range(func_name+": No record" );
  }
}

//_____________________________________________________________________
const DCGeomRecord*
DCGeomMan::GetRecord( const std::string& det_name ) const
{
  return GetRecord( GetDetectorId( det_name ) );
}

//_____________________________________________________________________
double
DCGeomMan::CalcWirePosition( int lnum, double wire ) const
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");
  DCGeomRecord *geom_record = m_geom_container[lnum];
  if( geom_record ){
    return geom_record->WirePos(wire);
  }
  else{
    std::cerr << func_name << ": No record. Layer#="
	      << lnum << std::endl;
    throw std::out_of_range(func_name+": No record" );
  }
}

//_____________________________________________________________________
double
DCGeomMan::CalcWirePosition( const std::string& det_name, double wire ) const
{
  return CalcWirePosition( GetDetectorId( det_name ), wire );
}

//_____________________________________________________________________
int
DCGeomMan::CalcWireNumber( int lnum, double pos ) const
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");
  DCGeomRecord *geom_record = m_geom_container[lnum];
  if( geom_record ){
    return geom_record->WireNumber(pos);
  }
  else{
    std::cerr << func_name << ": No record. Layer#="
	      << lnum << std::endl;
    throw std::out_of_range(func_name+": No record" );
  }
}

//_____________________________________________________________________
int
DCGeomMan::CalcWireNumber( const std::string& det_name, double wire ) const
{
  return CalcWireNumber( GetDetectorId( det_name ), wire );
}

//_____________________________________________________________________
void
DCGeomMan::ClearElements( void )
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");
  //  for_each( m_geom_container.begin(), m_geom_container.end(), DeleteObject() );
  std::map <int, DCGeomRecord *>::iterator itr;
  for( itr=m_geom_container.begin(); itr!=m_geom_container.end(); ++itr ){
    delete itr->second;
  }
  m_geom_container.clear();
}

//_____________________________________________________________________
bool
DCGeomMan::Initialize( void )
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");

  std::ifstream f(m_file_name.c_str());
  if( !f.is_open() ){
    std::cerr << "#E " << func_name
	      << " file open fail : " << m_file_name << std::endl;
    std::exit(EXIT_FAILURE);
  }

  ClearElements();

  std::string line;
  while( !f.eof() && std::getline( f, line ) ){
    if( line.empty() || line[0]=='#' ) continue;
    std::istringstream input_line( line );
    int id; std::string name;
    double xs, ys, zs, ta, ra1, ra2, l, res, w0, dd, ofs;
    if( input_line >> id >> name >> xs >> ys >> zs >> ta >> ra1 >> ra2
	>> l >> res >> w0 >> dd >> ofs ){
      DCGeomRecord *geom_record =
	new DCGeomRecord( id, name, xs, ys, zs, ta, ra1, ra2,
			  l, res, w0, dd, ofs );
      DCGeomRecord *pre_record = m_geom_container[id];
      m_geom_container[id] = geom_record;

      if( pre_record ){
	std::cerr << func_name << ": duplicated id number. "
		  << " following record is deleted." << std::endl;
	std::cerr << "Id=" << pre_record->Id() << " ("
		  << pre_record->Pos().X() << ", "
		  << pre_record->Pos().Y() << ", "
		  << pre_record->Pos().Z() << " ) ... " << std::endl;
	delete pre_record;
      }
    }else{
      std::cerr << "#E " << func_name << " "
		<< "invalid format : " << line << std::endl;
    }
  }

  std::cout << func_name << " Initialized" << std::endl;

  return true;
}

//_____________________________________________________________________
std::vector<int>
DCGeomMan::GetDetectorIDList( void ) const
{
  std::vector<int> vlist;
  vlist.reserve(m_geom_container.size());
  std::map <int, DCGeomRecord *>::const_iterator
    itr=m_geom_container.begin(), end=m_geom_container.end();

  for(; itr!=end; ++itr ){
    vlist.push_back( itr->first );
  }

  return vlist;
}

//_____________________________________________________________________
ThreeVector
DCGeomMan::Local2GlobalPos( int lnum, const ThreeVector& in ) const
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");

  DCGeomRecord *geom_record = m_geom_container[lnum];
  if( !geom_record )
    throw std::out_of_range(func_name+": No record" );

  double x = geom_record->dxds()*in.x() + geom_record->dxdt()*in.y()
    + geom_record->dxdu()*in.z() + geom_record->Pos().x();
  double y = geom_record->dyds()*in.x() + geom_record->dydt()*in.y()
    + geom_record->dydu()*in.z() + geom_record->Pos().y();
  double z = geom_record->dzds()*in.x() + geom_record->dzdt()*in.y()
    + geom_record->dzdu()*in.z() + geom_record->Pos().z();

  return ThreeVector( x, y, z );
}

//_____________________________________________________________________
ThreeVector
DCGeomMan::Local2GlobalPos( const std::string& det_name, const ThreeVector& in ) const
{
  return Local2GlobalPos( GetDetectorId( det_name ), in );
}

//_____________________________________________________________________
ThreeVector
DCGeomMan::Global2LocalPos( int lnum, const ThreeVector& in ) const
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");

  DCGeomRecord *geom_record = m_geom_container[lnum];
  if( !geom_record ){
    std::cerr << func_name << ": No record. Layer#="
	      << lnum << std::endl;
    throw std::out_of_range(func_name+": No record" );
  }

  double x
    = geom_record->dsdx()*(in.x()-geom_record->Pos().x())
    + geom_record->dsdy()*(in.y()-geom_record->Pos().y())
    + geom_record->dsdz()*(in.z()-geom_record->Pos().z());
  double y
    = geom_record->dtdx()*(in.x()-geom_record->Pos().x())
    + geom_record->dtdy()*(in.y()-geom_record->Pos().y())
    + geom_record->dtdz()*(in.z()-geom_record->Pos().z());
  double z
    = geom_record->dudx()*(in.x()-geom_record->Pos().x())
    + geom_record->dudy()*(in.y()-geom_record->Pos().y())
    + geom_record->dudz()*(in.z()-geom_record->Pos().z());

  return ThreeVector( x, y, z );
}

//_____________________________________________________________________
ThreeVector
DCGeomMan::Global2LocalPos( const std::string& det_name, const ThreeVector& in ) const
{
  return Global2LocalPos( GetDetectorId( det_name ), in );
}

//_____________________________________________________________________
ThreeVector
DCGeomMan::Local2GlobalDir( int lnum, const ThreeVector& in ) const
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");

  DCGeomRecord *geom_record = m_geom_container[lnum];
  if( !geom_record ){
    std::cerr << func_name << ": No record. Layer#="
	      << lnum << std::endl;
    throw std::out_of_range(func_name+": No record" );
  }

  double x = geom_record->dxds()*in.x() + geom_record->dxdt()*in.y()
    + geom_record->dxdu()*in.z();
  double y = geom_record->dyds()*in.x() + geom_record->dydt()*in.y()
    + geom_record->dydu()*in.z();
  double z = geom_record->dzds()*in.x() + geom_record->dzdt()*in.y()
    + geom_record->dzdu()*in.z();

  return ThreeVector( x, y, z );
}

//_____________________________________________________________________
ThreeVector
DCGeomMan::Local2GlobalDir( const std::string& det_name, const ThreeVector& in ) const
{
  return Local2GlobalDir( GetDetectorId( det_name ), in );
}

//_____________________________________________________________________
ThreeVector
DCGeomMan::Global2LocalDir( int lnum, const ThreeVector& in ) const
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");

  DCGeomRecord *geom_record = m_geom_container[lnum];
  if( !geom_record ){
    std::cerr << func_name << ": No record. Layer#="
	      << lnum << std::endl;
    throw std::out_of_range(func_name+": No record" );
  }

  double x = geom_record->dsdx()*in.x() + geom_record->dsdy()*in.y()
    + geom_record->dsdz()*in.z();
  double y = geom_record->dtdx()*in.x() + geom_record->dtdy()*in.y()
    + geom_record->dtdz()*in.z();
  double z = geom_record->dudx()*in.x() + geom_record->dudy()*in.y()
    + geom_record->dudz()*in.z();

  return ThreeVector( x, y, z );
}

//_____________________________________________________________________
ThreeVector
DCGeomMan::Global2LocalDir( const std::string& det_name, const ThreeVector& in ) const
{
  return Global2LocalDir( GetDetectorId( det_name ), in );
}

//_____________________________________________________________________
void
DCGeomMan::SetResolution( int lnum, double res ) const
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");
  DCGeomRecord *geom_record = m_geom_container[lnum];
  if( geom_record ) {
    geom_record->SetResolution( res );
    return;
  }
  else{
    std::cerr << func_name << ": No record. Layer#="
              << lnum << std::endl;
    throw std::out_of_range(func_name+": No record" );
  }
}

//_____________________________________________________________________
void
DCGeomMan::SetResolution( const std::string& det_name, double res ) const
{
  SetResolution( GetDetectorId( det_name ), res );
}

//_____________________________________________________________________
int
DCGeomMan::GetDetectorId( const std::string &det_name ) const
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");

  std::map <int, DCGeomRecord *>::const_iterator
    itr,
    itr_begin = m_geom_container.begin(),
    itr_end   = m_geom_container.end();

  for( itr=itr_begin; itr!=itr_end; ++itr ){
    if ( itr->second->Name() == det_name )
      return itr->second->Id();
  }

  std::cerr << func_name << " : No such detector " << det_name << std::endl;
  std::exit(EXIT_FAILURE);
}
