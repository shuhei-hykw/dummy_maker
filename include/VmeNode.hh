/**
 *  file: VmeNode.hh
 *  date: 2016.02.01
 *
 */

#ifndef VME_NODE_HH
#define VME_NODE_HH

#include "DAQNode.hh"
#include "TypeDef.hh"

#include <vector>

//_____________________________________________________________________
class VmeNode : public DAQNode
{
public:
  explicit VmeNode( const std::string& node_name, const unsigned int node_id );
  ~VmeNode();

private:
  VmeNode( const VmeNode& );
  VmeNode& operator =( const VmeNode& );

private:
  enum e_node_header
    {
      k_vme_master_magic, k_vme_data_size, k_vme_n_blocks,
      k_node_header_length
    };
  const unsigned int k_vme_master_magic_word = 0x00564d45;

private:
  unsigned int m_vme_data_size;
  unsigned int m_vme_n_blocks;

public:
  unsigned int GetLocalDataSize( void )     const { return m_vme_data_size; }
  bool         RegisterModule( DAQModule *module );
  void         SetLocalDataSize( void );

};

#endif
