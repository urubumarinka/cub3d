_This project has been created as part of the 42 curriculum by maborges and kchatela_

# Cub3D 🕹️

## Description

Cub3D is a 42 school project that recreates the look and feel of early 3D games using raycasting. The goal is to read a `.cub` map configuration, build a playable maze, and render a first-person view with textures, walls, floor and ceiling colors, collision detection, and player movement.

The project is written in C and uses MiniLibX for window management, image rendering, and keyboard input.

## Instructions

### Compilation

Run:

```bash
make
```

This creates the `cub3D` executable at the root of the repository.

### Instalation

After compilated you can directly execute the created executable file, no need to install.

### Execution

Launch the game with a valid `.cub` map file:

```bash
./cub3D <map.cub>
```

Example:

```bash
./cub3D test_map.cub
```

### Controls

- `W`, `A`, `S`, `D`: move forward, left, backward, and right
- Left and right arrow keys: rotate the camera
- `Esc`: close the game window

### Cleaning

Remove object files:

```bash
make clean
```

Remove the executable and rebuild dependencies:

```bash
make fclean
```

Rebuild everything from scratch:

```bash
make re
```

## Resources

- [MiniLibX documentation](https://harm-smits.github.io/42docs/libs/minilibx)
- [Cub3D subject and project guide](https://cdn.intra.42.fr/pdf/pdf/146983/en.subject.pdf)
- [Lode's Computer Graphics Tutorial: Raycasting](https://lodev.org/cgtutor/raycasting.html)
- [The Fuzzy Wuzzy Book: Raycasting](https://www.permadi.com/tutorial/raycast/)

### AI usage

GitHub Copilot was used for the following tasks:

Code Review
Code Refactoring
Testing
Educational Support
