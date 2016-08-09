/**
 *  file: DAQNode.hh
 *  date: 2016.02.01
 *
 */

#ifndef DAQ_NODE_HH
#define DAQ_NODE_HH

#include "TypeDef.hh"

#include <string>
#include <vector>

//_____________________________________________________________________
class DAQNode
{
public:
  DAQNode( const std::string& node_name,  const unsigned int node_id );
  ~DAQNode();

private:
  DAQNode( const DAQNode& );
  DAQNode& operator =( const DAQNode& );

protected:
  enum e_eb_header
    {
      k_eb_magic, k_data_size,  k_event_number, k_run_number,
      k_node_id,    k_event_type, k_n_blocks,     k_reserved,
      k_eb_header_length
    };
  const unsigned int k_eb_magic_word      = 0x45564e54U;
  unsigned int       k_node_header_length = 0;

protected:
  unsigned int    m_nest;
  std::string     m_node_name;
  std::string     m_node_type;
  DataWord        m_eb_header;
  DataWord        m_node_header;
  NodeContainer   m_node_container;
  ModuleContainer m_module_container;
  unsigned int    m_data_size;
  unsigned int    m_event_number;
  unsigned int    m_run_number;
  unsigned int    m_node_id;
  unsigned int    m_event_type;
  unsigned int    m_n_blocks;
  unsigned int    m_reserved;

public:
  bool            Clear( void );
  unsigned int    GetNest( void )            const { return m_nest; }
  std::string     GetNodeName( void )        const { return m_node_name; }
  std::string     GetNodeType( void )        const { return m_node_type; }
  DataWord        GetEBHeader( void )        const { return m_eb_header; }
  DataWord        GetNodeHeader( void )      const { return m_node_header; }
  NodeContainer   GetNodeContainer( void )   const { return m_node_container; }
  ModuleContainer GetModuleContainer( void ) const { return m_module_container; }
  unsigned int    GetDataSize( void )        const { return m_data_size; }
  unsigned int    GetEventNumber( void )     const { return m_event_number;  }
  unsigned int    GetRunNumber( void )       const { return m_run_number; }
  unsigned int    GetNodeId( void )          const { return m_node_id; }
  bool            RegisterNode( DAQNode *node );
  virtual bool    RegisterModule( DAQModule *module );
  void            SetNest( unsigned int nest ){ m_nest = nest; }
  void            SetNodeName( const std::string& name ){ m_node_name = name; }
  void            SetEventNumber( unsigned int number );
  void            SetDataSize( unsigned int size );
  void            SetDataSize( void );
  virtual void    SetLocalDataSize( void );
  DataWord        SummarizeDataWord( void ) const;
  void            PrintNodeList( void );
  void            PrintModuleList( void );
  void            PrintModuleData( void );

};

#endif
