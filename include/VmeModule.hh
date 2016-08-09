/**
 *  file: VmeModule.hh
 *  date: 2016.02.01
 *
 */

#ifndef VME_MODULE_HH
#define VME_MODULE_HH

#include "DAQModule.hh"
#include "TypeDef.hh"

#include <vector>

//_____________________________________________________________________
class VmeModule : public DAQModule
{
public:
  VmeModule( const std::string& module_name,
	     const unsigned int base_address );
  ~VmeModule();

private:
  VmeModule( const VmeModule& );
  VmeModule& operator =( const VmeModule& );

protected:
  enum e_module_header
    {
      k_vme_module_magic,
      k_base_address,
      k_data_size,
      k_n_times_read_device,
      k_module_type1,
      k_module_type2,
      k_tv_sec,
      k_tv_nsec,
      k_module_header_length
    };
  const unsigned int k_vme_module_magic_word1 = 0x766d6562;
  const unsigned int k_vme_module_magic_word2 = 0x6f617264;

protected:
  unsigned int m_base_address;
  unsigned int m_n_times_read_device;
  unsigned int m_module_type1;
  unsigned int m_module_type2;
  unsigned int m_tv_sec;
  unsigned int m_tv_nsec;

public:
  virtual bool Clear( void );
  void         SetModuleDataSize( unsigned int size );

};

#endif
