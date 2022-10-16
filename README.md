<p align="center">
  <a href="" rel="noopener">
 <img width=200px height=200px src="https://i.imgur.com/6wj0hh6.jpg" alt="Project logo"></a>
</p>

<h3 align="center">DynamoEngine</h3>

<p align="center"> A 2D game engine using SDL2 written in C++
    <br> 
</p>

## 📝 Table of Contents

- [About](#about)
- [Getting Started](#getting_started)
- [Features](#features)
- [Authors](#authors)
- [Acknowledgments](#acknowledgement)

***

## 🧐 About <a name = "about"></a>

This project is an attempt to create a "game engine" in C++ that serves as a starting point to create a multitude of different 2D games.

**NB:** Only Linux is currently supported.

***

## 🏁 Getting Started <a name = "getting_started"></a>

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes. 

### Prerequisites

This game engine depends only on SDL2 which is typically provided by the package manager on your linux distribution.

On Debian or Debian based distributions (like Ubuntu, Linux Mint etc.), do
```
sudo apt install libsdl2-dev libsdl2-ttf-dev libsdl2-image-dev
```

On Arch based distributions, do
```
sudo pacman -S sdl2 sdl2_image sdl2_ttf
```

### Build

The engine can be built by simply running the build script from the root directory, i.e
```
./build.sh
```

***

## 🐒 Features <a name = "features"></a>
- Generic and extensible
- Provides a window system and fast 2D rendering
- Event system (supports also custom user defined events)
- Memory efficient (resources are shared between game objects and scenes)
- Easily manage multiple game scenes with arbitrary number of game objects

## 🐸 Features to come <a name = "features"></a>
- A simple level editor
- An entity-component system (ECS)

## ✍️ Authors <a name = "authors"></a>

- [@SundeMarius](https://github.com/SundeMarius) - Idea & Development

## 🎉 Acknowledgements <a name = "acknowledgement"></a>

- Thanks [@nlohmann JSON](https://github.com/nlohmann/json) for an awesome C++ JSON library!
- Inspiration from [@TheCherno Hazel Engine](https://github.com/TheCherno/Hazel)
