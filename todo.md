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
  - [x] Toggle surface from userinput
    - [x] Expose function call
    - Toggle specific molecule
    - Make molecule an identificable entity
  - [x] Manipulate Molecule size 
  - [x] Spawn Actors
* Interface
  - [x] Menu
    - [x] Set text from mol to button
  - [x] Filebrowser to select molecule file
  - [x] Make menu stick to controler
  - [x] Disabled physics for more practical use (molecules dont need to fall down)
  - [x] Spawn molucule in hand or before menu --> hide menu?
  - [x] Find good menu position
  - [ ] Create Lab level
    - [ ] Lab table with molecules on top
    - [ ] ~~Fixed menu in front of table --> spawn molecules on table~~
  - [ ] Widget interaction bug left of molecule
  - [x] Left hand bug interaction bug
  - [ ] Consolidate input from Vive and Oculus


