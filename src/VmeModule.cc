/**
 *  file: VmeModule.cc
 *  date: 2016.01.28
 *
 */

#include "VmeModule.hh"
#include "DAQModule.hh"

#include <iostream>
#include <string>

static const std::string class_name("VmeModule");

//_____________________________________________________________________
VmeModule::VmeModule( const std::string& module_name,
		      const unsigned int base_address )
  : DAQModule( module_name ),
    m_base_address(base_address),
    m_n_times_read_device(0),
    m_module_type1(0),
    m_module_type2(0),
    m_tv_sec(0),
    m_tv_nsec(0)
{
  m_module_header.resize( k_module_header_length*2 );
  m_module_header[k_vme_module_magic*2+0]     = k_vme_module_magic_word2;
  m_module_header[k_vme_module_magic*2+1]     = k_vme_module_magic_word1;
  m_module_header[k_base_address*2+0]         = m_base_address;
  m_module_header[k_base_address*2+1]         = 0;
  m_module_header[k_data_size*2+0]            = m_data_size;
  m_module_header[k_data_size*2+1]            = 0;
  m_module_header[k_n_times_read_device*2+0]  = m_n_times_read_device;
  m_module_header[k_n_times_read_device*2+1]  = 0;
  m_module_header[k_module_type1*2+0]         = m_module_type1;
  m_module_header[k_module_type1*2+1]         = 0;
  m_module_header[k_module_type2*2+0]         = m_module_type2;
  m_module_header[k_module_type2*2+1]         = 0;
  m_module_header[k_tv_sec*2+0]               = m_tv_sec;
  m_module_header[k_tv_sec*2+1]               = 0;
  m_module_header[k_tv_nsec*2+0]              = m_tv_nsec;
  m_module_header[k_tv_nsec*2+1]              = 0;

  m_module_trailer.clear();
}

//_____________________________________________________________________
VmeModule::~VmeModule()
{
}

//_____________________________________________________________________
bool
VmeModule::Clear( void )
{
  return true;
}

//_____________________________________________________________________
void
VmeModule::SetModuleDataSize( unsigned int size )
{
  m_data_size = size;
  m_module_header[k_data_size*2+0] = m_data_size;
}
