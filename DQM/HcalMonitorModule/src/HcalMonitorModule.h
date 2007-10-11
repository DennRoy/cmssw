#ifndef HcalMonitorModule_H
#define HcalMonitorModule_H

/*
 * \file HcalMonitorModule.h
 *
 * $Date: 2007/10/04 21:03:12 $
 * $Revision: 1.17 $
 * \author W. Fisher
 *
*/

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DQMServices/Core/interface/DaqMonitorBEInterface.h"
#include "DQMServices/Daemon/interface/MonitorDaemon.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "Geometry/Records/interface/IdealGeometryRecord.h"
#include "Geometry/CaloGeometry/interface/CaloGeometry.h"
#include "DataFormats/Provenance/interface/EventID.h"  
#include "DataFormats/HcalDigi/interface/HcalUnpackerReport.h"
#include "DQMServices/Components/interface/DQMAnalyzer.h"

#include "DQM/HcalMonitorModule/interface/HcalMonitorSelector.h"
#include "DQM/HcalMonitorTasks/interface/HcalDigiMonitor.h"
#include "DQM/HcalMonitorTasks/interface/HcalDataFormatMonitor.h"
#include "DQM/HcalMonitorTasks/interface/HcalRecHitMonitor.h"
#include "DQM/HcalMonitorTasks/interface/HcalTrigPrimMonitor.h"
#include "DQM/HcalMonitorTasks/interface/HcalPedestalMonitor.h"
#include "DQM/HcalMonitorTasks/interface/HcalLEDMonitor.h"
#include "DQM/HcalMonitorTasks/interface/HcalMTCCMonitor.h"
#include "DQM/HcalMonitorTasks/interface/HcalHotCellMonitor.h"
#include "DQM/HcalMonitorTasks/interface/HcalCommissioningMonitor.h"
#include "DQM/HcalMonitorTasks/interface/HcalTemplateAnalysis.h"
#include "TBDataFormats/HcalTBObjects/interface/HcalTBRunData.h"

#include <memory>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class HcalMonitorModule: public DQMAnalyzer{

public:
  
  // Constructor
  HcalMonitorModule(const edm::ParameterSet& ps);

  // Destructor
  ~HcalMonitorModule();
  
 protected:
  
  // Analyze
  void analyze(const edm::Event& e, const edm::EventSetup& c);
  
  // BeginJob
  void beginJob(const edm::EventSetup& c);
  
  // BeginRun
  void beginRun(const edm::Run& run, const edm::EventSetup& c);

  // Begin LumiBlock
  void beginLuminosityBlock(const edm::LuminosityBlock& lumiSeg, 
                            const edm::EventSetup& c) ;

  // End LumiBlock
  void endLuminosityBlock(const edm::LuminosityBlock& lumiSeg, 
                          const edm::EventSetup& c);

  // EndJob
  void endJob(void);
  
  // EndRun
  void endRun(const edm::Run& run, const edm::EventSetup& c);

  // Reset
  void reset(void);
  
 private:

  int ievt_;
  bool fedsListed_;
  
  edm::InputTag inputLabelDigi_;
  edm::InputTag inputLabelRecHitHBHE_;
  edm::InputTag inputLabelRecHitHF_;
  edm::InputTag inputLabelRecHitHO_;

  MonitorElement* meFEDS_;
  MonitorElement* meStatus_;
  MonitorElement* meRunType_;
  MonitorElement* meEvtMask_;
  MonitorElement* meTrigger_;
  
  HcalMonitorSelector*    evtSel_;
  HcalDigiMonitor*        digiMon_;
  HcalDataFormatMonitor*  dfMon_;
  HcalRecHitMonitor*      rhMon_;
  HcalTrigPrimMonitor*    tpMon_;
  HcalPedestalMonitor*    pedMon_;
  HcalLEDMonitor*         ledMon_;
  HcalMTCCMonitor*        mtccMon_;
  HcalHotCellMonitor*     hotMon_;
  HcalCommissioningMonitor* commisMon_;
  HcalTemplateAnalysis*   tempAnalysis_;
  
  edm::ESHandle<HcalDbService> conditions_;
  const HcalElectronicsMap*    readoutMap_;

};

#endif
