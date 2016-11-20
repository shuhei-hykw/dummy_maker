/**
 *  file: EventManager.cc
 *  date: 2016.11.20
 *
 */

#include "EventManager.hh"

#include "DAQNode.hh"
#include "DAQModule.hh"
#include "DCGeomMan.hh"
#include "DeleteObject.hh"
#include "DetectorID.hh"
#include "DetectorManager.hh"
#include "EventRecorder.hh"
#include "NodeManager.hh"
#include "VmeCaenV775.hh"
#include "VmeCaenV792.hh"
#include "VmeNoticeTdc64M.hh"

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>

#include <TFile.h>
#include <TCanvas.h>
#include <TH1.h>
#include <TRandom.h>
#include <TTree.h>

extern unsigned int g_event_number;
EventManager *EventManager::m_event_manager = 0;

static const std::string class_name("EventManager");

//_____________________________________________________________________
EventManager::EventManager( void )
  : m_file_name(""),
    m_file(0),
    m_tree_name("tree"),
    m_tree(0),
    m_nentries(0)
{
}

//_____________________________________________________________________
EventManager::~EventManager( void )
{
}

//_____________________________________________________________________
EventManager&
EventManager::GetInstance( void )
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");
  if( !m_event_manager )
    m_event_manager = new EventManager;
  return *m_event_manager;
}

//_____________________________________________________________________
bool
EventManager::Initialize( void )
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");

  std::cout << "#D " << func_name << std::endl;

  m_file = new TFile( m_file_name.c_str() );
  if( !m_file->IsOpen() ){
    std::cout << " * cannot find file : " << m_file_name << std::endl;
    return false;
  }
  std::cout << "   open file : " << m_file_name << std::endl;

  m_tree = (TTree*)m_file->Get( m_tree_name.c_str() );
  if( !m_tree ){
    std::cout << " * cannot find tree : " << m_file_name << std::endl;
    return false;
  }
  std::cout << "   open tree : " << m_tree_name << std::endl;

  m_nentries = m_tree->GetEntries();

  SetBranchAddress();

  gRandom->SetSeed( time(0) );

  return true;
}

//_____________________________________________________________________
bool
EventManager::Initialize( const std::string& file_name )
{
  m_file_name = file_name;
  Initialize();
  return true;
}

//_____________________________________________________________________
bool
EventManager::InitializeEvent( void )
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");

  m_tree->GetEntry( g_event_number );

  static NodeManager& node_manager = NodeManager::GetInstance();
  node_manager.Clear();

  return true;
}

//_____________________________________________________________________
bool
EventManager::ProcessEvent( void )
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");

  static NodeManager&     node_manager     = NodeManager::GetInstance();
  static DetectorManager& detector_manager = DetectorManager::GetInstance();
  static DCGeomMan&       geom_manager     = DCGeomMan::GetInstance();

#if 0
  if( g_event_number%1000==0 ){
    std::cout << "#D " << func_name << " Event number : "
  	      << std::setw(8) << g_event_number << std::endl;
  }
