/*
 *  DCGeomRecord.cc
 */

#include "DCGeomRecord.hh"

#include <cmath>

const double Deg2Rad = acos(-1.)/180.;

//______________________________________________________________________________
DCGeomRecord::DCGeomRecord( int id, const char *name,
			    double x, double y, double z, double ta,
			    double ra1, double ra2, double length, double resol,
			    double w0, double dd, double ofs )
  : m_id(id), m_name(name), m_pos(x,y,z), m_tilt_angle(ta),
    m_rot_angle1(ra1), m_rot_angle2(ra2),
    m_length(length), m_resolution(resol), m_w0(w0), m_dd(dd), m_offset(ofs)
{
  calcVectors();
}

//______________________________________________________________________________
DCGeomRecord::DCGeomRecord( int id, const std::string &name,
			    double x, double y, double z, double ta,
			    double ra1, double ra2, double length, double resol,
			    double w0, double dd, double ofs )
  : m_id(id), m_name(name), m_pos(x,y,z), m_tilt_angle(ta),
    m_rot_angle1(ra1), m_rot_angle2(ra2),
    m_length(length), m_resolution(resol), m_w0(w0), m_dd(dd), m_offset(ofs)
{
  calcVectors();
}

//______________________________________________________________________________
DCGeomRecord::DCGeomRecord( int id, const char *name,
			    const ThreeVector pos, double ta,
			    double ra1, double ra2, double length, double resol,
			    double w0, double dd, double ofs )
  : m_id(id), m_name(name), m_pos(pos),  m_tilt_angle(ta),
    m_rot_angle1(ra1), m_rot_angle2(ra2),
    m_length(length), m_resolution(resol), m_w0(w0), m_dd(dd), m_offset(ofs)
{
  calcVectors();
}

//______________________________________________________________________________
DCGeomRecord::DCGeomRecord( int id, const std::string &name,
			    const ThreeVector pos, double ta,
			    double ra1, double ra2, double length, double resol,
			    double w0, double dd, double ofs )
  : m_id(id), m_name(name), m_pos(pos),  m_tilt_angle(ta),
    m_rot_angle1(ra1), m_rot_angle2(ra2),
    m_length(length), m_resolution(resol), m_w0(w0), m_dd(dd), m_offset(ofs)
{
  calcVectors();
}

//______________________________________________________________________________
void
DCGeomRecord::calcVectors( void )
{
  double ct0 = cos(m_tilt_angle*Deg2Rad), st0 = sin(m_tilt_angle*Deg2Rad);
  double ct1 = cos(m_rot_angle1*Deg2Rad), st1 = sin(m_rot_angle1*Deg2Rad);
  double ct2 = cos(m_rot_angle2*Deg2Rad), st2 = sin(m_rot_angle2*Deg2Rad);

  m_dxds =  ct0*ct2-st0*ct1*st2;
  m_dxdt = -st0*ct2-ct0*ct1*st2;
  m_dxdu =  st1*st2;

  m_dyds =  ct0*st2+st0*ct1*ct2;
  m_dydt = -st0*st2+ct0*ct1*ct2;
  m_dydu = -st1*ct2;

  m_dzds =  st0*st1;
  m_dzdt =  ct0*st1;
  m_dzdu =  ct1;

  m_dsdx =  ct0*ct2-st0*ct1*st2;
  m_dsdy =  ct0*st2+st0*ct1*ct2;
  m_dsdz =  st0*st1;

  m_dtdx = -st0*ct2-ct0*ct1*st2;
  m_dtdy = -st0*st2+ct0*ct1*ct2;
  m_dtdz =  ct0*st1;

  m_dudx =  st1*st2;
  m_dudy = -st1*ct2;
  m_dudz =  ct1;
}

//______________________________________________________________________________
int
DCGeomRecord::WireNumber( double pos ) const
{
  double dw = ( (pos-m_offset)/m_dd ) + m_w0;
  int iw = int(dw);
  if( (dw-double(iw))>0.5 )
    return iw+1;
  else
    return iw;
}
