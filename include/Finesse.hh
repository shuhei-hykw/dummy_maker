/**
 *  file: Finesse.hh
 *  date: 2016.02.01
 *
 */

#ifndef FINESSE_HH
#define FINESSE_HH

#include "DAQModule.hh"
#include "TypeDef.hh"

#include <vector>

//_____________________________________________________________________
class Finesse : public DAQModule
{
public:
  Finesse( const std::string& module_name,
	   const unsigned int slot_id, 
	   const unsigned int clite_id );
  ~Finesse();

private:
  Finesse( const Finesse& );
  Finesse& operator =( const Finesse& );

protected:
  enum e_module_header
    {
      // clite
      k_clite_header_magic,
      k_clite_slot_id,
      k_data_length, // data size of all finesse card, unit is byte
      k_clite_id,
      // finesse
      k_finesse_header_magic,
      k_local_tag,
      k_module_header_length
    };

  enum e_module_trailer
    {
      k_finesse_trailer_magic,
      k_clite_trailer_magic,
      k_module_trailer_length
    };

  const unsigned int k_clite_header_magic_word    = 0x7fff000a;
  const unsigned int k_clite_trailer_magic_word   = 0x00030000;
  const unsigned int k_finesse_header_magic_word  = 0xffaa0000;
  const unsigned int k_finesse_trailer_magic_word = 0xff550000;
  const unsigned int k_default_module_data_size   = 3*4;

protected:
  unsigned int m_slot_id;
  unsigned int m_clite_id;
  unsigned int m_data_length;
  unsigned int m_local_tag;
  unsigned int m_event_tag;
  unsigned int m_spill_tag;
  unsigned int m_serial_tag;

public:
  virtual bool Clear( void );
  void         SetModuleDataSize( unsigned int size );

};

#endif
