/**
 *  file: NodeManager.hh
 *  date: 2016.02.01
 *
 */

#ifndef NODE_MANAGER_HH
#define NODE_MANAGER_HH

#include "DAQNode.hh"
#include "TypeDef.hh"

#include <iterator>
#include <map>
#include <string>
#include <vector>

//_____________________________________________________________________
class NodeManager
{
public:
  static NodeManager& GetInstance( void );
  ~NodeManager( void );

private:
  explicit NodeManager( void );
  NodeManager( const NodeManager& );
  NodeManager& operator =( const NodeManager& );

private:
  static NodeManager *m_node_manager;
  NodeContainer       m_node_container;
  NodeList            m_node_list;
  ModuleList          m_module_list;
  DataWord            m_data_word;

public:
  bool          AddNodeList( DAQNode* node );
  bool          AddModuleList( DAQModule* module );
  bool          Clear( void );
  bool          Initialize( void );
  NodeContainer GetNodeContainer( void ) const { return m_node_container; }
  DataWord      GetDataWord( void ) const { return m_data_word; }
  DAQNode*      GetNode( const std::string& name );
  DAQModule*    GetModule( const std::string& name );
  bool          RegisterNode( DAQNode *node );
  bool          SetEventNumber( unsigned int event_number );
  void          PrintNodeList( void );
  void          PrintModuleList( void );
  void          PrintRegisteredAll( void );

};

#endif
