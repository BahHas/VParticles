#include "MuNuclearBuilder.hh"

#include "G4ParticleDefinition.hh"
#include "G4MuonPlus.hh"
#include "G4MuonMinus.hh"

#include "G4ProcessManager.hh"
//#include "G4MuNuclearInteraction.hh"
//#include "G4PreCompoundModel.hh"
#include "G4MuonNuclearProcess.hh"
#include "G4MuonVDNuclearModel.hh"

#include "G4LogicalVolumeStore.hh"


MuNuclearBuilder::MuNuclearBuilder(const G4String& name)
   :  G4VPhysicsConstructor(name)
{}

MuNuclearBuilder::~MuNuclearBuilder()
{}


void MuNuclearBuilder::ConstructProcess()
{
  G4ProcessManager * pManager = 0;

  G4MuonNuclearProcess* muNucProcess = new G4MuonNuclearProcess();
  G4MuonVDNuclearModel* muNucModel = new G4MuonVDNuclearModel();
  muNucProcess->RegisterMe(muNucModel);
  muNucProcess->BiasCrossSectionByFactor(1000);


  pManager = G4MuonPlus::MuonPlus()->GetProcessManager();
  pManager->AddDiscreteProcess(muNucProcess);

  pManager = G4MuonMinus::MuonMinus()->GetProcessManager();
  pManager->AddDiscreteProcess(muNucProcess);


}
