//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
/// \file BiasingOperation.cc
/// \brief Implementation of the BiasingOperation class
//
//

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "BiasingOperation.hh"
#include "G4BiasingProcessInterface.hh"
#include "G4VParticleChange.hh"
// #include "G4ProtonInelasticProcess.hh"
// #include "G4NeutronInelasticProcess.hh"
// #include "G4PionPlusInelasticProcess.hh"
// #include "G4PionMinusInelasticProcess.hh"
#include "G4HadronicParameters.hh"
#include "G4FTFModel.hh"
#include "G4LundStringFragmentation.hh"
#include "G4ExcitedStringDecay.hh"
#include "G4GeneratorPrecompoundInterface.hh"
#include "G4TheoFSGenerator.hh"
#include "G4HadronicInteractionRegistry.hh"
#include "G4VPreCompoundModel.hh"
// #include "G4INCLXXInterface.hh"
#include "G4HadronInelasticDataSet.hh"

#include "G4MuonPlus.hh"
#include "G4MuonMinus.hh"
#include "G4ProcessManager.hh"
#include "G4MuonNuclearProcess.hh"
#include "G4MuonVDNuclearModel.hh"
#include "G4LogicalVolumeStore.hh"

// #include "G4DecayPhysics.hh"
// #include "G4EmStandardPhysics.hh"
// #include "G4EmExtraPhysics.hh"
// #include "G4IonPhysics.hh"
// #include "G4StoppingPhysics.hh"
// #include "G4HadronElasticPhysics.hh"
// #include "G4NeutronTrackingCut.hh"
//
// #include "G4HadronPhysicsFTFP_BERT.hh"
// #include "FTFP_BERT.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

BiasingOperation::BiasingOperation( G4String name ) : G4VBiasingOperation( name ) {


  fmuNucProcess = new G4MuonNuclearProcess();


//muon nuclear model
  G4MuonVDNuclearModel* muNucModel = new G4MuonVDNuclearModel();


  // fmuNucProcess->RegisterMe( theHighEnergyModel );
  // fmuNucProcess->RegisterMe( thePreCompoundModel );
  fmuNucProcess->RegisterMe( muNucModel );
  // fmuNucProcess->RegisterMe( new G4EmStandardPhysics() );
  // fmuNucProcess->RegisterMe( new G4EmExtraPhysics() );
  // fmuNucProcess->RegisterMe( new G4DecayPhysics() );
  // fmuNucProcess->RegisterMe( new G4HadronElasticPhysics() );
  // fmuNucProcess->RegisterMe( new G4HadronPhysicsFTFP_BERT() );
  // fmuNucProcess->RegisterMe( new G4StoppingPhysics() );
  // fmuNucProcess->RegisterMe( new G4IonPhysics() );
  // fmuNucProcess->RegisterMe( new G4NeutronTrackingCut() );



  // fmuNucProcess->BiasCrossSectionByFactor(1000000);


  // Register the cross sections: this is mandatory starting from G4 10.6
  // because the default Gheisha inelastic cross sections have been removed.
  // It is convenient to use the Gheisha inelastic cross sections here
  // because they do not require any special initialization.
  // fProtonInelasticProcess->AddDataSet( new G4HadronInelasticDataSet );
  // fNeutronInelasticProcess->AddDataSet( new G4HadronInelasticDataSet );
  // fPionPlusInelasticProcess->AddDataSet( new G4HadronInelasticDataSet );
  // fPionMinusInelasticProcess->AddDataSet( new G4HadronInelasticDataSet );
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

BiasingOperation::~BiasingOperation() {}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


G4VParticleChange* BiasingOperation::
ApplyFinalStateBiasing( const G4BiasingProcessInterface* ,
                        const G4Track* track, const G4Step* step, G4bool& ) {
	//  if ( track->GetParentID() != 0 ) {
	//    return 0;
  if (track->GetParticleDefinition() == G4MuonPlus::Definition()) {
	return fmuNucProcess->PostStepDoIt( *track, *step );
  } else if ( track->GetParticleDefinition() == G4MuonMinus::Definition() ) {
    return fmuNucProcess->PostStepDoIt( *track, *step );
  } else {
    G4cerr << "ERROR in BiasingOperation::ApplyFinalStateBiasing : unexpected particle = "
           << track->GetParticleDefinition()->GetParticleName() << G4endl;
    return 0;
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
