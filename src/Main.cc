/**
 *  file: Main.cc
 *  date: 2016.04.26
 *
 */

#include "EventManager.hh"
#include "EventRecorder.hh"
#include "DAQNode.hh"
#include "DCGeomMan.hh"
#include "DetectorManager.hh"
#include "NodeManager.hh"
#include "VmeCaenV792.hh"
#include "VmeNode.hh"

#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <libgen.h>
#include <signal.h>
#include <sys/stat.h>

#include <TString.h>

enum e_argc
  {
    k_process,
    k_root_file_name,
    // k_dummy_file_name,
    k_argc
  };

static const std::string class_name("");
unsigned int g_run_number   = 0;
unsigned int g_event_number = 0;
bool         g_user_stop    = false;

//_____________________________________________________________________
void
catch_signal( int sig )
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");
  g_user_stop = true;
  std::cout << "\x1b[2D\x1b[1m"
	    << "#D " << func_name << "() catch signal " << sig
	    << " ... exit process   \x1b[0m" << std::endl;
}

//_____________________________________________________________________
int
main(int argc, char **argv)
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");

  const std::string process = basename(argv[k_process]);

  if(argc!=k_argc){
    std::cerr << "#D Usage: " << process
	      << " [root_file] " << std::endl;
      //<< " [root_file] [dummy_file]" << std::endl;
    return EXIT_SUCCESS;
  }

  ////////// initialize
  std::string root_file_name  = argv[k_root_file_name];
  // const std::string dummy_file_name = argv[k_dummy_file_name];
  EventManager&    event_manager    = EventManager::GetInstance();
  EventRecorder&   event_recorder   = EventRecorder::GetInstance();
  NodeManager&     node_manager     = NodeManager::GetInstance();
  DetectorManager& detector_manager = DetectorManager::GetInstance();
  DCGeomMan&       geom_manager     = DCGeomMan::GetInstance();
  event_manager.SetFileName( root_file_name );

  event_manager.Initialize();
  event_recorder.Initialize();
  node_manager.Initialize();
  detector_manager.Initialize();
  geom_manager.Initialize("DCGeomParam_Dummy");

  ////////// event loop
  signal( SIGINT, catch_signal );
  for( unsigned int nentries = event_manager.GetEntries();
       g_event_number<nentries && !g_user_stop; ++g_event_number ){

      event_manager.InitializeEvent();
      event_manager.ProcessEvent();
      event_manager.FinalizeEvent();

  }

  event_manager.Finalize();
  event_recorder.Finalize();

  std::cout << "#D " << func_name << " "
	    << "End of DummyMaker " << std::endl;
  
  return EXIT_SUCCESS;
}

