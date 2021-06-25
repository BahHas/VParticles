#ifndef PhysicsList_h
#define PhysicsList_h 1

#include "globals.hh"
#include "G4VModularPhysicsList.hh"

class PhysicsList : public G4VModularPhysicsList
{
public:
  explicit PhysicsList(G4int verb = 1 , const G4String& n_model = "HP",
                     const G4String& HadrPhysVariant = "");
  virtual ~PhysicsList();

  // virtual void ConstructProcess();
  // void AddPhysicsList(const G4String& name);

private:

  // copy constructor and hide assignment operator
  // G4VPhysicsConstructor* fMuNuclPhysicsList;
  PhysicsList(PhysicsList &);
  PhysicsList & operator=(const PhysicsList &right);
};

#endif
