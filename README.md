# Breakout (Arkanoid 2)

A Breakout/Arkanoid-style arcade game written in C++ with Qt Widgets, created at the end of 2018 as a learning project. The source code and UI text are in Polish.

## Features

- Paddle controlled with the mouse, ball physics with wall, paddle and block collisions
- Four fixed block layouts plus a randomly generated one, picked at random each round
- Three lives; each lost ball spawns a new one
- Three difficulty levels (ball speed)
- Window resolution options (800x600, 1280x720, 1920x1080) and full-screen mode
- Top-10 high score table saved to `wyniki.txt` in the working directory
- Main menu with New game, High scores, Settings, Authors and Exit screens

## Tech stack

- C++11
- Qt 5 (Core, GUI, Widgets; `QGraphicsView`/`QGraphicsScene`)
- qmake project (`Breakout.pro`), created with Qt Creator

## Building

Open `Breakout.pro` in Qt Creator and build, or from the command line with a Qt 5 toolchain:

```bash
qmake Breakout.pro
make        # or nmake / mingw32-make / jom on Windows
```

The code uses `qsrand`/`qrand`, which were removed in Qt 6, so a Qt 5 kit is required.

## Project structure

| File | Purpose |
| --- | --- |
| `main.cpp` | application entry point |
| `mainwindow.*` | main window, menu screens, settings and high scores |
| `gra.*` | game view/scene, level layouts, lives and score (`gra` = game) |
| `pilka.*` | ball movement and collisions (`pilka` = ball) |
| `paletka.*` | mouse-controlled paddle (`paletka` = paddle) |
| `blok.*` | breakable block (`blok` = block) |

`wynik.cpp` and `zdjecia.qrc` are leftovers that are not part of the build (`zdjecia.qrc` references an image that is not in the repository).
