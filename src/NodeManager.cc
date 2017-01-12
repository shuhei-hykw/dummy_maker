/**
 *  file: NodeManager.hh
 *  date: 2017.01.12
 *
 */

#include "NodeManager.hh"

#include "CopperLite.hh"
#include "DAQModule.hh"
#include "DAQNode.hh"
#include "DetectorID.hh"
#include "Finesse.hh"
#include "FinessePtdc.hh"
#include "VmeCaenV775.hh"
#include "VmeCaenV792.hh"
#include "VmeNode.hh"
#include "VmeNoticeTdc64M.hh"
#include "VmeModule.hh"

#include <iostream>
#include <sstream>

#include <TString.h>

NodeManager *NodeManager::m_node_manager = 0;

static const std::string class_name("NodeManager");

//_____________________________________________________________________
NodeManager::NodeManager( void )
{
}

//_____________________________________________________________________
NodeManager::~NodeManager( void )
{
}

//_____________________________________________________________________
NodeManager&
NodeManager::GetInstance( void )
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");
  if( !m_node_manager )
    m_node_manager = new NodeManager;
  return *m_node_manager;
}

//_____________________________________________________________________
bool
NodeManager::AddNodeList( DAQNode* node )
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");

  std::string node_name = node->GetNodeName();

  if( m_node_list.count( node_name ) ){
    std::cout << "#W " << func_name << " "
	      << " already added : " << node_name << std::endl;
    // PrintNodeList();
    return false;
  }

  m_node_list[node_name] = node;
  return true;
}

//_____________________________________________________________________
bool
NodeManager::AddModuleList( DAQModule* module )
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");

  std::string module_name = module->GetModuleName();

  if( m_module_list.count( module_name ) ){
    std::cout << "#W " << func_name << " "
	      << " already added : " << module_name << std::endl;
    // PrintModuleList();
    return false;
  }

  m_module_list[module_name] = module;

  return true;
}

//_____________________________________________________________________
bool
NodeManager::Clear( void )
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");

  for( ModuleListIterator itr=m_module_list.begin(),
	 itr_end=m_module_list.end(); itr!=itr_end; ++itr){
    itr->second->Clear();
  }

  return true;
}

//_____________________________________________________________________
bool
NodeManager::Initialize( void )
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");

  std::cout << "#D " << func_name << std::endl;

  m_module_list.clear();

  ////////// eb0
  DAQNode *eb0 = new DAQNode( "eb0", 0x1 );
  RegisterNode( eb0 );
  ////////// vme01
  VmeNode *vme01 = new VmeNode( "vme01", 0x201 );
  eb0->RegisterNode( vme01 );
  vme01->RegisterModule( new VmeCaenV792( "v792tofu", 0xad010000 ) );
  vme01->RegisterModule( new VmeCaenV792( "v792tofd", 0xad020000 ) );
  vme01->RegisterModule( new VmeCaenV775( "v775tofu", 0xcd010000 ) );
  vme01->RegisterModule( new VmeCaenV775( "v775tofd", 0xcd020000 ) );
  ////////// vme04
  VmeNode *vme04 = new VmeNode( "vme04", 0x204 );
  eb0->RegisterNode( vme04 );
  // SDC1
  for( int layer=0; layer<NumOfLayerSDC1; ++layer ){
    std::stringstream name;
    name << "tdc64m_sdc1_" << layer+1;
    unsigned int addr = 0x10000000 + 0x10000*(layer+1);
    vme04->RegisterModule( new VmeNoticeTdc64M( name.str(), addr ) );
  }
  // SDC2
  for( int layer=0; layer<NumOfLayerSDC2*2; ++layer ){
    std::stringstream name;
    name << "tdc64m_sdc2_" << layer+1;
    unsigned int addr = 0x20000000 + 0x10000*(layer+1);
    vme04->RegisterModule( new VmeNoticeTdc64M( name.str(), addr ) );
  }
  // SDC3-X
  for( int layer=0; layer<NumOfLayerSDC3X*2; ++layer ){
    std::stringstream name;
    name << "tdc64m_sdc3x_" << layer+1;
    unsigned int addr = 0x30000000 + 0x10000*(layer+1);
    vme04->RegisterModule( new VmeNoticeTdc64M( name.str(), addr ) );
  }
  // SDC3-Y
  for( int layer=0; layer<NumOfLayerSDC3Y; ++layer ){
    std::stringstream name;
    name << "tdc64m_sdc3y_" << layer+1;
    unsigned int addr = 0x40000000 + 0x10000*(layer+1);
    vme04->RegisterModule( new VmeNoticeTdc64M( name.str(), addr ) );
  }

  ////////// clite01
  // for( int i=0; i<10; ++i ){
  //   CopperLite *clite = new CopperLite( Form("clite%02d", i+1), 0x101 );
  //   eb0->RegisterNode( clite );
  //   for( int j=0; j<4; ++j )
  //     clite->RegisterModule( new FinessePtdc( Form("finesse%02d",
  // 						   i*4+j ),
  // 					      0, 0 ) );
  // }

  PrintRegisteredAll();

  return true;
}

