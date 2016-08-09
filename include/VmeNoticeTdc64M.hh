/**
 *  file: VmeNoticeTdc64M.hh
 *  date: 2016.01.18
 *
 */

#ifndef VME_NOTICE_TDC64M_HH
#define VME_NOTICE_TDC64M_HH

#include "VmeModule.hh"

#include <string>
#include <vector>

//_____________________________________________________________________
class VmeNoticeTdc64M : public VmeModule
{
public:
  explicit VmeNoticeTdc64M( const std::string& module_name,
			    const unsigned int base_address );
  ~VmeNoticeTdc64M( void );

private:
  VmeNoticeTdc64M( const VmeNoticeTdc64M& );
  VmeNoticeTdc64M& operator =( const VmeNoticeTdc64M& );

private:
  // general
  static const unsigned int k_n_channel       = 64;
  static const unsigned int k_word_type_shift = 28;
  static const unsigned int k_word_type_mask  = 0xf;
  static const unsigned int k_header_magic    = 0xa;
  static const unsigned int k_data_magic      = 0xc;
  static const unsigned int k_footer_magic    = 0xe;
  static const unsigned int k_invalid_magic   = 0x3;
  // header
  static const unsigned int k_header_position = 0;
  static const unsigned int k_data_size_shift = 0;
  static const unsigned int k_data_size_mask  = 0xfff;
  static const unsigned int k_module_id_shift = 16;
  static const unsigned int k_module_id_mask  = 0x1f;
  static const unsigned int k_emode_shift = 24;
  static const unsigned int k_emode_mask  = 0x1;
  static const unsigned int k_gmode_shift = 25;
  static const unsigned int k_gmode_mask  = 0x1;
  // body
  static const unsigned int k_body_position    = 1;
  static const unsigned int k_data_shift       = 0;
  static const unsigned int k_data_mask        = 0x1ffff;
  static const unsigned int k_hit_number_shift = 17;
  static const unsigned int k_hit_number_mask  = 0xf;
  static const unsigned int k_channel_shift    = 21;
  static const unsigned int k_channel_mask     = 0x3f;
  static const unsigned int k_edge_shift       = 27;
  static const unsigned int k_edge_mask        = 0x1;
  // footer
  static const unsigned int k_footer_position    = k_n_channel+1;
  static const unsigned int k_event_number_shift = 0;
  static const unsigned int k_event_number_mask  = 0xffff;
  static const unsigned int k_error1_shift       = 16;
  static const unsigned int k_error1_mask        = 0x1;
  static const unsigned int k_error2_shift       = 17;
  static const unsigned int k_error2_mask        = 0x1;
  static const unsigned int k_error3_shift       = 18;
  static const unsigned int k_error3_mask        = 0x1;
  static const unsigned int k_error4_shift       = 19;
  static const unsigned int k_error4_mask        = 0x1;

private:
  unsigned int m_module_id;
  unsigned int m_emode;
  unsigned int m_gmode;
  unsigned int m_tdc[k_n_channel];
  unsigned int m_hit_number[k_n_channel];
  unsigned int m_edge[k_n_channel];
  unsigned int m_event_number;
  unsigned int m_error1;
  unsigned int m_error2;
  unsigned int m_error3;
  unsigned int m_error4;

public:
  bool     Clear( void );
  bool     SetTdc( int channel, int tdc );

};

#endif
