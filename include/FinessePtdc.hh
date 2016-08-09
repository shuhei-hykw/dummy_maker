/**
 *  file: FinessePtdc.hh
 *  date: 2016.01.19
 *
 */

#ifndef FINESSE_PTDC_HH
#define FINESSE_PTDC_HH

#include "Finesse.hh"

#include <string>
#include <vector>

//_____________________________________________________________________
class FinessePtdc : public Finesse
{
public:
  explicit FinessePtdc( const std::string& module_name,
			const unsigned int slot_id, 
			const unsigned int clite_id );
  ~FinessePtdc( void );

private:
  FinessePtdc( const FinessePtdc& );
  FinessePtdc& operator =( const FinessePtdc& );

private:
  static const unsigned int k_n_channel        = 32;
  static const unsigned int k_n_depth          = 256;
  static const unsigned int k_data_shift       = 0;
  static const unsigned int k_data_mask        = 0x3ff;
  static const unsigned int k_channel_shift    = 16;
  static const unsigned int k_channel_mask     = 0x1f;
  static const unsigned int k_empty_flag_shift = 21;
  static const unsigned int k_empty_flag_mask  = 0x1;

private:
  unsigned int m_tdc[k_n_channel];
  unsigned int m_empty_flag[k_n_channel];

public:
  bool     Clear( void );
  bool     SetTdc( unsigned int channel, unsigned int tdc );

};

#endif