//_____________________________________________________________________
DAQNode*
NodeManager::GetNode( const std::string& name )
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");

  if( m_node_list.count( name ) ){
    return m_node_list[name];
  }else{
    std::cout << "#W " << func_name << " "
	      << "cannot find node : " << name << std::endl;
    return 0;
  }
}

//_____________________________________________________________________
DAQModule*
NodeManager::GetModule( const std::string& name )
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");

  if( m_module_list.count( name ) ){
    return m_module_list[name];
  }else{
    std::cout << "#W " << func_name << " "
	      << "cannot find module : " << name << std::endl;
    return 0;
  }
}

//_____________________________________________________________________
bool
NodeManager::RegisterNode( DAQNode *node )
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");

  static NodeManager& node_manager = NodeManager::GetInstance();
  node_manager.AddNodeList( node );

  m_node_container.push_back( node );

  return true;
}

//_____________________________________________________________________
bool
NodeManager::SetEventNumber( unsigned int event_number )
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");
  for( NodeListIterator itr=m_node_list.begin(),
	 itr_end=m_node_list.end(); itr!=itr_end; ++itr ){
    itr->second->SetEventNumber( event_number );
  }
  return true;
}

//_____________________________________________________________________
void
NodeManager::PrintNodeList( void )
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");

  std::cout << "#D " << func_name << std::endl;
  for( NodeListIterator itr=m_node_list.begin(),
	 itr_end=m_node_list.end(); itr!=itr_end; ++itr ){
    std::cout << "   " << itr->second->GetNodeName() << std::endl;
  }
}

//_____________________________________________________________________
void
NodeManager::PrintModuleList( void )
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");

  std::cout << "#D " << func_name << std::endl;
  for( ModuleListIterator itr=m_module_list.begin(),
	 itr_end=m_module_list.end(); itr!=itr_end; ++itr ){
    std::cout << "   " << itr->second->GetModuleName() << std::endl;
  }
}

//_____________________________________________________________________
void
NodeManager::PrintRegisteredAll( void )
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");

  // std::cout << "#D " << func_name << std::endl;

  std::size_t nest;
  std::string space;

  for( NodeIterator nitr=m_node_container.begin(),
	 nitr_end=m_node_container.end(); nitr!=nitr_end; ++nitr ){
    nest = (*nitr)->GetNest();
    for( std::size_t ii=0; ii<nest; ++ii ) space += "   ";
    std::cout << space
	      << (*nitr)->GetNodeType() << " : "
	      << (*nitr)->GetNodeName() << " ("
	      << (*nitr)->GetNodeId()   << ")" << std::endl;

    ModuleContainer module_container = (*nitr)->GetModuleContainer();

    for( ModuleIterator mitr=module_container.begin(),
	   mitr_end=module_container.end(); mitr!=mitr_end; ++mitr ){
      std::cout << "\t\\_ "
		<< (*mitr)->GetModuleType() << " : "
		<< (*mitr)->GetModuleName() << std::endl;
    }

    NodeContainer child_container = (*nitr)->GetNodeContainer();
    int n_blocks = child_container.size();
    while( n_blocks>0 ){

      for( NodeIterator citr=child_container.begin(),
	     citr_end=child_container.end(); citr!=citr_end; ++citr ){

	nest  = (*citr)->GetNest();
	space = "";
	for( std::size_t ii=0; ii<nest-1; ++ii ) space += "\t";

	std::cout << space << "\\_ "
		  << (*citr)->GetNodeType() << " : "
		  << (*citr)->GetNodeName() << " ("
		  << (*citr)->GetNodeId()   << ")" << std::endl;

	ModuleContainer module_container = (*citr)->GetModuleContainer();
	for( ModuleIterator mitr=module_container.begin(),
	       mitr_end=module_container.end(); mitr!=mitr_end; ++mitr ){
	  std::cout << space << "\t\\_ "
		    << (*mitr)->GetModuleType() << " : "
		    << (*mitr)->GetModuleName() << std::endl;
	}

	if( citr==citr_end-1 ){
	  child_container = (*citr)->GetNodeContainer();
	  n_blocks = child_container.size();
	}

      }
    }
  }
}
