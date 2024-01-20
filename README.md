# Simple X11 Console Example with ASCII animation

This application demonstrates how to open a simple X11 console window, and loop through a basic animation.

# Todo

- Gitch with calculating Y offset of text rows within the console (currently with hacky fix)

- It could be a funky rotating wireframe cube intead

- Beginnings of a test rig for testing parallel collision detection algorithm

# Running

To Run (within VSCode);

- Ensure project is open within the development container
- Hit F5

This application was written in C++ using VSCode and includes a devcontainer setup file,
which should create a self-contained environment with all the below requirements installed;

It should be possible to build and run the code with alternative development environments, outside of VSCode.

Host Machine Requirements;

To download VSCode;

https://code.visualstudio.com/download

The VSCode development container plugin is installed;

https://code.visualstudio.com/docs/remote/containers

Docker must also be installed;

https://docs.docker.com/get-docker/

This application, however is configured with linux based containers, and will not work correctly on Windows without modification.
