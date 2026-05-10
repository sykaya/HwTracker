#include "DraggableLabel.h"

DraggableLabel::DraggableLabel(QWidget *parent)
    : QLabel(parent)
{
}

void DraggableLabel::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
        dragStartPosition = event->pos();
    QLabel::mousePressEvent(event);
}

void DraggableLabel::mouseMoveEvent(QMouseEvent *event)
{
    if (!(event->buttons() & Qt::LeftButton))
        return;

    if (window())
        window()->move(window()->pos() + (event->pos() - dragStartPosition));
}
