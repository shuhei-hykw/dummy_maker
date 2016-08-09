/**
 *  file: CopperLite.cc
 *  date: 2016.02.01
 *
 */

#include "CopperLite.hh"
#include "DAQNode.hh"

#include <string>

extern unsigned int g_run_number;

static const std::string class_name("CopperLite");

//_____________________________________________________________________
CopperLite::CopperLite( const std::string& node_name, const unsigned int node_id )
  : DAQNode( node_name, node_id ),
    m_local_data_size(0)
{
  m_node_type = "CopperLite";
  m_node_header.clear();
}

//_____________________________________________________________________
CopperLite::~CopperLite( void )
{
}
