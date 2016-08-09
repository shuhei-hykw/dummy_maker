/**
 *  file: EventRecorder.hh
 *  date: 2016.02.01
 *
 */

#ifndef EVENT_RECORDER_HH
#define EVENT_RECORDER_HH

#include "TypeDef.hh"

#include <string>
#include <vector>
#include <zlib.h>

class NodeHeader;

//_____________________________________________________________________
class EventRecorder
{
public:
  static EventRecorder& GetInstance( void );
  ~EventRecorder( void );

private:
  explicit EventRecorder( void );
  EventRecorder( const EventRecorder& );
  EventRecorder& operator =( const EventRecorder& );

private:
  static EventRecorder *m_event_recorder;
  gzFile                m_file;
  std::string           m_file_name;
  bool                  m_is_open;

public:
  bool        Initialize( void );
  bool        Finalize( void );
  bool        IsOpen( void ) const { return m_is_open; }
  std::string GetFileName( void ) const { return m_file_name; }
  void        SetFileName( const std::string& file_name ){ m_file_name = file_name; }
  bool        Write( const DataWord& data );

};

#endif
