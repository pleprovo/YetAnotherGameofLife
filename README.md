# Yet Another Game of Life
Yet Another Game of Life is an impletmentation of the Conway's [Game of Life](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life) using Qt.

## Motivation
This project exist as a learning material for Qt Framework. Among the many example the Qt documentation provide, there is already a implementation of the Game of Life that use their Model-View design.
For the sake of learning, I purposely did my own implementation trying to stay away from what has already been done. Note for myself: I was surprised by the use of raw pointers everywhere, turns out all class
That descend from QObject has memoru handling so, nothing to worry on that side.

## Desing
When exploring the Qt documentation it is stated that the Graphics are designed to be able to display many items. I wanted the game to be able to create _large_ game space. So I design the game core around the [GraphicsItem]() class : Cell. A Cell owns it current and previous state as a boolean. It knows how to draw itself wheather it's alive or dead. All the cells are owned by a [GraphicsView]() class : View. The View's role is to create the cells for the game, display all of them and update the states of the whole grid when called. The View is owned by the [MainWindow]() class : Gameoflife. This class own the View and a [Toolbar]() gathering the controls for the game. Tool bar actions buttons are connected to changing the state of the game.
The code was written using Qtcreator IDE, using qmake for building the program. Only ran on Linux Ubuntu 18 so far.

## Dependencies
  * Qt5
  * qmake

## Build
```bash
$ cd YetAnotherGameofLife
$ mkdir build
$ cd build
$ qmake ../YetAnotherGameofLife.pro
$ make
```

## Usage
```bash
$ ./yetanothergameoflife
```

### Start Dialog
Upon starting the game ask you to give the size of the desired grid. The game allow you to create a game of minimum 2x2 to 1000x1000. Note thatthe later creates 1000000 cells and the result in a fairly poor experience (on a Lenevo Thinkpad T420, i5-2520M, 4GB).
![Alt text](./images/star_dialog.png)

### Mainwindow
The main window of the game et composed of a menu tool bar and a grid view.
![Alt text](./images/mainwindow.png)

### Action Menu Bar
The menu tool bar provides action on the game as follow.
  * **New** : Calls the dialog to create a new grid.
  * **Start** : Start a loop updating the grid every 250ms.
  * **Stop** : Stops the aformentioned loop.
  * **Next** : Update the grid aaccording to the rules. If the loop is on then stops it.
  * **Clear** : Kills all the cells in the grid. If the loop is on then stops it.

### Game View
The grid can be explored by scrolling in and out. Each cell of the grid can be toggled on&off using the mouse.
![Alt text](./images/running.png)

## TO-DO
  * Seprate the game model to its view (this is a big change I realised to late to make).
  * Make the View.update() loop async to speed it up.
  * Take advantage of the optimisation options of QGraphicsView.
  * Add tests
  * Add periodic boundary condition.
  * Add different neighborhood scanning kernels.
  * Use QMessageLogger instead of std::clog.

## License
[GNU GPLv3](https://www.gnu.org/licenses/gpl-3.0.html)

## Reception
_"This is the best Game of Life implementation ever !" - **Sir Conway**_