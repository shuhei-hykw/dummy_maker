/**
 *  file: DAQModule.hh
 *  date: 2016.02.01
 *
 */

#ifndef DAQ_MODULE_HH
#define DAQ_MODULE_HH

#include "TypeDef.hh"

#include <string>
#include <vector>

//_____________________________________________________________________
class DAQModule
{
public:
  DAQModule( const std::string& module_name );
  ~DAQModule( void );

private:
  DAQModule( const DAQModule& );
  DAQModule& operator =( const DAQModule& );

protected:
  std::string  m_module_name;
  std::string  m_module_type;
  DataWord     m_module_header;
  DataWord     m_data_word;
  DataWord     m_module_trailer;
  unsigned int m_data_size;

public:
  virtual bool Clear( void );
  std::string  GetModuleName( void )    const { return m_module_name;    }
  std::string  GetModuleType( void )    const { return m_module_type;    }
  DataWord     GetModuleHeader( void )  const { return m_module_header;  }
  DataWord     GetDataWord( void )      const { return m_data_word;      }
  DataWord     GetModuleTrailer( void ) const { return m_module_trailer; }
  unsigned int GetDataSize( void )      const { return m_data_size;      }
  void         PrintModuleHeader( void );
  void         PrintDataWord( void );
  void         PrintModuleTrailer( void );
  void         SetModuleName( const std::string& name );

};

#endif
