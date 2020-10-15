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

#include "cell.h"

#include "gameview.h"

Cell::Cell(GameView *view) : m_view(view)
{
    setZValue(-1); // Put the cell in the back
    m_neighbors.reserve(8);
}

void Cell::addNeighbor(Cell *neighbor)
{
    m_neighbors << neighbor;
}

QList<Cell *> Cell::getNeighbors() const
{
    return m_neighbors;
}

bool Cell::getCurrentState()
{
    return m_currentState;
}

bool Cell::getPreviousState()
{
    return m_previousState;
}

void Cell::saveState()
{
    m_previousState = m_currentState;
}

void Cell::on()
{
    m_currentState = true;
    update();
}

void Cell::off()
{
    m_currentState = false;
    update();
}

QRectF Cell::boundingRect() const
{
    return QRectF(-5, -5, 10, 10);
}

QPainterPath Cell::shape() const
{
    QPainterPath path;
    path.addRect(-5, -5, 10, 10);
    return path;
}

void Cell::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED( option )
    Q_UNUSED( widget )

    painter->setPen(Qt::SolidLine);
    painter->setPen(Qt::gray);

    // Based on the current state fill the cell square in black or nothing.
    if(m_currentState) {
        painter->setBrush(Qt::black);
    } else {
        painter->setBrush(Qt::NoBrush);
    }
    painter->drawRect(QRect(-5, -5, 10, 10));
}

void Cell::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED( event )

    if(m_currentState) {
        off();
    } else {
        on();
    }
}



