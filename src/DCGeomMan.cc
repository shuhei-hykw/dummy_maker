/*
 *  DCGeomMan.cc
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

static const std::string classname("DCGeomMan");

const int MaxChar = 200;

DCGeomMan* DCGeomMan::m_geom_manager = 0;

//______________________________________________________________________________
DCGeomMan::DCGeomMan()
  : m_tof_id(k_tof_id),
    m_lc_id(k_lc_id)
{}

//______________________________________________________________________________
DCGeomMan::~DCGeomMan()
{}

//______________________________________________________________________________
void
DCGeomMan::SetFileName( const char* file_name )
{
  m_file_name = file_name;
}

//______________________________________________________________________________
void
DCGeomMan::SetFileName( const std::string& file_name )
{
  m_file_name = file_name;
}

//______________________________________________________________________________
bool
DCGeomMan::Initialize( const char* file_name )
{
  m_file_name = file_name;
  return Initialize();
}

//______________________________________________________________________________
bool
DCGeomMan::Initialize( const std::string& file_name )
{
  m_file_name = file_name;
  return Initialize();
}

//______________________________________________________________________________
DCGeomMan&
DCGeomMan::GetInstance( void )
{
  if( !m_geom_manager ){
    m_geom_manager = new DCGeomMan();
  }
  return *m_geom_manager;
}

//______________________________________________________________________________
double
DCGeomMan::GetLocalZ( int lnum ) const
{
  static const std::string funcname("["+classname+"::"+__func__+"()]");
  DCGeomRecord *geom_record = m_geom_container[lnum];
  if( geom_record ) return geom_record->Length();
  else{
    std::cerr << funcname << ": No record. Layer#="
	      << lnum << std::endl;
    throw std::out_of_range(funcname+": No record" );
  }
}

//______________________________________________________________________________
double
DCGeomMan::GetResolution( int lnum ) const
{
  static const std::string funcname("["+classname+"::"+__func__+"()]");
  DCGeomRecord *geom_record = m_geom_container[lnum];
  if( geom_record ) return geom_record->Resolution();
  else{
    std::cerr << funcname << ": No record. Layer#="
	      << lnum << std::endl;
    throw std::out_of_range(funcname+": No record" );
  }
}

//______________________________________________________________________________
double
DCGeomMan::GetTiltAngle( int lnum ) const
{
  static const std::string funcname("["+classname+"::"+__func__+"()]");
  DCGeomRecord *geom_record = m_geom_container[lnum];
  if( geom_record ) return geom_record->TiltAngle();
  else{
    std::cerr << funcname << ": No record. Layer#="
	      << lnum << std::endl;
    throw std::out_of_range(funcname+": No record" );
  }
}

//______________________________________________________________________________
double
DCGeomMan::GetRotAngle1( int lnum ) const
{
  static const std::string funcname("["+classname+"::"+__func__+"()]");
  DCGeomRecord *geom_record = m_geom_container[lnum];
  if( geom_record ) return geom_record->RotationAngle1();
  else{
    std::cerr << funcname << ": No record. Layer#="
	      << lnum << std::endl;
    throw std::out_of_range(funcname+": No record" );
  }
}

//______________________________________________________________________________
double
DCGeomMan::GetRotAngle2( int lnum ) const
{
  static const std::string funcname("["+classname+"::"+__func__+"()]");
  DCGeomRecord *geom_record = m_geom_container[lnum];
  if( geom_record ) return geom_record->RotationAngle2();
  else{
    std::cerr << funcname << ": No record. Layer#="
	      << lnum << std::endl;
    throw std::out_of_range(funcname+": No record" );
  }
}

//______________________________________________________________________________
double
DCGeomMan::GetdXdW( int lnum ) const
{
  static const std::string funcname("["+classname+"::"+__func__+"()]");
  DCGeomRecord *geom_record = m_geom_container[lnum];
  if( geom_record ) return geom_record->dXdW();
  else{
    std::cerr << funcname << ": No record. Layer#="
	      << lnum << std::endl;
    throw std::out_of_range(funcname+": No record" );
  }
}

//______________________________________________________________________________
const ThreeVector&
DCGeomMan::GetGlobalPosition( int lnum ) const
{
  static const std::string funcname("["+classname+"::"+__func__+"()]");
  DCGeomRecord *geom_record = m_geom_container[lnum];
  if( geom_record ) return geom_record->Pos();
  else{
    std::cerr << funcname << ": No record. Layer#="
	      << lnum << std::endl;
    throw std::out_of_range(funcname+": No record" );
  }
}

//______________________________________________________________________________
ThreeVector
DCGeomMan::NormalVector( int lnum ) const
{
  static const std::string funcname("["+classname+"::"+__func__+"()]");
  DCGeomRecord *geom_record = m_geom_container[lnum];
  if( geom_record ) return geom_record->NormalVector();
  else{
    std::cerr << funcname << ": No record. Layer#="
	      << lnum << std::endl;
    throw std::out_of_range(funcname+": No record" );
  }
}

//______________________________________________________________________________
ThreeVector
DCGeomMan::UnitVector( int lnum ) const
{
  static const std::string funcname("["+classname+"::"+__func__+"()]");
  DCGeomRecord *geom_record = m_geom_container[lnum];
  if( geom_record ) return geom_record->UnitVector();
  else{
    std::cerr << funcname << ": No record. Layer#="
	      << lnum << std::endl;
    throw std::out_of_range(funcname+": No record" );
  }
}

//______________________________________________________________________________
const DCGeomRecord*
DCGeomMan::GetRecord( int lnum ) const
{
  static const std::string funcname("["+classname+"::"+__func__+"()]");
  DCGeomRecord *geom_record = m_geom_container[lnum];
  if( geom_record ) return geom_record;
  else{
    std::cerr << funcname << ": No record. Layer#="
	      << lnum << std::endl;
    throw std::out_of_range(funcname+": No record" );
  }
}

//______________________________________________________________________________
double
DCGeomMan::calcWirePosition( int lnum, double wire ) const
{
  static const std::string funcname("["+classname+"::"+__func__+"()]");
  DCGeomRecord *geom_record = m_geom_container[lnum];
  if( geom_record ){
    return geom_record->WirePos(wire);
  }
  else{
    std::cerr << funcname << ": No record. Layer#="
	      << lnum << std::endl;
    throw std::out_of_range(funcname+": No record" );
  }
}

//______________________________________________________________________________
int
DCGeomMan::calcWireNumber( int lnum, double pos ) const
{
  static const std::string funcname("["+classname+"::"+__func__+"()]");
  DCGeomRecord *geom_record = m_geom_container[lnum];
  if( geom_record ){
    return geom_record->WireNumber(pos);
  }
  else{
    std::cerr << funcname << ": No record. Layer#="
	      << lnum << std::endl;
    throw std::out_of_range(funcname+": No record" );
  }
}

//______________________________________________________________________________
void
DCGeomMan::clearElements( void )
{
  static const std::string funcname("["+classname+"::"+__func__+"()]");
  //  for_each( m_geom_container.begin(), m_geom_container.end(), DeleteObject() );
  std::map <int, DCGeomRecord *>::iterator itr;
  for( itr=m_geom_container.begin(); itr!=m_geom_container.end(); ++itr ){
    delete itr->second;
  }
  m_geom_container.clear();
  m_tof_id = k_tof_id;
}

//______________________________________________________________________________
bool
DCGeomMan::Initialize( void )
{
  static const std::string funcname("["+classname+"::"+__func__+"()]");
  char cname[MaxChar];
  int id;
  double xs, ys, zs, ta, ra1, ra2, l, res, w0, dd, ofs;
  //double A = 0.8/750.;

  std::ifstream f( m_file_name.c_str() );
  if( !f.is_open() ){
    std::cerr << "#E " << funcname
	      << " file open fail : " << m_file_name << std::endl;
    std::exit(EXIT_FAILURE);
  }

  clearElements();

  std::string line;
  while( f.good() && std::getline(f,line) ){
    if( line.empty()||line[0]=='#' ) continue;
    if( sscanf( line.c_str(), "%d %s %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf",
		&id, cname, &xs, &ys, &zs, &ta, &ra1, &ra2, &l, &res,
		&w0, &dd, &ofs ) == 13 ){
      DCGeomRecord *geom_record = new DCGeomRecord( id, cname, xs, ys, zs,
					     ta, ra1, ra2, l, res,
					     w0, dd, ofs );
      DCGeomRecord *pre_record = m_geom_container[id];
      m_geom_container[id] = geom_record;

      if(strcmp(cname,"TOF")==0) m_tof_id = id;

      if( pre_record ){
	std::cerr << funcname << ": duplicated id number. "
		  << " following record is deleted." << std::endl;
	std::cerr << "Id=" << pre_record->Id() << " " << pre_record->Pos()
		  << " ) ... " << std::endl;
	delete pre_record;
      }
    } else {
      std::cerr << funcname << " Invalid format : " << line << std::endl;
    }
  }

  f.close();

  std::cout << funcname << " Initialization finished." << std::endl;

  return true;
}

//______________________________________________________________________________
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

//______________________________________________________________________________
ThreeVector
DCGeomMan::Local2GlobalPos( int lnum, const ThreeVector& in ) const
{
  static const std::string funcname("["+classname+"::"+__func__+"()]");

  DCGeomRecord *geom_record = m_geom_container[lnum];
  if( !geom_record )
    throw std::out_of_range(funcname+": No record" );

  double x = geom_record->dxds()*in.x() + geom_record->dxdt()*in.y()
    + geom_record->dxdu()*in.z() + geom_record->Pos().x();
  double y = geom_record->dyds()*in.x() + geom_record->dydt()*in.y()
    + geom_record->dydu()*in.z() + geom_record->Pos().y();
  double z = geom_record->dzds()*in.x() + geom_record->dzdt()*in.y()
    + geom_record->dzdu()*in.z() + geom_record->Pos().z();

  return ThreeVector( x, y, z );
}

//______________________________________________________________________________
ThreeVector
DCGeomMan::Global2LocalPos( int lnum, const ThreeVector& in ) const
{
  static const std::string funcname("["+classname+"::"+__func__+"()]");

  DCGeomRecord *geom_record = m_geom_container[lnum];
  if( !geom_record ){
    std::cerr << funcname << ": No record. Layer#="
	      << lnum << std::endl;
    throw std::out_of_range(funcname+": No record" );
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

//______________________________________________________________________________
ThreeVector
DCGeomMan::Local2GlobalDir( int lnum, const ThreeVector& in ) const
{
  static const std::string funcname("["+classname+"::"+__func__+"()]");

  DCGeomRecord *geom_record = m_geom_container[lnum];
  if( !geom_record ){
    std::cerr << funcname << ": No record. Layer#="
	      << lnum << std::endl;
    throw std::out_of_range(funcname+": No record" );
  }

  double x = geom_record->dxds()*in.x() + geom_record->dxdt()*in.y()
    + geom_record->dxdu()*in.z();
  double y = geom_record->dyds()*in.x() + geom_record->dydt()*in.y()
    + geom_record->dydu()*in.z();
  double z = geom_record->dzds()*in.x() + geom_record->dzdt()*in.y()
    + geom_record->dzdu()*in.z();

  return ThreeVector( x, y, z );
}

//______________________________________________________________________________
ThreeVector
DCGeomMan::Global2LocalDir( int lnum, const ThreeVector& in ) const
{
  static const std::string funcname("["+classname+"::"+__func__+"()]");

  DCGeomRecord *geom_record = m_geom_container[lnum];
  if( !geom_record ){
    std::cerr << funcname << ": No record. Layer#="
	      << lnum << std::endl;
    throw std::out_of_range(funcname+": No record" );
  }

  double x = geom_record->dsdx()*in.x() + geom_record->dsdy()*in.y()
    + geom_record->dsdz()*in.z();
  double y = geom_record->dtdx()*in.x() + geom_record->dtdy()*in.y()
    + geom_record->dtdz()*in.z();
  double z = geom_record->dudx()*in.x() + geom_record->dudy()*in.y()
    + geom_record->dudz()*in.z();

  return ThreeVector( x, y, z );
}

//______________________________________________________________________________
void
DCGeomMan::SetResolution( int lnum, double res ) const
{
  static const std::string funcname("["+classname+"::"+__func__+"()]");
  DCGeomRecord *geom_record = m_geom_container[lnum];
  if( geom_record ) {
    geom_record->SetResolution( res );
    return;
  }
  else{
    std::cerr << funcname << ": No record. Layer#="
              << lnum << std::endl;
    throw std::out_of_range(funcname+": No record" );
  }
}

//______________________________________________________________________________
int
DCGeomMan::GetDetectorId( const std::string &detName ) const
{
  static const std::string funcname("["+classname+"::"+__func__+"()]");

  std::map <int, DCGeomRecord *>::const_iterator
    itr=m_geom_container.begin(), end=m_geom_container.end();

  for(; itr!=end; ++itr ){
    if (itr->second->Name() == detName)
      return itr->second->Id();
  }

  std::cerr << funcname << " : No such detector " << detName << std::endl;
  std::exit(EXIT_FAILURE);
}
