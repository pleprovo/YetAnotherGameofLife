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

#ifndef CELL_H
#define CELL_H

#include <QGraphicsItem>

// Forward Declarations
class GameView;
class QGraphicsSceneMouseEvent;

/**
 * @brief The Cell class
 */
class Cell : public QGraphicsItem
{
public:
    Cell(GameView *view);

    /**
     * @brief addNeighbor.
     * @param neighbor
     */
    void addNeighbor(Cell *neighbor);

    /**
     * @brief getNeighbors.
     * @return
     */
    QList<Cell *> getNeighbors() const;

    /**
     * @brief on : Toggle the currentState to true.
     */
    void on();

    /**
     * @brief off : Toggle the currentState to false.
     */
    void off();

    // Getters for the States
    bool getPreviousState();
    bool getCurrentState();

    /**
     * @brief saveState : Save the currentState before update.
     */
    void saveState();

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;

protected:
    /**
     * @brief mousePressEvent : Toggle the cell on & off.
     * @param event
     */
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

private:
    QList<Cell *> m_neighbors;
    QPointF m_position;
    GameView *m_view;
    bool m_currentState = false;
    bool m_previousState = false;
};

#endif // CELL_H
