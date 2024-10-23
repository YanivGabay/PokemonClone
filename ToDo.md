

# Revisiting the project 23.10.24

## Urgent to fix

Currently, there arent any installation guide, and cloning doesnt work even when loading into Visual studio.

### Problems found

#### Box2d isnt needed
Object are reliant on box2d, despite not using any real physics. 
Box2d is a big library, we dont want to push, or logicly even use here.

#### Solution

will remove the usage of it, into a self variable of position_x and position_y.
Than remove it from cmake file and other refrences.

#### No cpp files
we were lazy.

#### Solution
seperate into cpp files.

#### Alot of files are staticly typed
instead of doing a modular loading from a specific folder

#### Solution
create a script and folders, to load all the names/path from a folder.
