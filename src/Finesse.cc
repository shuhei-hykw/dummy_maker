/**
 *  file: Finesse.cc
 *  date: 2016.01.19
 *
 */

#include "Finesse.hh"
#include "DAQModule.hh"

#include <iostream>
#include <string>

static const std::string class_name("Finesse");

//_____________________________________________________________________
Finesse::Finesse( const std::string& module_name,
		  const unsigned int slot_id, 
		  const unsigned int clite_id )
  : DAQModule( module_name ),
    m_slot_id(slot_id),
    m_clite_id(clite_id),
    m_data_length(3*4),
    m_local_tag(0),
    m_event_tag(0),
    m_spill_tag(0)
{
  m_module_header.resize( k_module_header_length );
  m_module_header[k_clite_header_magic]   = k_clite_header_magic_word;
  m_module_header[k_clite_slot_id]        = slot_id;
  m_module_header[k_data_length]          = m_data_length;
  m_module_header[k_clite_id]             = m_clite_id;
  m_module_header[k_finesse_header_magic] = k_finesse_header_magic_word;
  m_module_header[k_local_tag]            = 0;

  m_module_trailer.resize( k_module_trailer_length );
  m_module_trailer[k_finesse_trailer_magic] = k_finesse_trailer_magic_word;
  m_module_trailer[k_clite_trailer_magic]   = k_clite_trailer_magic_word;
}

//_____________________________________________________________________
Finesse::~Finesse()
{
}

//_____________________________________________________________________
bool
Finesse::Clear( void )
{
  return true;
}

//_____________________________________________________________________
void
Finesse::SetModuleDataSize( unsigned int size )
{
  m_data_size   = size;
  m_data_length = size/4;
  m_module_header[k_data_length] = m_data_length;
}
