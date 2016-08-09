/**
 *  file: CopperLite.hh
 *  date: 2016.02.01
 *
 */

#ifndef COPPER_LITE_HH
#define COPPER_LITE_HH

#include "DAQNode.hh"

#include <vector>

//_____________________________________________________________________
class CopperLite : public DAQNode
{
public:
  explicit CopperLite( const std::string& node_name,
		       const unsigned int node_id );
  ~CopperLite( void );

private:
  CopperLite( const CopperLite& );
  CopperLite& operator =( const CopperLite& );

private:
  unsigned int m_local_data_size;

public:
  unsigned int GetLocalDataSize( void ) const { return m_local_data_size; }
  void         SetLocalDataSize( void )       { return; }

};

#endif
