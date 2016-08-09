/**
 *  file: EventRecorder.cc
 *  date: 2016.04.25
 *
 */

#include "EventRecorder.hh"

#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <sys/stat.h>
#include <zlib.h>

extern unsigned int g_run_number;
EventRecorder *EventRecorder::m_event_recorder = 0;

static const std::string class_name("EventRecorder");

//_____________________________________________________________________
EventRecorder::EventRecorder( void )
  : m_file(0),
    m_file_name(""),
    m_is_open(false)
{
}

//_____________________________________________________________________
EventRecorder::~EventRecorder( void )
{
}

//_____________________________________________________________________
EventRecorder&
EventRecorder::GetInstance( void )
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");
  if( !m_event_recorder )
    m_event_recorder = new EventRecorder;
  return *m_event_recorder;
}

//_____________________________________________________________________
bool
EventRecorder::Initialize( void )
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");

  std::ostringstream name;
  name << "./data/run" << std::setw(5) << std::setfill('0')
       << g_run_number << ".dat.gz";

  struct stat st;
  while( !stat( name.str().c_str(), &st ) ){
    name.str("");
    name.clear( std::stringstream::goodbit );
    name << "./data/run" << std::setw(5) << std::setfill('0')
	 << ++g_run_number << ".dat.gz";
    if( g_run_number>=100000 ){
      return EXIT_FAILURE;
    }
  }

  m_file_name = name.str();
  m_file = gzopen( m_file_name.c_str(), "wb6" );
  if( !m_file ){
    std::cout << "#D " << func_name << " cannot open file : "
	      << m_file_name << std::endl;
    std::exit(EXIT_FAILURE);
  }

  std::cout << "#D " << func_name << " open file : "
	    << m_file_name << std::endl;
  return m_is_open = true;
}

//_____________________________________________________________________
bool
EventRecorder::Finalize( void )
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");

  std::cout << "#D " << func_name << " close file : "
	    << m_file_name << std::endl;
  gzclose( m_file );
  chmod( m_file_name.c_str(), S_IRUSR | S_IRGRP | S_IROTH );
  m_is_open = false;
  return true;
}

//_____________________________________________________________________
bool
EventRecorder::Write( const DataWord& data )
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");

  static const size_t data_width = sizeof( unsigned int );
  if( !m_is_open ) return false;

  for( DataWordIterator itr=data.begin(), itr_end=data.end();
       itr!=itr_end; ++itr ){
#if 0
    if(itr==data.begin()) std::cout << "#D " << func_name << std::endl;
    std::cout << std::hex << std::setw(8) << std::setfill('0')
	      << *itr << std::endl;
#endif
    gzwrite( m_file, &*itr, data_width );
  }

  return true;
}
