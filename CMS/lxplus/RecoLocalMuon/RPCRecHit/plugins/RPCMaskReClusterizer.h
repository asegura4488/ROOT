#ifndef RecoLocalMuon_RPCMaskReClusterizer_h
#define RecoLocalMuon_RPCMaskReClusterizer_h

/** \Class RPCMaskReClusterizer
 *  \author J.C. Sanabria -- UniAndes, Bogota
 */

#include "RecoLocalMuon/RPCRecHit/interface/RPCRollMask.h"
#include "RecoLocalMuon/RPCRecHit/plugins/RPCClusterContainer.h"
#include "DataFormats/MuonDetId/interface/RPCDetId.h"

class RPCMaskReClusterizer
{
 public :
   RPCMaskReClusterizer() {};
   ~RPCMaskReClusterizer() {};
   RPCClusterContainer doAction(const RPCDetId& id,RPCClusterContainer& initClusters, const RollMask& mask) const;
   bool get(const RollMask& mask,int strip) const;

};

#endif
