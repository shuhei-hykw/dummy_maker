/**
 *  file: DAQNode.cc
 *  date: 2016.01.28
 *
 */

#include "DAQNode.hh"
#include "DAQModule.hh"
#include "NodeManager.hh"

#include <iostream>
#include <string>

extern unsigned int g_run_number;

static const std::string class_name("DAQNode");

//_____________________________________________________________________
DAQNode::DAQNode( const std::string& node_name, const unsigned int node_id )
  : m_nest(1),
    m_node_name(node_name),
    m_node_type("DAQNode"),
    m_data_size(k_eb_header_length),
    m_event_number(0),
    m_run_number(g_run_number),
    m_node_id(node_id),
    m_event_type(0),
    m_n_blocks(0),
    m_reserved(0)
{
  m_eb_header.resize( k_eb_header_length );
  m_eb_header[k_eb_magic]   = k_eb_magic_word;
  m_eb_header[k_data_size]    = m_data_size;
  m_eb_header[k_event_number] = m_event_number;
  m_eb_header[k_run_number]   = m_run_number;
  m_eb_header[k_node_id]      = m_node_id;
  m_eb_header[k_event_type]   = m_event_type;
  m_eb_header[k_n_blocks]     = m_n_blocks;
  m_eb_header[k_reserved]     = m_reserved;
}

//_____________________________________________________________________
DAQNode::~DAQNode()
{
}

//_____________________________________________________________________
bool
DAQNode::Clear( void )
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");

  for( ModuleIterator itr=m_module_container.begin(),
	 itr_end=m_module_container.end(); itr!=itr_end; ++itr ){
    (*itr)->Clear();
  }

  return true;
}

//_____________________________________________________________________
bool
DAQNode::RegisterNode( DAQNode *node )
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");

  static NodeManager& node_manager = NodeManager::GetInstance();
  node_manager.AddNodeList( node );

  m_eb_header[k_n_blocks] = ++m_n_blocks;

  node->SetNest( m_nest+1 );
  m_node_container.push_back( node );

  return true;
}

//_____________________________________________________________________
bool
DAQNode::RegisterModule( DAQModule *module )
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");

  static NodeManager& node_manager = NodeManager::GetInstance();
  node_manager.AddModuleList( module );

  m_module_container.push_back( module );

  return true;
}

//_____________________________________________________________________
void
DAQNode::SetEventNumber( unsigned int number )
{
  m_event_number = number;
  m_eb_header[k_event_number] = m_event_number;
}

//_____________________________________________________________________
void
DAQNode::SetDataSize( unsigned int size )
{
  m_data_size = size;
  m_eb_header[k_data_size] = m_data_size;
}

//_____________________________________________________________________
void
DAQNode::SetDataSize( void )
{
  m_data_size = k_eb_header_length;
  m_data_size += k_node_header_length;

  for( NodeIterator itr=m_node_container.begin(),
	 itr_end=m_node_container.end(); itr!=itr_end; ++itr ){
    (*itr)->SetDataSize();
    (*itr)->SetLocalDataSize();
    m_data_size += (*itr)->GetDataSize();
  }

  for( ModuleIterator itr=m_module_container.begin(),
	 itr_end=m_module_container.end(); itr!=itr_end; ++itr ){
    m_data_size += (*itr)->GetDataSize();
  }

  m_eb_header[k_data_size] = m_data_size;
}

//_____________________________________________________________________
void
DAQNode::SetLocalDataSize( void )
{
}

//_____________________________________________________________________
DataWord
DAQNode::SummarizeDataWord( void ) const
{
  DataWord data;

  data.insert( data.end(), m_eb_header.begin(), m_eb_header.end() );
  data.insert( data.end(), m_node_header.begin(), m_node_header.end() );

  for( NodeIterator itr=m_node_container.begin(),
	 itr_end=m_node_container.end(); itr!=itr_end; ++itr ){
    DataWord child_data = (*itr)->SummarizeDataWord();
    data.insert( data.end(), child_data.begin(), child_data.end() );
  }

  for( ModuleIterator itr=m_module_container.begin(),
	 itr_end=m_module_container.end(); itr!=itr_end; ++itr ){
    DataWord module_header  = (*itr)->GetModuleHeader();
    DataWord module_data    = (*itr)->GetDataWord();
    DataWord module_trailer = (*itr)->GetModuleTrailer();
    data.insert( data.end(), module_header.begin(),  module_header.end() );
    data.insert( data.end(), module_data.begin(),    module_data.end() );
    data.insert( data.end(), module_trailer.begin(), module_trailer.end() );
  }

  return data;
}

//_____________________________________________________________________
void
DAQNode::PrintNodeList( void )
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");

  std::cout << "#D " << func_name << " " << m_node_name << std::endl;
  for( NodeIterator itr=m_node_container.begin(),
	 itr_end=m_node_container.end(); itr!=itr_end; ++itr ){
    std::cout << "   " << (*itr)->GetNodeName() << std::endl;
  }
}

//_____________________________________________________________________
void
DAQNode::PrintModuleList( void )
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");

  std::cout << "#D " << func_name << " " << m_node_name << std::endl;
  for( ModuleIterator itr=m_module_container.begin(),
	 itr_end=m_module_container.end(); itr!=itr_end; ++itr ){
    std::cout << "   " << (*itr)->GetModuleName() << std::endl;
  }
}

//_____________________________________________________________________
void
DAQNode::PrintModuleData( void )
{
  for( ModuleIterator itr=m_module_container.begin(),
	 itr_end=m_module_container.end(); itr!=itr_end; ++itr ){
    (*itr)->PrintDataWord();
  }
}
