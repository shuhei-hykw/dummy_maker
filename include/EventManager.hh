/**
 *  file: EventManager.hh
 *  date: 2016.04.25
 *
 */

#ifndef EVENT_MANAGER_HH
#define EVENT_MANAGER_HH

#include "DetectorID.hh"

#include <string>
#include <vector>

class DetectorHit;
class TFile;
class TTree;

//_____________________________________________________________________
struct Event
{
  static const int MaxTrack = 100;
  int       evnum;
  int       beam_sw;
  double    pg[4];
  double    xg[3];
  double    product_pg[4];
  double    product_xg[3];
  int       npid;
  double    x0[MaxTrack][3];
  double    p0[MaxTrack][5];
  double    pt0[MaxTrack];
  double    mass0[MaxTrack];
  double    theta0[MaxTrack];
  double    pfermi[4];
  double    crosssection;
  int       ntSsd;
  int       tidSsd[MaxTrack];
  int       pidSsd[MaxTrack];
  int       didSsd[MaxTrack];
  double    massSsd[MaxTrack];
  int       chargeSsd[MaxTrack];
  double    edepSsd[MaxTrack];
  double    xSsd[MaxTrack];
  double    ySsd[MaxTrack];
  double    zSsd[MaxTrack];
  double    pxSsd[MaxTrack];
  double    pySsd[MaxTrack];
  double    pzSsd[MaxTrack];
  double    ppSsd[MaxTrack];
  double    tofSsd[MaxTrack];
  int       SsdpID[MaxTrack];
  double    vtxpxSsd[MaxTrack];
  double    vtxpySsd[MaxTrack];
  double    vtxpzSsd[MaxTrack];
  double    vtxppSsd[MaxTrack];
  double    vtxxSsd[MaxTrack];
  double    vtxySsd[MaxTrack];
  double    vtxzSsd[MaxTrack];
  double    lengthSsd[MaxTrack];
  int       ntAc;
  int       tidAc[MaxTrack];
  int       pidAc[MaxTrack];
  int       didAc[MaxTrack];
  double    massAc[MaxTrack];
  int       chargeAc[MaxTrack];
  double    xAc[MaxTrack];
  double    yAc[MaxTrack];
  double    zAc[MaxTrack];
  double    pxAc[MaxTrack];
  double    pyAc[MaxTrack];
  double    pzAc[MaxTrack];
  double    ppAc[MaxTrack];
  double    tofAc[MaxTrack];
  int       AcpID[MaxTrack];
  double    vtxpxAc[MaxTrack];
  double    vtxpyAc[MaxTrack];
  double    vtxpzAc[MaxTrack];
  double    vtxppAc[MaxTrack];
  double    vtxxAc[MaxTrack];
  double    vtxyAc[MaxTrack];
  double    vtxzAc[MaxTrack];
  double    lengthAc[MaxTrack];
  int       ntBac;
  int       tidBac[MaxTrack];
  int       pidBac[MaxTrack];
  int       didBac[MaxTrack];
  double    massBac[MaxTrack];
  int       chargeBac[MaxTrack];
  double    edepBac[MaxTrack];
  double    xBac[MaxTrack];
  double    yBac[MaxTrack];
  double    zBac[MaxTrack];
  double    pxBac[MaxTrack];
  double    pyBac[MaxTrack];
  double    pzBac[MaxTrack];
  double    ppBac[MaxTrack];
  double    tofBac[MaxTrack];
  int       BacpID[MaxTrack];
  double    vtxpxBac[MaxTrack];
  double    vtxpyBac[MaxTrack];
  double    vtxpzBac[MaxTrack];
  double    vtxppBac[MaxTrack];
  double    vtxxBac[MaxTrack];
  double    vtxyBac[MaxTrack];
  double    vtxzBac[MaxTrack];
  double    lengthBac[MaxTrack];
  int       ntBh2;
  int       tidBh2[MaxTrack];
  int       pidBh2[MaxTrack];
  int       didBh2[MaxTrack];
  double    massBh2[MaxTrack];
  int       chargeBh2[MaxTrack];
  double    edepBh2[MaxTrack];
  double    xBh2[MaxTrack];
  double    yBh2[MaxTrack];
  double    zBh2[MaxTrack];
  double    pxBh2[MaxTrack];
  double    pyBh2[MaxTrack];
  double    pzBh2[MaxTrack];
  double    ppBh2[MaxTrack];
  double    tofBh2[MaxTrack];
  int       Bh2pID[MaxTrack];
  double    vtxpxBh2[MaxTrack];
  double    vtxpyBh2[MaxTrack];
  double    vtxpzBh2[MaxTrack];
  double    vtxppBh2[MaxTrack];
  double    vtxxBh2[MaxTrack];
  double    vtxyBh2[MaxTrack];
  double    vtxzBh2[MaxTrack];
  double    lengthBh2[MaxTrack];
  int       ntSch;
  int       tidSch[MaxTrack];
  int       pidSch[MaxTrack];
  int       didSch[MaxTrack];
  double    massSch[MaxTrack];
  int       chargeSch[MaxTrack];
  double    xSch[MaxTrack];
  double    ySch[MaxTrack];
  double    zSch[MaxTrack];
  double    pxSch[MaxTrack];
  double    pySch[MaxTrack];
  double    pzSch[MaxTrack];
  double    ppSch[MaxTrack];
  double    tofSch[MaxTrack];
  int       SchpID[MaxTrack];
  double    vtxpxSch[MaxTrack];
  double    vtxpySch[MaxTrack];
  double    vtxpzSch[MaxTrack];
  double    vtxppSch[MaxTrack];
  double    vtxxSch[MaxTrack];
  double    vtxySch[MaxTrack];
  double    vtxzSch[MaxTrack];
  double    lengthSch[MaxTrack];
  int       ntTof;
  int       tidTof[MaxTrack];
  int       pidTof[MaxTrack];
  int       didTof[MaxTrack];
  double    massTof[MaxTrack];
  int       chargeTof[MaxTrack];
  double    edepTof[MaxTrack];
  double    xTof[MaxTrack];
  double    yTof[MaxTrack];
  double    zTof[MaxTrack];
  double    pxTof[MaxTrack];
  double    pyTof[MaxTrack];
  double    pzTof[MaxTrack];
  double    ppTof[MaxTrack];
  double    tofTof[MaxTrack];
  int       TofpID[MaxTrack];
  double    vtxpxTof[MaxTrack];
  double    vtxpyTof[MaxTrack];
  double    vtxpzTof[MaxTrack];
  double    vtxppTof[MaxTrack];
  double    vtxxTof[MaxTrack];
  double    vtxyTof[MaxTrack];
  double    vtxzTof[MaxTrack];
  double    lengthTof[MaxTrack];
  int       ntSdc;
  int       tidSdc[MaxTrack];
  int       pidSdc[MaxTrack];
  int       didSdc[MaxTrack];
  double    massSdc[MaxTrack];
  int       chargeSdc[MaxTrack];
  double    xSdc[MaxTrack];
  double    ySdc[MaxTrack];
  double    zSdc[MaxTrack];
  double    pxSdc[MaxTrack];
  double    pySdc[MaxTrack];
  double    pzSdc[MaxTrack];
  double    ppSdc[MaxTrack];
  double    tofSdc[MaxTrack];
  int       SdcpID[MaxTrack];
  double    vtxpxSdc[MaxTrack];
  double    vtxpySdc[MaxTrack];
  double    vtxpzSdc[MaxTrack];
  double    vtxppSdc[MaxTrack];
  double    vtxxSdc[MaxTrack];
  double    vtxySdc[MaxTrack];
  double    vtxzSdc[MaxTrack];
  double    lengthSdc[MaxTrack];
  int       targethits;
  int       targetpid[MaxTrack];
  int       targetparentid[MaxTrack];
  int       targettid[MaxTrack];
  double    targetpos[MaxTrack][3];
  double    targetvtx[MaxTrack][3];
  int       ntXi;
  double    XipID[MaxTrack];
  double    xXi[MaxTrack];
  double    yXi[MaxTrack];
  double    zXi[MaxTrack];
  double    pxXi[MaxTrack];
  double    pyXi[MaxTrack];
  double    pzXi[MaxTrack];
  double    ppXi[MaxTrack];
  double    tlengthXi[MaxTrack];
  double    tidXi[MaxTrack];
  double    didXi[MaxTrack];
  double    pidXi[MaxTrack];
  double    vtxxXi[MaxTrack];
  double    vtxyXi[MaxTrack];
  double    vtxzXi[MaxTrack];
  double    vtxpxXi[MaxTrack];
  double    vtxpyXi[MaxTrack];
  double    vtxpzXi[MaxTrack];
  double    vtxppXi[MaxTrack];
};

//_____________________________________________________________________
class EventManager
{
public:
  static EventManager& GetInstance( void );
  ~EventManager( void );

private:
  explicit EventManager( void );
  EventManager( const EventManager& );
  EventManager& operator =( const EventManager& );

private:
  static EventManager *m_event_manager;
  std::string          m_file_name;
  TFile               *m_file;
  std::string          m_tree_name;
  TTree               *m_tree;
  unsigned int         m_nentries;
  Event                m_event;

public:
  unsigned int GetEntries( void ) const { return m_nentries; }
  Event        GetEvent( void ) const { return m_event; }
  void         SetFileName( const std::string& file_name ){ m_file_name = file_name; }
  void         SetTree( TTree *tree ){ m_tree = tree; }
  bool         Initialize( void );
  bool         Initialize( const std::string& file_name );
  bool         InitializeEvent( void );
  bool         ProcessEvent( void );
  bool         FinalizeEvent( void );
  bool         Finalize( void );
  bool         SetBranchAddress( void );

};

#endif
