# cs174a-term-project
**Fall 2011 UCLA 174A Graphics I Term Project**

Final project for cs174A put together with team Tarun Solanki, Mike Sechooler, Howard Lee, and Garrett Johnson

![image](/docs/animation-sm.gif)

## Controls

### Basic
Basic controls for operating the main character
```
ESC		quit

W 		move forward
A 		move left
D 		move right
S 		move back

Q E 		cycle weapon
SPACE 		jump (with a tank?!)
F 		toggle mouse capture

Mouse 		look direction

Left Click 	shoot
Right Click 	enable shield
```

### Debug
Controls for toggling a variety of graphics features
```
P O		increase / decrease normal map depth

L K 		enable / disable fog layer

;		enter full screen (cannot get out, must exit with 'esc')
"		enter first person view
```

### UI
Top bar is health

Bottom bar is shield recharge

## Technologies and Dependencies
### Advanced topics
#### Collision Detection
AABB and sphere collision on environment and characters in conjunction with basic physics

#### Normal Mapping
Normal map in shader with variable intensity

#### Multiple Lights
Support for up to 10 dynamic point lights

#### Render Texture Rendering
Rendering to render texture to create "portals"

#### Transparency
Transparent objects with back-to-front rendering

### Other
#### Load OBJs
Used library from [this repo](https://github.com/stcui/Obj-Loader) to load obj models

#### Sound
Play back sounds using [SDL](https://www.libsdl.org/)

#### Image Loading
Load images using [DevIL](http://openil.sourceforge.net/)

#### Graphics
Used [GLUT](https://www.opengl.org/resources/libraries/glut/), OpenGL to set up and interact with GPU

Used vector and matrix utility code from Angel [here](http://www.cs.unm.edu/~angel/BOOK/INTERACTIVE_COMPUTER_GRAPHICS/SIXTH_EDITION/)
