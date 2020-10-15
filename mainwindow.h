/*
    Yet Another Game of Life
    Copyright (C) 2020  Pierre Leprovost

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

// Forward declarations
class QTimer;
class GameView;

/**
 * @brief The MainWindow class
 * Hold a view and a tool bar to visualize and control the game.
 * Also own a Timer that control the automatic update of the game.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

signals:

public slots:
    /**
     * @brief newGame : Create a Dialog. The Dialog ask for input od row and column sizes.
     * Resize and populated the scene.
     */
    void newGame();

    /**
     * @brief start : Launch the timer and call the next method to update the GameView.
     */
    void start();

    /**
     * @brief stop : Stops the timer.
     */
    void stop();

    /**
     * @brief next : Calls the update method of GameView.
     */
    void next();

    /**
     * @brief clear : Kills every cells in the GameView.
     */
    void clear();

private:
    void createActions();
    void createStatusBar();

    GameView *m_view;
    QTimer *m_timer;

    unsigned long int m_update_count = 0;
};

#endif // MAINWINDOW_H
