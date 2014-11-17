EarthWarrior3D
======

This is an experimental project from Cocos2d-x, featuring 3D models in a 2d game.

Using Cocos2d-x 3.0 and the experimental Sprite3D.

The code of this project, Cocos2d-x, Sprite3D are all licensed under MIT

Musics are copyrighted by [Matthew Pablo](http://www.matthewpablo.com/), and licensed under CC-BY 3.0

You may not use any art including 2d and 3d from this project for commercial purpose


###FMOD

This fork has replaced the audio with FMOD Studio events as a simple example of how to use the FMOD API.

Currently only the Win32 project has been setup and is dependent on external libraries available from the FMOD website.

1. Download FMOD Studio API 1.05.xx from http://www.fmod.org/download
2. Install the API to any location.
3. Copy [fmod dir]/api/lowlevel/inc/* to cocos2d/external/fmod/include
4. Copy [fmod dir]/api/studio/inc/* to cocos2d/external/fmod/include
5. Copy [fmod dir]/api/lowlevel/lib/* to cocos2d/external/fmod/prebuilt/win32
6. Copy [fmod dir]/api/studio/lib/* to cocos2d/external/fmod/prebuilt/win32


###Sprite3D


The Sprite3D code featured in this project can currently load static OBJ model.

to load a model:
```c++
auto model = Sprite3D::create("3dmodel.obj", "texture.png");
```

###Toon Shading

There is no lighting in Cocos2d-x yet. But
To compliment that, we added built-in support for toon-shader, specifically, toon outline:
```c++
auto model = Sprite3D::create("3dmodel.obj", "texture.png");
model->setOutline(1.5, Color3B(0,0,0)); // set the outline to be 1.5 point wide, and black
```


###3D API

3D API are available since Cocos2d-x 3.0 for all Nodes

```c++
node->setPosition3D(Vertex3F(x,y,z));
Vertex3F pos = node->getPosition3D();

node->setRotation3D(Vertex3F(x,y,z));
Vertex3F rot = node->getRotation3D(); //2d rotation is the same as rotating in z axis
```
3D API are also ported to some actions as well
```c++
node->runAction(RotateBy::create(Vertex3F(x,y,z)));
```
