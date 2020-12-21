#include "FWCore/PluginManager/interface/ModuleDef.h"

#include "FWCore/Framework/interface/MakerMacros.h"

#include "RecoLocalMuon/RPCRecHit/plugins/RPCRecHitProducer.h"
#include "RecoLocalMuon/RPCRecHit/plugins/RPCPointProducer.h"

#include "RecoLocalMuon/RPCRecHit/interface/RPCRecHitAlgoFactory.h"
#include "RecoLocalMuon/RPCRecHit/plugins/RPCRecHitStandardAlgo.h"


DEFINE_FWK_MODULE(RPCRecHitProducer);
DEFINE_FWK_MODULE(RPCPointProducer);
DEFINE_EDM_PLUGIN (RPCRecHitAlgoFactory, RPCRecHitStandardAlgo, "RPCRecHitStandardAlgo");
