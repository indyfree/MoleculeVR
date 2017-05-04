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
  - [ ] Toggle surface from userinput
    - ~~Expose function call~~
    - Toggle specific molecule
    - Make molecule an identificable entity
  - [ ] Move molecule with VR controllers
    - [ ] Simulate physics 
      - Look at Convex Collision example
      - Set physics in Blueprint
      - Expose vertices from c++ to Blueprint via UPROPERY
     - [ ] Use PickupActor interface for VR integration
  - [ ] Manipulate Molecule size 
  - [ ] Spawn Actors
* Interface
  - [ ] Menu
  - [ ] Filebrowser to select molecule file

