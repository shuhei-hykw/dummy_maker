/**
 *  file: VmeCaenV792.hh
 *  date: 2016.01.19
 *
 */

#ifndef VME_CAEN_V792_HH
#define VME_CAEN_V792_HH

#include "VmeModule.hh"

#include <string>
#include <vector>

//_____________________________________________________________________
class VmeCaenV792 : public VmeModule
{
public:
  explicit VmeCaenV792( const std::string& module_name,
			const unsigned int base_address );
  ~VmeCaenV792( void );

private:
  VmeCaenV792( const VmeCaenV792& );
  VmeCaenV792& operator =( const VmeCaenV792& );

private:
  // general
  static const unsigned int k_n_channel       = 32;
  static const unsigned int k_word_type_shift = 24;
  static const unsigned int k_word_type_mask  = 0x7;
  static const unsigned int k_header_magic    = 0x2;
  static const unsigned int k_data_magic      = 0x0;
  static const unsigned int k_footer_magic    = 0x4;
  static const unsigned int k_invalid_magic   = 0x6;
  // header
  static const unsigned int k_header_position         = 0;
  static const unsigned int k_memorised_channel_shift = 8;
  static const unsigned int k_memorised_channel_mask  = 0x3f;
  static const unsigned int k_crate_number_shift      = 16;
  static const unsigned int k_crate_number_mask       = 0xff;
  static const unsigned int k_header_geo_shift        = 27;
  static const unsigned int k_header_geo_mask         = 0x1f;
  // body
  static const unsigned int k_body_position         = 1;
  static const unsigned int k_data_shift            = 0;
  static const unsigned int k_data_mask             = 0xfff;
  static const unsigned int k_overflow_shift        = 12;
  static const unsigned int k_overflow_mask         = 0x1;
  static const unsigned int k_under_threshold_shift = 13;
  static const unsigned int k_under_threshold_mask  = 0x1;
  static const unsigned int k_channel_shift         = 16;
  static const unsigned int k_channel_mask          = 0x3f;
  static const unsigned int k_data_geo_shift        = 27;
  static const unsigned int k_data_geo_mask         = 0x1f;
  // footer
  static const unsigned int k_footer_position    = k_n_channel+1;
  static const unsigned int k_event_number_shift = 0;
  static const unsigned int k_event_number_mask  = 0xffffff;
  static const unsigned int k_footer_geo_shift   = 27;
  static const unsigned int k_footer_geo_mask    = 0x1f;

private:
  unsigned int m_geo_address;
  unsigned int m_memorised_channel;
  unsigned int m_crate_number;
  unsigned int m_overflow[k_n_channel];
  unsigned int m_under_threshold[k_n_channel];
  unsigned int m_adc[k_n_channel];

public:
  bool     Clear( void );
  bool     SetAdc( unsigned int channel, unsigned int adc );

};

#endif
