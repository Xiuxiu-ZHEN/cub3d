# cub3D - RayCasting Engine
*This project has been created as part of the 42 curriculum by xzhen and naastrak*

## 1. Description
cub3D is a pseudo-3D game engine based on ray-casting technology, inspired by Wolfenstein 3D - the first FPS game ever created.  
The program reads a map configuration file (.cub) and creates a first-person perspective view of a maze, allowing the player to move and look around in real-time using the miniLibX graphics library.

## 2. Instructions

### Compilation
```bash
make        # compile mandatory part
make clean  # remove object files
make fclean # remove object files and executable
make re     # recompile
```
### Execution
```bash
./cub3D maps/example.cub
```
### Controls

    W A S D - move forward/left/backward/right

    ← → - rotate view left/right

    ESC or click red cross - exit game

### Map Format

    Textures:

        NO ./north.xpm

        SO ./south.xpm

        WE ./west.xpm

        EA ./east.xpm

    Colors:

        F R,G,B - floor color (RGB values 0-255)

        C R,G,B - ceiling color (RGB values 0-255)

### Map Rules

    0 - empty space

    1 - wall

    N/S/E/W - player start position and orientation

    Map must be closed/surrounded by walls

    Map must be the last element in the file

    Elements can be in any order (except map)

    Elements can be separated by empty lines

    Spaces are allowed within elements

## 3. Resources
    Original Wolfenstein 3D

    42 miniLibX Documentation

    Minilibx Tutorial by Oi

### AI Usage

AI was used to assist with:

    Understanding ray-casting algorithms and mathematical concepts

    Debugging parser edge cases for map validation

    Structuring the project and improving code readability

    Optimizing rendering performance