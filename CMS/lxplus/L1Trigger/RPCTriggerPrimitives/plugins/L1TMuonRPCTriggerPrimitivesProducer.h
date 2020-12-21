#ifndef L1Trigger_RPCTriggerPrimitives_L1TMuonRPCTriggerPrimitivesProducer_h
#define L1Trigger_RPCTriggerPrimitives_L1TMuonRPCTriggerPrimitivesProducer_h

#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/stream/EDProducer.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/stream/EDProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/MuonDetId/interface/RPCDetId.h"
#include "DataFormats/RPCDigi/interface/RPCDigiCollection.h"

#include "DataFormats/RPCRecHit/interface/RPCRecHit.h"
#include "DataFormats/RPCRecHit/interface/RPCRecHitCollection.h"

#include "RecoLocalMuon/RPCRecHit/interface/RPCRecHitAlgoFactory.h"
#include "FWCore/PluginManager/interface/PluginFactory.h"
#include "RecoLocalMuon/RPCRecHit/interface/RPCRecHitBaseAlgo.h"


#include "TVector3.h"

#include "PrimitivePreprocess.h"

// Class declaration

class L1TMuonRPCTriggerPrimitivesProducer : public edm::stream::EDProducer<> {
public:
  explicit L1TMuonRPCTriggerPrimitivesProducer(const edm::ParameterSet&);
  ~L1TMuonRPCTriggerPrimitivesProducer() override;

private:
  void beginStream(edm::StreamID) override;
  void endStream() override;
  void produce(edm::Event& event, const edm::EventSetup& setup) override;

  std::unique_ptr<PrimitivePreprocess> preprocess_pointer_;
  std::unique_ptr<RPCRecHitBaseAlgo> theAlgorithm;
};

#endif /* #define L1Trigger_RPCTriggerPrimitives_L1TMuonRPCTriggerPrimitivesProducer_h */
