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

#ifndef VIEW_H
#define VIEW_H

#include <QGraphicsView>

// Forward declarations
class Cell;
class QGraphicsScene;

/**
 * @brief The GameView class
 * Create and owns the cells for the game.
 * Hold the scene in which the cells are displayed.
 */

class GameView : public QGraphicsView
{
    Q_OBJECT
public:
    GameView(QWidget *parent = nullptr);

public slots:
    void zoomIn();
    void zoomOut();

    /**
     * @brief update : Update all the cells according to the game of life rules.
     */
    void update();

    /**
     * @brief clear : Kills all the cells.
     */
    void clear();

    /**
     * @brief populate the scene
     * @param n Row Size
     * @param m Column Size
     */
    void populate(const int n = 100, const int m = 100);

protected:
    void wheelEvent(QWheelEvent *event) override;
    void scaleView(qreal scaleFactor);

private:
    QGraphicsScene *m_scene;
    QList<Cell *> m_cells;
};

#endif // VIEW_H
