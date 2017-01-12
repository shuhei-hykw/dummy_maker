/**
 *  file: VmeCaenV792.cc
 *  date: 2017.01.12
 *
 */

#include "VmeCaenV792.hh"

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

extern unsigned int g_event_number;

static const std::string class_name("VmeCaenV792");

//_____________________________________________________________________
VmeCaenV792::VmeCaenV792( const std::string& module_name,
			  const unsigned int base_address )
  : VmeModule( module_name, base_address ),
    m_geo_address(0x1f),
    m_memorised_channel(0),
    m_crate_number(0)
{
  m_module_type = "VmeCaenV792";

  m_data_word.resize( k_n_channel + 2 );
  SetModuleDataSize( m_module_header.size() + m_data_word.size() );

  ////////// header
  m_data_word[k_header_position]
    = ( ( m_memorised_channel & k_memorised_channel_mask )
  	<< k_memorised_channel_shift )
    | ( ( m_crate_number & k_crate_number_mask ) << k_crate_number_shift )
    | ( ( m_geo_address & k_header_geo_mask ) << k_header_geo_shift )
    | ( ( k_header_magic & k_word_type_mask ) << k_word_type_shift );

  // ////////// footer
  m_data_word[k_footer_position]
    = ( ( g_event_number & k_event_number_mask ) << k_event_number_shift )
    | ( ( m_geo_address & k_footer_geo_mask ) << k_footer_geo_shift )
    | ( ( k_footer_magic & k_word_type_mask ) << k_word_type_shift );

}

//_____________________________________________________________________
VmeCaenV792::~VmeCaenV792( void )
{
  m_module_header.clear();
  m_data_word.clear();
}

//_____________________________________________________________________
bool
VmeCaenV792::Clear( void )
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");

  for( std::size_t channel=0; channel<k_n_channel; ++channel ){
    SetAdc( channel, 0 );
    m_overflow[channel]        = 0;
    m_under_threshold[channel] = 0;
  }

  m_memorised_channel = 0;
  m_crate_number      = 0;

  return true;
}

//_____________________________________________________________________
bool
VmeCaenV792::SetAdc( unsigned int channel, unsigned int adc )
{
  if( channel>=k_n_channel )
    return false;
  if( adc < 0. )
    adc = 0;
  if( adc > k_data_mask )
    adc = k_data_mask;

  m_memorised_channel++;
  m_adc[channel] = adc;

  m_data_word[channel+1]
    = ( ( m_adc[channel] & k_data_mask ) << k_data_shift )
    | ( ( m_overflow[channel] & k_overflow_mask ) << k_overflow_shift )
    | ( ( m_under_threshold[channel] & k_under_threshold_mask )
	<< k_under_threshold_shift )
    | ( ( channel & k_channel_mask ) << k_channel_shift )
    | ( ( m_geo_address & k_data_geo_mask ) << k_data_geo_shift )
    | ( ( k_data_magic & k_word_type_mask ) << k_word_type_shift );

  return true;
}
