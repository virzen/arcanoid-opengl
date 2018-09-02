# TODO list
The following list represents tasks that should be completed
before releasing a specific version of `graphics-opengl-project`.

## Version 1.0
Version *1.0* should be the version that can be shown to the lecturer.

#### Goals:
- **Code fulfilling all project requirements**

  The code has to fulfill all requirements listed on [lecturer's website](http://www.cs.put.poznan.pl/wandrzejewski/strona-glowna/dydaktyka/cg-projekty/).
  
- **Fluent gameplay**

  Gamer has to be able to start a new game, play until he wins or loses and repeat the process.
  
- **Good user experience**

  Game has to represent a proper level of UX, including flashing game logo, intuitive game controls,
  statistics display and optional technical details (FPS etc.) displayed after certain key is pressed.

- **Code following the best practices**

  - Code split into functional classes
  - Code documented with comments over classes, over methods and optionally inside methods
  - File, class, method and variable naming following C++ specification
  - ?
  
## Version 0.2
**To be filled soon.**

## Version 0.1
Code in *0.1* should provide a stable codebase for future development.

#### Goals:
- **Reliable build process across Mac and Linux environments**

  Code should build with `make` without errors on both environments right after checkout,
  assuming that the developer has all dependencies installed on his machine.
  
- **Common codebase for adding new models and behaviours**

  Code should allow for adding new models effortlessly by creating a new object,
  providing `*.obj` file and optionally other files describing it.