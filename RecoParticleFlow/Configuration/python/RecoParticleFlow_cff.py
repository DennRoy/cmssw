import FWCore.ParameterSet.Config as cms


from RecoParticleFlow.PFTracking.particleFlowTrack_cff import *
#from RecoParticleFlow.PFTracking.particleFlowTrackWithDisplacedVertex_cff import *

from RecoParticleFlow.PFProducer.particleFlowSimParticle_cff import *
from RecoParticleFlow.PFProducer.particleFlowBlock_cff import *

from RecoParticleFlow.PFProducer.particleFlowEGamma_cff import *
from RecoParticleFlow.PFProducer.particleFlow_cff import *
from RecoParticleFlow.PFProducer.pfElectronTranslator_cff import *
from RecoParticleFlow.PFProducer.pfPhotonTranslator_cff import *
#from RecoParticleFlow.PFProducer.pfGsfElectronCiCSelector_cff import *
from RecoParticleFlow.PFProducer.pfGsfElectronMVASelector_cff import *

from RecoParticleFlow.PFProducer.pfLinker_cff import * 

from CommonTools.ParticleFlow.pfParticleSelection_cff import *

from RecoEgamma.EgammaIsolationAlgos.particleBasedIsoProducer_cff import *

from RecoJets.JetProducers.fixedGridRhoProducerFastjet_cfi import *
fixedGridRhoFastjetAllTmp = fixedGridRhoFastjetAll.clone(pfCandidatesTag = cms.InputTag("particleFlowTmp"))

particleFlowReco = cms.Sequence( particleFlowTrackWithDisplacedVertex*
#                                 pfGsfElectronCiCSelectionSequence*
                                 pfGsfElectronMVASelectionSequence*
                                 particleFlowBlock*
                                 particleFlowEGammaFull*
                                 particleFlowTmp*
                                 fixedGridRhoFastjetAllTmp*
                                 particleFlowTmpPtrs*          
                                 particleFlowEGammaFinal*
                                 pfParticleSelectionSequence )

particleFlowLinks = cms.Sequence( particleFlow*particleFlowPtrs*particleBasedIsolationSequence)

from RecoParticleFlow.PFProducer.HGCalTrackCollection_cfi import *
from RecoParticleFlow.PFProducer.simPFProducer_cfi import *
from SimTracker.TrackerHitAssociation.tpClusterProducer_cfi import *
from SimTracker.TrackAssociatorProducers.quickTrackAssociatorByHits_cfi import *
from Configuration.StandardSequences.Eras import eras
HGCalTrackCollection.debug=cms.bool(True)
tpClusterProducer.pixelSimLinkSrc     = cms.InputTag("simSiPixelDigis", "Pixel")
tpClusterProducer.phase2OTSimLinkSrc  = cms.InputTag("simSiPixelDigis","Tracker")
quickTrackAssociatorByHits.pixelSimLinkSrc = cms.InputTag("simSiPixelDigis","Pixel")
quickTrackAssociatorByHits.stripSimLinkSrc = cms.InputTag("simSiPixelDigis","Tracker")
_phase2_hgcal_simPFSequence = cms.Sequence( HGCalTrackCollection + 
                                            tpClusterProducer +
                                            quickTrackAssociatorByHits +
                                            simPFProducer )
_phase2_hgcal_particleFlowReco = cms.Sequence( particleFlowReco.copy() + _phase2_hgcal_simPFSequence )

eras.phase2_hgcal.toReplaceWith( particleFlowReco, _phase2_hgcal_particleFlowReco )
