/**
 *  file: VmeNoticeTdc64M.cc
 *  date: 2016.05.04
 *
 */

#include "VmeNoticeTdc64M.hh"

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

extern unsigned int g_event_number;

static const std::string class_name("VmeNoticeTdc64M");

//_____________________________________________________________________
VmeNoticeTdc64M::VmeNoticeTdc64M( const std::string& module_name,
				  const unsigned int base_address )
  : VmeModule( module_name, base_address ),
    m_module_id(0),
    m_emode(0),
    m_gmode(0),
    m_event_number(0),
    m_error1(0),
    m_error2(0),
    m_error3(0),
    m_error4(0)
{
  m_module_type = "VmeNoticeTdc64M";

  m_data_word.resize( k_n_channel + 2 );
  SetModuleDataSize( m_module_header.size() + m_data_word.size() );

  ////////// header
  m_data_word[k_header_position]
    = ( ( m_data_size & k_data_size_mask ) << k_data_size_shift )
    | ( ( m_module_id & k_module_id_mask ) << k_module_id_shift )
    | ( ( m_emode & k_emode_mask ) << k_emode_shift )
    | ( ( m_gmode & k_gmode_mask ) << k_gmode_shift )
    | ( ( k_header_magic & k_word_type_mask ) << k_word_type_shift );
  
  // ////////// footer
  m_data_word[k_footer_position]
    = ( ( g_event_number & k_event_number_mask ) << k_event_number_shift )
    | ( ( m_error1 & k_error1_mask ) << k_error1_shift )
    | ( ( m_error2 & k_error2_mask ) << k_error2_shift )
    | ( ( m_error3 & k_error3_mask ) << k_error3_shift )
    | ( ( m_error4 & k_error4_mask ) << k_error4_shift )
    | ( ( k_footer_magic & k_word_type_mask ) << k_word_type_shift );

}

//_____________________________________________________________________
VmeNoticeTdc64M::~VmeNoticeTdc64M( void )
{
  m_module_header.clear();
  m_data_word.clear();
}

//_____________________________________________________________________
bool
VmeNoticeTdc64M::Clear( void )
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");

  for( int channel=0; channel<k_n_channel; ++channel ){
    SetTdc( channel, 0 );
  }

  m_error1 = 0;
  m_error2 = 0;
  m_error3 = 0;
  m_error4 = 0;

  return true;
}

//_____________________________________________________________________
bool
VmeNoticeTdc64M::SetTdc( int channel, int tdc )
{
  if( channel>=k_n_channel ) return false;

  m_tdc[channel] = tdc;

  m_data_word[channel+1]
    = ( ( m_tdc[channel] & k_data_mask ) << k_data_shift )
    | ( ( m_hit_number[channel] & k_hit_number_mask )
	<< k_hit_number_shift )
    | ( ( channel & k_channel_mask ) << k_channel_shift )
    | ( ( m_edge[channel] & k_edge_mask ) << k_edge_shift )
    | ( ( k_data_magic & k_word_type_mask ) << k_word_type_shift );

  return true;
}



