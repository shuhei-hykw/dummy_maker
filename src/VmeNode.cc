/**
 *  file: VmeNode.cc
 *  date: 2016.01.28
 *
 */

#include "VmeNode.hh"
#include "DAQNode.hh"
#include "NodeManager.hh"

#include <iostream>
#include <string>

extern unsigned int g_run_number;

static const std::string class_name("VmeNode");

//_____________________________________________________________________
VmeNode::VmeNode( const std::string& node_name, const unsigned int node_id )
  : DAQNode( node_name, node_id ),
    m_vme_data_size(0),
    m_vme_n_blocks(0)
{
  m_node_type = "VmeNode";
  m_node_header.resize( k_node_header_length );
  m_node_header[k_vme_master_magic] = k_vme_master_magic_word;
  m_node_header[k_vme_data_size]    = m_vme_data_size;
  m_node_header[k_vme_n_blocks]     = m_vme_n_blocks;
  DAQNode::k_node_header_length = VmeNode::k_node_header_length;
}

//_____________________________________________________________________
VmeNode::~VmeNode()
{
}

//_____________________________________________________________________
bool
VmeNode::RegisterModule( DAQModule *module )
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");

  static NodeManager& node_manager = NodeManager::GetInstance();
  node_manager.AddModuleList( module );

  m_node_header[k_vme_n_blocks] = ++m_vme_n_blocks;

  m_module_container.push_back( module );

  return true;
}

//_____________________________________________________________________
void
VmeNode::SetLocalDataSize( void )
{
  m_vme_data_size = m_data_size - k_eb_header_length;
  m_node_header[k_vme_data_size] = m_vme_data_size;
}
