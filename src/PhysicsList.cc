#include "PhysicsList.hh"
#include "globals.hh"

#include "G4DecayPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"
#include "G4EmParameters.hh"
#include "G4EmStandardPhysics.hh"
#include "G4EmStandardPhysics_option4.hh"
#include "G4EmExtraPhysics.hh"
#include "G4IonQMDPhysics.hh"
#include "G4IonElasticPhysics.hh"
#include "G4StoppingPhysics.hh"
#include "G4HadronElasticPhysicsHP.hh"
#include "G4HadronElasticPhysicsLEND.hh"
#include "G4ParticleHPManager.hh"

#include "G4DataQuestionaire.hh"
#include "G4HadronPhysicsShielding.hh"
#include "G4HadronPhysicsShieldingLEND.hh"
#include <CLHEP/Units/SystemOfUnits.h>

#include "G4ParticleDefinition.hh"
#include "G4MuonPlus.hh"
#include "G4MuonMinus.hh"
#include "G4ProcessManager.hh"
#include "G4MuonNuclearProcess.hh"
#include "G4MuonVDNuclearModel.hh"

#include "MuNuclearBuilder.hh"

PhysicsList::PhysicsList(G4int verbose, const G4String& n_model,
						 const G4String& HadrPhysVariant )
{
	G4String LEN_model = n_model;
	size_t find = LEN_model.find("LEND__");
	G4String evaluation;
	if ( find != G4String::npos )
		{
			evaluation=LEN_model;
			evaluation.erase(0,find+6);
			LEN_model="LEND";
		}

	G4DataQuestionaire it(photon, neutron, radioactive);
	G4cout << "<<< Geant4 Physics List simulation engine: PhysicsList"
		   << HadrPhysVariant << G4endl;
	if ( LEN_model=="LEND" ) G4cout <<
								 "<<< LEND will be used for low energy neutron and gamma projectiles"
								  << G4endl;

	defaultCutValue = 0.7*CLHEP::mm;
	SetCutValue(0, "proton");
	SetVerboseLevel(verbose);

	// EM Physics
	RegisterPhysics( new G4EmStandardPhysics(verbose));

	// Synchroton Radiation & GN Physics
	G4EmExtraPhysics* emExtraPhysics = new G4EmExtraPhysics(verbose);
	if ( LEN_model == "LEND" ) {
		// Use LEND model for Gamma Nuclear
		emExtraPhysics->LENDGammaNuclear(true);
	}
	RegisterPhysics( emExtraPhysics );

	// Decays
	RegisterPhysics( new G4DecayPhysics(verbose) );
	RegisterPhysics( new G4RadioactiveDecayPhysics(verbose) );

	// Hadron Elastic scattering
	if ( LEN_model == "HP" )
		{
			RegisterPhysics( new G4HadronElasticPhysicsHP(verbose) );
		}
	else if ( LEN_model == "LEND" )
		{
			RegisterPhysics( new G4HadronElasticPhysicsLEND(verbose,evaluation));
			G4DataQuestionaire itt(lend);
		}
	else
		{
			G4cout << "Physics List: Warning!" <<G4endl;
			G4cout << "\"" << LEN_model
				   << "\" is not valid for the low energy neutorn model." <<G4endl;
			G4cout << "Neutron HP package will be used." <<G4endl;
			RegisterPhysics( new G4HadronElasticPhysicsHP(verbose) );
		}

	G4VPhysicsConstructor* hpc;
	// Hadron Physics HP or LEND
	if (HadrPhysVariant == "M") {
		hpc = new G4HadronPhysicsShielding("hInelastic Shielding", verbose,
										   9.5*CLHEP::GeV, 9.9*CLHEP::GeV);
	} else {
		hpc = new G4HadronPhysicsShielding("hInelastic Shielding", verbose,
										   4.0*CLHEP::GeV, 5.0*CLHEP::GeV);
	}

	if ( LEN_model == "LEND" ) {
		delete hpc;
		if (HadrPhysVariant == "M") {
			hpc = new G4HadronPhysicsShieldingLEND("hInelastic ShieldingLEND",
												   verbose, 9.5*CLHEP::GeV, 9.9*CLHEP::GeV);
		} else {
			hpc = new G4HadronPhysicsShieldingLEND("hInelastic ShieldingLEND",
												   verbose, 4.0*CLHEP::GeV, 5.0*CLHEP::GeV);
		}
	} else {
		//G4cout << "Shielding Physics List: Warning." <<G4endl;
		//G4cout << "Name of Low Energy Neutron model " << LEN_model
		//         << " is invalid." <<G4endl;
		//G4cout << "Will use neutron HP package." <<G4endl;
	}
	RegisterPhysics( hpc );

	if ( LEN_model == "HP" ) {
		//Activate prodcuton of fission fragments in neutronHP
		G4ParticleHPManager::GetInstance()->SetProduceFissionFragments( true );
	}

	// Stopping Physics
	RegisterPhysics( new G4StoppingPhysics(verbose) );

	// Ion Physics
	RegisterPhysics( new G4IonElasticPhysics(verbose));
	RegisterPhysics( new G4IonQMDPhysics(verbose));

	RegisterPhysics( new MuNuclearBuilder(verbose));


}

PhysicsList::~PhysicsList()
{}

