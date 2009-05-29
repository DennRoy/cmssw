#include "RecoTauTag/RecoTau/interface/PFRecoTauDiscriminationByIsolation.h"

void PFRecoTauDiscriminationByIsolation::produce(Event& iEvent,const EventSetup& iEventSetup){
  Handle<PFTauCollection> thePFTauCollection;
  iEvent.getByLabel(PFTauProducer_,thePFTauCollection);
  
  // fill the AssociationVector object
  auto_ptr<PFTauDiscriminator> thePFTauDiscriminatorByIsolation(new PFTauDiscriminator(PFTauRefProd(thePFTauCollection)));
  
  for(size_t iPFTau=0;iPFTau<thePFTauCollection->size();++iPFTau) {
    PFTauRef thePFTauRef(thePFTauCollection,iPFTau);
    PFTau thePFTau=*thePFTauRef;
    math::XYZVector thePFTau_XYZVector=thePFTau.momentum();   
    PFTauElementsOperators thePFTauElementsOperators(thePFTau);
    if (ApplyDiscriminationByTrackerIsolation_){  
      // optional selection by a tracker isolation : ask for 0 charged hadron PFCand / reco::Track in an isolation annulus around a leading PFCand / reco::Track axis
      float TrackPtSum=0;
      double theTrackerIsolationDiscriminator = 1.;
      if (ManipulateTracks_insteadofChargedHadrCands_){
         const TrackRefVector& isolationTracks = thePFTau.isolationTracks();
         unsigned int tracksAboveThreshold = 0;

         for(size_t iTrack = 0; iTrack < isolationTracks.size(); ++iTrack)
         {

	   if (SumOverCandidates_){
	     TrackPtSum+=isolationTracks[iTrack]->pt();
	     if ((TrackPtSum>maxChargedPt_)&&(!TrackIsolationOverTauPt_)){
	       theTrackerIsolationDiscriminator = 0.;
	       break;
	     }
	     if ((TrackPtSum/thePFTau.pt()>maxChargedPt_)&&(TrackIsolationOverTauPt_)){
	       theTrackerIsolationDiscriminator = 0.;
	       break;
	     }	     
	   }
	   else{
	     if(isolationTracks[iTrack]->pt() > maxChargedPt_) {
               if(++tracksAboveThreshold > TrackerIsolAnnulus_Tracksmaxn_)
		 {
		   theTrackerIsolationDiscriminator = 0.;
		   break;
		 }
	     }
	   }
         }

      } else { //use pf candidates instead
         const PFCandidateRefVector& pfIsoChargedCands = thePFTau.isolationPFChargedHadrCands();
         unsigned int tracksAboveThreshold = 0;
         for(size_t iIsoCand = 0; iIsoCand < pfIsoChargedCands.size(); ++iIsoCand)
         {
	   if (SumOverCandidates_){
	     TrackPtSum+=pfIsoChargedCands[iIsoCand]->pt();
	     if ((TrackPtSum>maxChargedPt_)&&(!TrackIsolationOverTauPt_)){
	       theTrackerIsolationDiscriminator = 0.;
	       break;
	     }
	     if ((TrackPtSum/thePFTau.pt()>maxChargedPt_)&&(TrackIsolationOverTauPt_)){
	       theTrackerIsolationDiscriminator = 0.;
	       break;
	     }	     
	   } 
	   else{
	     if(pfIsoChargedCands[iIsoCand]->pt() > maxChargedPt_) {
               if(++tracksAboveThreshold > TrackerIsolAnnulus_Candsmaxn_) {
		 theTrackerIsolationDiscriminator = 0.;
		 break;
               }
	     }
	   }
         }
      }

      if (theTrackerIsolationDiscriminator == 0.){
	thePFTauDiscriminatorByIsolation->setValue(iPFTau,0.);
        continue;
      }
    }    
    
    if (ApplyDiscriminationByECALIsolation_){
      
      cout<<"H1"<<endl;
      // optional selection by an ECAL isolation : ask for 0 gamma PFCand in an isolation annulus around a leading PFCand
      double theECALIsolationDiscriminator =1.;
      const PFCandidateRefVector& pfIsoGammaCands = thePFTau.isolationPFGammaCands();
      unsigned int gammasAboveThreshold = 0;
      float PhotonSum=0;
      for(size_t iIsoGamma = 0; iIsoGamma < pfIsoGammaCands.size(); ++iIsoGamma)
      {
	if (SumOverCandidates_){
	  PhotonSum+=pfIsoGammaCands[iIsoGamma]->pt();
	  if ((PhotonSum>maxGammaPt_)&&(!TrackIsolationOverTauPt_)){
	     theECALIsolationDiscriminator = 0.;
	    break;
	  }
	  if ((PhotonSum/thePFTau.pt()>maxGammaPt_)&&(TrackIsolationOverTauPt_)){
	       theECALIsolationDiscriminator = 0.;
	       break;
	  }	     
	} 
	else{
	  if(pfIsoGammaCands[iIsoGamma]->pt() > maxGammaPt_) {
            if(++gammasAboveThreshold > ECALIsolAnnulus_Candsmaxn_) {
	      theECALIsolationDiscriminator = 0;
	      break;
            }
	  }
	}
      }
      if (theECALIsolationDiscriminator==0.){
	thePFTauDiscriminatorByIsolation->setValue(iPFTau,0);
	continue;
      }
    }
    
    // not optional selection : ask for a leading (Pt>minPt) PFCand / reco::Track in a matching cone around the PFJet axis
    bool theleadElementDiscriminator = true;
    if (ManipulateTracks_insteadofChargedHadrCands_) {
      if (!thePFTau.leadTrack()) theleadElementDiscriminator = false;
    } else if (!thePFTau.leadPFChargedHadrCand()) theleadElementDiscriminator = false;

    if (!theleadElementDiscriminator) thePFTauDiscriminatorByIsolation->setValue(iPFTau,0);
    else thePFTauDiscriminatorByIsolation->setValue(iPFTau,1); //passes everything
  }    

  iEvent.put(thePFTauDiscriminatorByIsolation);
  
}


