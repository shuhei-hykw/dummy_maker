/**
 *  file: FinessePtdc.cc
 *  date: 2016.01.19
 *
 */

#include "FinessePtdc.hh"

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

extern unsigned int g_event_number;

static const std::string class_name("FinessePtdc");

//_____________________________________________________________________
FinessePtdc::FinessePtdc( const std::string& module_name,
			  const unsigned int slot_id, 
			  const unsigned int clite_id )
  : Finesse( module_name, slot_id, clite_id )
{
  m_module_type = "FinessePtdc";
}

//_____________________________________________________________________
FinessePtdc::~FinessePtdc( void )
{
  m_module_header.clear();
  m_data_word.clear();
}

//_____________________________________________________________________
bool
FinessePtdc::Clear( void )
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");

  for( int channel=0; channel<k_n_channel; ++channel ){
    m_empty_flag[channel] = 0;
  }

  SetModuleDataSize( k_default_module_data_size );
  m_data_word.clear();
  m_local_tag  = 0;
  m_event_tag  = 0;
  m_spill_tag  = 0;
  m_serial_tag = 0;
  
  return true;
}

//_____________________________________________________________________
bool
FinessePtdc::SetTdc( unsigned int channel, unsigned int tdc )
{
  if( channel>=k_n_channel ) return false;

  SetModuleDataSize( ++m_data_size );

  m_tdc[channel] = tdc;

  m_data_word[channel]
    = ( ( m_tdc[channel] & k_data_mask ) << k_data_shift )
    | ( ( channel & k_channel_mask ) << k_channel_shift )
    | ( ( m_empty_flag[channel] & k_empty_flag_mask ) << k_empty_flag_shift );

  return true;
}



