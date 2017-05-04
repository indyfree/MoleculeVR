# Todo MoleculeVR 
* Export
  - [x] Use Collada (.dae) export of molecules  from  pymol  
* Import
  - [x] Use Assimp library to import molecule files
  - [x] Split mesh into surface and molecule core
* Render
  - [x] Use UE4-Plugin RuntimeMeshComponent to render mesh
  - [x] Render molecule core and surface as different mesh sections
* Game
  - [x] Move molecule with VR controllers
    - [x] Simulate physics 
      - ~~Look at Convex Collision example~~
      - ~~Set physics and collision in c++ class~~
     - [x] Use PickupActor interface for VR integration
  - [ ] Toggle surface from userinput
    - [x] Expose function call
    - Toggle specific molecule
    - Make molecule an identificable entity
  - [ ] Manipulate Molecule size 
  - [ ] Spawn Actors
* Interface
  - [ ] Menu
  - [ ] Filebrowser to select molecule file