#endif

  node_manager.SetEventNumber( g_event_number );

  static VmeNoticeTdc64M *tdc64m_sdc1[NumOfLayerSDC1];
  static VmeNoticeTdc64M *tdc64m_sdc2[NumOfLayerSDC2*2];
  static VmeNoticeTdc64M *tdc64m_sdc3x[NumOfLayerSDC3X*2];
  static VmeNoticeTdc64M *tdc64m_sdc3y[NumOfLayerSDC3Y];
  if( g_event_number==0 ){
    // for SDC1
    for( int layer=0; layer<NumOfLayerSDC1; ++layer ){
      std::stringstream name;
      name << "tdc64m_sdc1_" << layer+1;
      tdc64m_sdc1[layer] =
	(VmeNoticeTdc64M*)node_manager.GetModule( name.str() );
    }
    // for SDC2
    for( int layer=0; layer<NumOfLayerSDC2*2; ++layer ){
      std::stringstream name;
      name << "tdc64m_sdc2_" << layer+1;
      tdc64m_sdc2[layer] =
	(VmeNoticeTdc64M*)node_manager.GetModule( name.str() );
    }
    // for SDC3X
    for( int layer=0; layer<NumOfLayerSDC3X*2; ++layer ){
      std::stringstream name;
      name << "tdc64m_sdc3x_" << layer+1;
      tdc64m_sdc3x[layer] =
	(VmeNoticeTdc64M*)node_manager.GetModule( name.str() );
    }
    // for SDC3Y
    for( int layer=0; layer<NumOfLayerSDC3Y; ++layer ){
      std::stringstream name;
      name << "tdc64m_sdc3y_" << layer+1;
      tdc64m_sdc3y[layer] =
	(VmeNoticeTdc64M*)node_manager.GetModule( name.str() );
    }
  }
  // for TOF
  static VmeCaenV792 *v792tofu =
    (VmeCaenV792*)node_manager.GetModule("v792tofu");
  static VmeCaenV792 *v792tofd =
    (VmeCaenV792*)node_manager.GetModule("v792tofd");
  static VmeCaenV775 *v775tofu =
    (VmeCaenV775*)node_manager.GetModule("v775tofu");
  static VmeCaenV775 *v775tofd =
    (VmeCaenV775*)node_manager.GetModule("v775tofd");

  enum e_type { k_generated, k_accepted, k_stopped, n_type };
  bool flag[n_type];
  for(int t=0; t<n_type; ++t) flag[t] = false;
  flag[k_generated] = true;

  for( int ih=0; ih<m_event.ntTof; ++ih ){
    if(!flag[k_accepted]){
      flag[k_accepted] = ( m_event.massTof[ih]>0.4 &&
			   m_event.massTof[ih]<0.5 );
    }
  }

  // if( !flag[k_accepted] ) return true;

  flag[k_stopped] = ( flag[k_accepted] && m_event.didXi[0]==2 );

  // if(flag[k_stopped])
  //   std::cout << "#D " << func_name << " Xi stopped! " << std::endl;

  // SSD
  {
    int ntssd1 = 0;
    int ntssd2 = 0;
    for( int ih=0; ih<m_event.ntSsd; ++ih ){
      if( m_event.zSsd[ih]<-1030. ){
	++ntssd1;
      }
      if( m_event.zSsd[ih]>-1030. ){
	++ntssd2;
      }
    }
  }

  // Xi
  {
    for( int ih=0; ih<m_event.ntXi; ++ih ){
      ;//std::cout << "#D " << func_name << " ";
    }
  }

  // ACs
  {
    int ntpvac = 0;
    int ntfac  = 0;
    for( int ih=0; ih<m_event.ntAc; ++ih ){
      if( m_event.zAc[ih]<-900 ){
	ntpvac++;
      }
      if( m_event.zAc[ih]>-900 ){
	ntfac++;
      }
    }
  }

  // SCH
  {
    for( int ih=0; ih<m_event.ntSch; ++ih ){
      ;//if( std::fabs(chargeSch[ih])>1 ) return;
    }
  }

  // SDC
  {
    int ntsdc1 = 0;
    int ntsdc2 = 0;
    int ntsdc3 = 0;
    // std::cout << "=== start SDC" << std::endl;
    for( int ih=0; ih<m_event.ntSdc; ++ih ){
      int pid     = m_event.pidSdc[ih];
      if( pid!=321 ) continue;
      int did     = m_event.didSdc[ih];
      int isdc    = m_event.didSdc[ih]/10000;
      int layer   = (m_event.didSdc[ih] -isdc*10000)/1000;
      int channel = m_event.didSdc[ih] -isdc*10000 -layer*1000;
      int lid = layer;
      if( isdc==1 ) lid +=  0;
      if( isdc==2 ) lid += 30;
      if( isdc==3 ) lid += 34;
      if( isdc==4 ) lid += 36;
      double wire_pos = geom_manager.calcWirePosition( lid, channel );
      const double Deg2Rad = acos(-1.)/180.;
      double angle = geom_manager.GetTiltAngle( lid ) * Deg2Rad;
      // double z = geom_manager.GetLocalZ( lid );
      double x = m_event.xSdc[ih];
      double y = m_event.ySdc[ih];
      double z = m_event.zSdc[ih];
      double dl = std::abs( x*cos(angle) - y*sin(angle) - wire_pos );
      // if( ( isdc==1 && dl> 3.0 ) || ( isdc==2 && dl> 4.5 ) ||
      // 	  ( isdc==3 && dl>10.0 ) || ( isdc==4 && dl>10.0 ) ){
      // 	std::cout << "[Exceed Max DL] did: " << did << " lid: "
      // 		  << std::setw(2) << lid << " wire: "
      // 		  << std::setw(3) << channel << " dl: "
      // 		  << std::fixed << dl << " wire_pos: "
      // 		  << std::setw(4) << wire_pos << " (x,y,z)=("
      // 		  << x << "," << y << "," << z << ")"
      // 		  << std::endl;
      // 	continue;
      // }
#if 0
      std::cout << "did: " << did << " lid: "
		<< std::setw(2) << lid << " wire: "
		<< std::setw(3) << channel << " dl: "
		<< std::fixed << dl << " wire_pos: "
		<< std::setw(4) << wire_pos << " (x,y,z)=("
		<< x << "," << y << "," << z << ")"
		<< std::endl;
#endif
      const double dt = dl*10.;
      switch( isdc ){
      case 1: { // SDC1
	unsigned int tdc = 700;
	//unsigned int tdc = (unsigned int)(1500-m_event.tofSdc[ih]*100);
	tdc -= (int)dt;
	tdc64m_sdc1[layer-1]->SetTdc( channel-1, tdc );
	ntsdc1++;
	break;
      }
      case 2: { // SDC2
	layer = (layer-1)*2;
	if( channel>64 ){
	  channel -= 64;
	  layer   +=  1;
	}
	unsigned int tdc = 700;
	// unsigned int tdc = (unsigned int)(1500-m_event.tofSdc[ih]*100);
	tdc -= (int)dt;
	tdc64m_sdc2[layer]->SetTdc( channel-1, tdc );
	ntsdc2++;
	break;
      }
      case 3: { // SDC3X
	layer = (layer-1)*2;
	if( channel>64 ){
	  channel -= 64;
	  layer   +=  1;
	}
	unsigned int tdc = 700;
	//unsigned int tdc = (unsigned int)(1500-m_event.tofSdc[ih]*100);
	tdc -= (int)dt;
	tdc64m_sdc3x[layer]->SetTdc( channel-1, tdc );
	ntsdc3++;
	break;
      }
      case 4: { // SDC3Y
	unsigned int tdc = 700;
	//unsigned int tdc = (unsigned int)(1500-m_event.tofSdc[ih]*100);
	tdc -= (int)dt;
	tdc64m_sdc3y[layer-1]->SetTdc( channel-1, tdc );
	ntsdc3++;
	break;
      }
      default:
	break;
      } // switch( isdc )
    } // for( ih )
  } // SDC

  ////////// TOF
  static Detector *tof = detector_manager.GetDetector("TOF");
  {
    static const double e = tof->GetEnergyResolution();
    static const double t = tof->GetTimeResolution();
    for( int ih=0; ih<m_event.ntTof; ++ih ){
      int channel = m_event.didTof[ih];
      double edep = gRandom->Gaus( m_event.edepTof[ih],
      				   m_event.edepTof[ih]*e );
      double time = gRandom->Gaus( m_event.tofTof[ih],
      				   m_event.tofTof[ih]*t );
      if( edep < 0. ) edep = 0.;
      if( time < 0. ) time = 0.;
      //unsigned int adc = (unsigned int)( edep*2000 );
      unsigned int adc = 0;
      if( m_event.pidTof[ih]==321 ){
	adc = m_event.ppTof[ih]*1000;
      // std::cout << "pKaon : " << m_event.ppTof[ih] << " adc : " << adc << std::endl;
      }
      unsigned int tdc = (unsigned int)( time/v775tofu->GetLSB() );
      v792tofu->SetAdc( channel-1, adc );
      v792tofd->SetAdc( channel-1, adc );
      v775tofu->SetTdc( channel-1, tdc );
      v775tofd->SetTdc( channel-1, tdc );
      // std::cout << "#D " << func_name << " TOF[" << channel-1 << "]"
      // 		<< " adc : " << adc << "\t tdc : " << tdc << std::endl;
    }
  }

  return true;
}

