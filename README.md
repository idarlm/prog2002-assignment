# PROG2002 Graphics Programming

![Animation](https://github.com/idarlm/prog2002-assignment/assets/101576034/07432af9-101c-4e83-9ca8-fd0fa14caa59)

## Project overview

This project was done as part of the PROG2002 course at NTNU Gjøvik. The goal of this project was to create a simple OpenGL renderer using GLFW and GLAD.

We were supplied with a repo containing the base file structure and submodules. From there we had to follow issues showing how to implement framework components that we would use to solve the assignment.
These issues are not visible here as the original repo was in a private Gitlab instance.

## How to run the project

Most dependencies are provided as submodules and statically linked. On windows it should run right out of the box when built with CMake in Visual Studio.
On linux you might need some additional packages to build.

## Using the application

When the application is running you can interact with it using these keys:

 | Key(s) | Actions |
 | :-- | :-- |
 | H, L | Orbit camera |
 | O, P | Change zoom level |
 | Arrow Keys | Select tile |
 | Enter | Select/place cube |

The application allows you to select cubes and move them to unoccupied tiles.

## Postmortem

The code implements all features from the assignment issues.
However there are still things I wish i had time to implement:
 - I wanted to make a component system, but didn't have time.
This would make the application loop much cleaner, and would make it easier to expand the functionality of each entity.
 - A shader manager. Right now all the shaders are stored in a header file. I would have liked to store them
  in seperate files and load them in a similar fashion to the TextureManager.
 - The cubes are supposed to be transparent, however the draw order is not sorted so they are drawn before the board.
