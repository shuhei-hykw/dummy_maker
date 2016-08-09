/**
 *  file: DAQModule.cc
 *  date: 2016.02.01
 *
 */

#include "DAQModule.hh"

#include <iomanip>
#include <iostream>
#include <string>

static const std::string class_name("DAQModule");

//_____________________________________________________________________
DAQModule::DAQModule( const std::string& module_name )
  : m_module_name( module_name ),
    m_module_type("DAQModule"),
    m_data_size(0)
{
}

//_____________________________________________________________________
DAQModule::~DAQModule( void )
{
}

//_____________________________________________________________________
bool
DAQModule::Clear( void )
{
  return true;
}

//_____________________________________________________________________
void
DAQModule::PrintModuleHeader( void )
{
  for( int i=0, n=m_module_header.size(); i<n; ++i){
    std::cout << std::hex << std::setw(8) << std::setfill('0')
	      << m_module_header[i] << std::endl;
  }
}

//_____________________________________________________________________
void
DAQModule::PrintDataWord( void )
{
  for( int i=0, n=m_data_word.size(); i<n; ++i){
    std::cout << std::hex << std::setw(8) << std::setfill('0')
	      << m_data_word[i] << std::endl;
  }
}

//_____________________________________________________________________
void
DAQModule::PrintModuleTrailer( void )
{
  for( int i=0, n=m_module_trailer.size(); i<n; ++i){
    std::cout << std::hex << std::setw(8) << std::setfill('0')
	      << m_module_trailer[i] << std::endl;
  }
}

//_____________________________________________________________________
void
DAQModule::SetModuleName( const std::string& name )
{
  m_module_name = name;
}