//_____________________________________________________________________
bool
EventManager::FinalizeEvent( void )
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");

  static NodeManager&   node_manager   = NodeManager::GetInstance();
  static EventRecorder& event_recorder = EventRecorder::GetInstance();
  if( !event_recorder.IsOpen() ){
    std::cout << "#D " << func_name << " "
	      << "EventRecorder is not open ..." << std::endl;  
    return false;
  }

  NodeContainer node_container = node_manager.GetNodeContainer();
  for( NodeIterator itr=node_container.begin(),
	 itr_end=node_container.end(); itr!=itr_end; ++itr ){
    (*itr)->SetDataSize();
    event_recorder.Write( (*itr)->SummarizeDataWord() );
  }

  return true;
}

//_____________________________________________________________________
bool
EventManager::Finalize( void )
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");

  return true;
}

//_____________________________________________________________________
bool
EventManager::SetBranchAddress( void )
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");
  m_tree->SetBranchAddress("evnum",&m_event.evnum);
  m_tree->SetBranchAddress("beam_sw",&m_event.beam_sw);
  m_tree->SetBranchAddress("pg",m_event.pg);
  m_tree->SetBranchAddress("xg",m_event.xg);
  m_tree->SetBranchAddress("product_pg",m_event.product_pg);
  m_tree->SetBranchAddress("product_xg",m_event.product_xg);
  m_tree->SetBranchAddress("npid",&m_event.npid);
  m_tree->SetBranchAddress("x0",m_event.x0);
  m_tree->SetBranchAddress("p0",m_event.p0);
  m_tree->SetBranchAddress("pt0",m_event.pt0);
  m_tree->SetBranchAddress("mass0",m_event.mass0);
  m_tree->SetBranchAddress("theta0",m_event.theta0);
  m_tree->SetBranchAddress("pfermi",m_event.pfermi);
  m_tree->SetBranchAddress("crosssection",&m_event.crosssection);
  m_tree->SetBranchAddress("ntSsd",&m_event.ntSsd);
  m_tree->SetBranchAddress("tidSsd",m_event.tidSsd);
  m_tree->SetBranchAddress("pidSsd",m_event.pidSsd);
  m_tree->SetBranchAddress("didSsd",m_event.didSsd);
  m_tree->SetBranchAddress("massSsd",m_event.massSsd);
  m_tree->SetBranchAddress("chargeSsd",m_event.chargeSsd);
  m_tree->SetBranchAddress("edepSsd",m_event.edepSsd);
  m_tree->SetBranchAddress("xSsd",m_event.xSsd);
  m_tree->SetBranchAddress("ySsd",m_event.ySsd);
  m_tree->SetBranchAddress("zSsd",m_event.zSsd);
  m_tree->SetBranchAddress("pxSsd",m_event.pxSsd);
  m_tree->SetBranchAddress("pySsd",m_event.pySsd);
  m_tree->SetBranchAddress("pzSsd",m_event.pzSsd);
  m_tree->SetBranchAddress("ppSsd",m_event.ppSsd);
  m_tree->SetBranchAddress("tofSsd",m_event.tofSsd);
  m_tree->SetBranchAddress("SsdpID",m_event.SsdpID);
  m_tree->SetBranchAddress("vtxpxSsd",m_event.vtxpxSsd);
  m_tree->SetBranchAddress("vtxpySsd",m_event.vtxpySsd);
  m_tree->SetBranchAddress("vtxpzSsd",m_event.vtxpzSsd);
  m_tree->SetBranchAddress("vtxppSsd",m_event.vtxppSsd);
  m_tree->SetBranchAddress("vtxxSsd",m_event.vtxxSsd);
  m_tree->SetBranchAddress("vtxySsd",m_event.vtxySsd);
  m_tree->SetBranchAddress("vtxzSsd",m_event.vtxzSsd);
  m_tree->SetBranchAddress("lengthSsd",m_event.lengthSsd);
  m_tree->SetBranchAddress("ntAc",&m_event.ntAc);
  m_tree->SetBranchAddress("tidAc",m_event.tidAc);
  m_tree->SetBranchAddress("pidAc",m_event.pidAc);
  m_tree->SetBranchAddress("didAc",m_event.didAc);
  m_tree->SetBranchAddress("massAc",m_event.massAc);
  m_tree->SetBranchAddress("chargeAc",m_event.chargeAc);
  m_tree->SetBranchAddress("xAc",m_event.xAc);
  m_tree->SetBranchAddress("yAc",m_event.yAc);
  m_tree->SetBranchAddress("zAc",m_event.zAc);
  m_tree->SetBranchAddress("pxAc",m_event.pxAc);
  m_tree->SetBranchAddress("pyAc",m_event.pyAc);
  m_tree->SetBranchAddress("pzAc",m_event.pzAc);
  m_tree->SetBranchAddress("ppAc",m_event.ppAc);
  m_tree->SetBranchAddress("tofAc",m_event.tofAc);
  m_tree->SetBranchAddress("AcpID",m_event.AcpID);
  m_tree->SetBranchAddress("vtxpxAc",m_event.vtxpxAc);
  m_tree->SetBranchAddress("vtxpyAc",m_event.vtxpyAc);
  m_tree->SetBranchAddress("vtxpzAc",m_event.vtxpzAc);
  m_tree->SetBranchAddress("vtxppAc",m_event.vtxppAc);
  m_tree->SetBranchAddress("vtxxAc",m_event.vtxxAc);
  m_tree->SetBranchAddress("vtxyAc",m_event.vtxyAc);
  m_tree->SetBranchAddress("vtxzAc",m_event.vtxzAc);
  m_tree->SetBranchAddress("lengthAc",m_event.lengthAc);
  m_tree->SetBranchAddress("ntBac",&m_event.ntBac);
  m_tree->SetBranchAddress("tidBac",&m_event.tidBac);
  m_tree->SetBranchAddress("pidBac",&m_event.pidBac);
  m_tree->SetBranchAddress("didBac",&m_event.didBac);
  m_tree->SetBranchAddress("massBac",&m_event.massBac);
  m_tree->SetBranchAddress("chargeBac",&m_event.chargeBac);
  m_tree->SetBranchAddress("edepBac",&m_event.edepBac);
  m_tree->SetBranchAddress("xBac",&m_event.xBac);
  m_tree->SetBranchAddress("yBac",&m_event.yBac);
  m_tree->SetBranchAddress("zBac",&m_event.zBac);
  m_tree->SetBranchAddress("pxBac",&m_event.pxBac);
  m_tree->SetBranchAddress("pyBac",&m_event.pyBac);
  m_tree->SetBranchAddress("pzBac",&m_event.pzBac);
  m_tree->SetBranchAddress("ppBac",&m_event.ppBac);
  m_tree->SetBranchAddress("tofBac",&m_event.tofBac);
  m_tree->SetBranchAddress("BacpID",&m_event.BacpID);
  m_tree->SetBranchAddress("vtxpxBac",&m_event.vtxpxBac);
  m_tree->SetBranchAddress("vtxpyBac",&m_event.vtxpyBac);
  m_tree->SetBranchAddress("vtxpzBac",&m_event.vtxpzBac);
  m_tree->SetBranchAddress("vtxppBac",&m_event.vtxppBac);
  m_tree->SetBranchAddress("vtxxBac",&m_event.vtxxBac);
  m_tree->SetBranchAddress("vtxyBac",&m_event.vtxyBac);
  m_tree->SetBranchAddress("vtxzBac",&m_event.vtxzBac);
  m_tree->SetBranchAddress("lengthBac",&m_event.lengthBac);
  m_tree->SetBranchAddress("ntBh2",&m_event.ntBh2);
  m_tree->SetBranchAddress("tidBh2",&m_event.tidBh2);
  m_tree->SetBranchAddress("pidBh2",&m_event.pidBh2);
  m_tree->SetBranchAddress("didBh2",&m_event.didBh2);
  m_tree->SetBranchAddress("massBh2",&m_event.massBh2);
  m_tree->SetBranchAddress("chargeBh2",&m_event.chargeBh2);
  m_tree->SetBranchAddress("edepBh2",&m_event.edepBh2);
  m_tree->SetBranchAddress("xBh2",&m_event.xBh2);
  m_tree->SetBranchAddress("yBh2",&m_event.yBh2);
  m_tree->SetBranchAddress("zBh2",&m_event.zBh2);
  m_tree->SetBranchAddress("pxBh2",&m_event.pxBh2);
  m_tree->SetBranchAddress("pyBh2",&m_event.pyBh2);
  m_tree->SetBranchAddress("pzBh2",&m_event.pzBh2);
  m_tree->SetBranchAddress("ppBh2",&m_event.ppBh2);
  m_tree->SetBranchAddress("tofBh2",&m_event.tofBh2);
  m_tree->SetBranchAddress("Bh2pID",&m_event.Bh2pID);
  m_tree->SetBranchAddress("vtxpxBh2",&m_event.vtxpxBh2);
  m_tree->SetBranchAddress("vtxpyBh2",&m_event.vtxpyBh2);
  m_tree->SetBranchAddress("vtxpzBh2",&m_event.vtxpzBh2);
  m_tree->SetBranchAddress("vtxppBh2",&m_event.vtxppBh2);
  m_tree->SetBranchAddress("vtxxBh2",&m_event.vtxxBh2);
  m_tree->SetBranchAddress("vtxyBh2",&m_event.vtxyBh2);
  m_tree->SetBranchAddress("vtxzBh2",&m_event.vtxzBh2);
  m_tree->SetBranchAddress("lengthBh2",&m_event.lengthBh2);
  m_tree->SetBranchAddress("ntSch",&m_event.ntSch);
  m_tree->SetBranchAddress("tidSch",m_event.tidSch);
  m_tree->SetBranchAddress("pidSch",m_event.pidSch);
  m_tree->SetBranchAddress("didSch",m_event.didSch);
  m_tree->SetBranchAddress("massSch",m_event.massSch);
  m_tree->SetBranchAddress("chargeSch",m_event.chargeSch);
  m_tree->SetBranchAddress("xSch",m_event.xSch);
  m_tree->SetBranchAddress("ySch",m_event.ySch);
  m_tree->SetBranchAddress("zSch",m_event.zSch);
  m_tree->SetBranchAddress("pxSch",m_event.pxSch);
  m_tree->SetBranchAddress("pySch",m_event.pySch);
  m_tree->SetBranchAddress("pzSch",m_event.pzSch);
  m_tree->SetBranchAddress("ppSch",m_event.ppSch);
  m_tree->SetBranchAddress("tofSch",m_event.tofSch);
  m_tree->SetBranchAddress("SchpID",m_event.SchpID);
  m_tree->SetBranchAddress("vtxpxSch",m_event.vtxpxSch);
  m_tree->SetBranchAddress("vtxpySch",m_event.vtxpySch);
  m_tree->SetBranchAddress("vtxpzSch",m_event.vtxpzSch);
  m_tree->SetBranchAddress("vtxppSch",m_event.vtxppSch);
  m_tree->SetBranchAddress("vtxxSch",m_event.vtxxSch);
  m_tree->SetBranchAddress("vtxySch",m_event.vtxySch);
  m_tree->SetBranchAddress("vtxzSch",m_event.vtxzSch);
  m_tree->SetBranchAddress("lengthSch",m_event.lengthSch);
  m_tree->SetBranchAddress("ntTof",&m_event.ntTof);
  m_tree->SetBranchAddress("tidTof",m_event.tidTof);
  m_tree->SetBranchAddress("pidTof",m_event.pidTof);
  m_tree->SetBranchAddress("didTof",m_event.didTof);
  m_tree->SetBranchAddress("massTof",m_event.massTof);
  m_tree->SetBranchAddress("chargeTof",m_event.chargeTof);
  m_tree->SetBranchAddress("edepTof",m_event.edepTof);
  m_tree->SetBranchAddress("xTof",m_event.xTof);
  m_tree->SetBranchAddress("yTof",m_event.yTof);
  m_tree->SetBranchAddress("zTof",m_event.zTof);
  m_tree->SetBranchAddress("pxTof",m_event.pxTof);
  m_tree->SetBranchAddress("pyTof",m_event.pyTof);
  m_tree->SetBranchAddress("pzTof",m_event.pzTof);
  m_tree->SetBranchAddress("ppTof",m_event.ppTof);
  m_tree->SetBranchAddress("tofTof",m_event.tofTof);
  m_tree->SetBranchAddress("TofpID",m_event.TofpID);
  m_tree->SetBranchAddress("vtxpxTof",m_event.vtxpxTof);
  m_tree->SetBranchAddress("vtxpyTof",m_event.vtxpyTof);
  m_tree->SetBranchAddress("vtxpzTof",m_event.vtxpzTof);
  m_tree->SetBranchAddress("vtxppTof",m_event.vtxppTof);
  m_tree->SetBranchAddress("vtxxTof",m_event.vtxxTof);
  m_tree->SetBranchAddress("vtxyTof",m_event.vtxyTof);
  m_tree->SetBranchAddress("vtxzTof",m_event.vtxzTof);
  m_tree->SetBranchAddress("lengthTof",m_event.lengthTof);
  m_tree->SetBranchAddress("ntSdc",&m_event.ntSdc);
  m_tree->SetBranchAddress("tidSdc",m_event.tidSdc);
  m_tree->SetBranchAddress("pidSdc",m_event.pidSdc);
  m_tree->SetBranchAddress("didSdc",m_event.didSdc);
  m_tree->SetBranchAddress("massSdc",m_event.massSdc);
  m_tree->SetBranchAddress("chargeSdc",m_event.chargeSdc);
  m_tree->SetBranchAddress("xSdc",m_event.xSdc);
  m_tree->SetBranchAddress("ySdc",m_event.ySdc);
  m_tree->SetBranchAddress("zSdc",m_event.zSdc);
  m_tree->SetBranchAddress("pxSdc",m_event.pxSdc);
  m_tree->SetBranchAddress("pySdc",m_event.pySdc);
  m_tree->SetBranchAddress("pzSdc",m_event.pzSdc);
  m_tree->SetBranchAddress("ppSdc",m_event.ppSdc);
  m_tree->SetBranchAddress("tofSdc",m_event.tofSdc);
  m_tree->SetBranchAddress("SdcpID",m_event.SdcpID);
  m_tree->SetBranchAddress("vtxpxSdc",m_event.vtxpxSdc);
  m_tree->SetBranchAddress("vtxpySdc",m_event.vtxpySdc);
  m_tree->SetBranchAddress("vtxpzSdc",m_event.vtxpzSdc);
  m_tree->SetBranchAddress("vtxppSdc",m_event.vtxppSdc);
  m_tree->SetBranchAddress("vtxxSdc",m_event.vtxxSdc);
  m_tree->SetBranchAddress("vtxySdc",m_event.vtxySdc);
  m_tree->SetBranchAddress("vtxzSdc",m_event.vtxzSdc);
  m_tree->SetBranchAddress("lengthSdc",m_event.lengthSdc);
  m_tree->SetBranchAddress("targethits",&m_event.targethits);
  m_tree->SetBranchAddress("targetpid",m_event.targetpid);
  m_tree->SetBranchAddress("targetparentid",m_event.targetparentid);
  m_tree->SetBranchAddress("targettid",m_event.targettid);
  m_tree->SetBranchAddress("targetpos",m_event.targetpos);
  m_tree->SetBranchAddress("targetvtx",m_event.targetvtx);
  m_tree->SetBranchAddress("ntXi",&m_event.ntXi);
  m_tree->SetBranchAddress("XipID",&m_event.XipID);
  m_tree->SetBranchAddress("xXi",m_event.xXi);
  m_tree->SetBranchAddress("yXi",m_event.yXi);
  m_tree->SetBranchAddress("zXi",m_event.zXi);
  m_tree->SetBranchAddress("pxXi",m_event.pxXi);
  m_tree->SetBranchAddress("pyXi",m_event.pyXi);
  m_tree->SetBranchAddress("pzXi",m_event.pzXi);
  m_tree->SetBranchAddress("ppXi",m_event.ppXi);
  m_tree->SetBranchAddress("tlengthXi",m_event.tlengthXi);
  m_tree->SetBranchAddress("tidXi",m_event.tidXi);
  m_tree->SetBranchAddress("didXi",m_event.didXi);
  m_tree->SetBranchAddress("pidXi",m_event.pidXi);
  m_tree->SetBranchAddress("vtxxXi",m_event.vtxxXi);
  m_tree->SetBranchAddress("vtxyXi",m_event.vtxyXi);
  m_tree->SetBranchAddress("vtxzXi",m_event.vtxzXi);
  m_tree->SetBranchAddress("vtxpxXi",m_event.vtxpxXi);
  m_tree->SetBranchAddress("vtxpyXi",m_event.vtxpyXi);
  m_tree->SetBranchAddress("vtxpzXi",m_event.vtxpzXi);
  m_tree->SetBranchAddress("vtxppXi",m_event.vtxppXi);
  return true;
}
