# PROG20002 Graphics Programming

Group 5 - *Idar Løkset Mykløy (@idarmy)*

Welcome to the repo for my project.


# Project overview

**Project file structure:**

```
assignment
 |- resources
 |  |- textures
 |      |- floor_texture.png
 |      |- cube_texture.png
 |- src
 |  |- [All the custom code for the assignment]
 |- CMakeLists.txt
 |- main.cpp
```

I have put all the assignment specific code in the src subfolder.
That code mostly builds upon the Framework components from the labs.

The code implements all features from the assignment issues.
However there are still things I wish i had time to implement:
 - I wanted to make a component system, but didn't have time.
This would make the application loop much cleaner, and would make it easier to expand the functionality of each entity.
 - A shader manager. Right now all the shaders are stored in a header file. I would have liked to store them
  in seperate files and load them in a similar fashion to the TextureManager.
 - The input system is easy to use, which is it's main purpose, but could still be expanded upon. 
 Binding inputs to an axis, where the input value is read as a float between -1 and 1 would simplify the movement related code.

 I have tested natively on windows and ubuntu, so hopefully you won't run into any issues when trying to compile.
