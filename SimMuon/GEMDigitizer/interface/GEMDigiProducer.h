#ifndef SimMuon_GEMDigitizer_GEMDigiProducer_h
#define SimMuon_GEMDigitizer_GEMDigiProducer_h

#include "FWCore/Framework/interface/stream/EDProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/ConsumesCollector.h"
#include "DataFormats/Common/interface/DetSetVector.h"
#include "SimDataFormats/TrackingHit/interface/PSimHitContainer.h"
#include "SimDataFormats/CrossingFrame/interface/MixCollection.h"
#include "SimDataFormats/TrackerDigiSimLink/interface/StripDigiSimLink.h"
#include "SimDataFormats/GEMDigiSimLink/interface/GEMDigiSimLink.h"

#include <string>

class GEMGeometry;
class GEMDigiModel;

class GEMDigiProducer : public edm::stream::EDProducer<>
{
public:

  typedef edm::DetSetVector<StripDigiSimLink> StripDigiSimLinks;
  
  typedef edm::DetSetVector<GEMDigiSimLink> GEMDigiSimLinks;

  explicit GEMDigiProducer(const edm::ParameterSet& ps);

  ~GEMDigiProducer() override;

  void beginRun(const edm::Run&, const edm::EventSetup&) override;

  void produce(edm::Event&, const edm::EventSetup&) override;

private:

  //Name of Collection used for create the XF 
  edm::EDGetTokenT<CrossingFrame<PSimHit> > cf_token; 
  
  std::unique_ptr<GEMDigiModel> gemDigiModel_;
};

#endif

