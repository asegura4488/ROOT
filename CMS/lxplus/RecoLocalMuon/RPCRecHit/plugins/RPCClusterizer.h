#ifndef RecoLocalMuon_RPCClusterizer_h
#define RecoLocalMuon_RPCClusterizer_h
/** \class RPCClusterizer
 *  \author M. Maggi -- INFN Bari
 */

#include "RecoLocalMuon/RPCRecHit/plugins/RPCClusterContainer.h"
#include "RecoLocalMuon/RPCRecHit/interface/RPCCluster.h"
#include "DataFormats/RPCDigi/interface/RPCDigiCollection.h"

class RPCClusterizer{
 public:
  RPCClusterizer() {};
  ~RPCClusterizer() {};
  RPCClusterContainer doAction(const RPCDigiCollection::Range& digiRange);
};
#endif
