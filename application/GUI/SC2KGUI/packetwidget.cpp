#include "packetwidget.h"

#include <QDebug>

#include <QDrag>
#include <QDragEnterEvent>
#include <QMimeData>


bool PacketWidget::getIsTC() const
{
    return isTC;
}

void PacketWidget::setIsTC(bool value)
{
    isTC = value;
}
PacketWidget::PacketWidget()
{
    setAcceptDrops(true);
    setMinimumSize(500, 500);
    setMaximumSize(500, 500);
    /* Create base packet widget */
    createNewPacket();
    /* Create */
    isTC = true;
}

PacketWidget::~PacketWidget()
{

}

void PacketWidget::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("text/pus-item")) {
        qDebug() << "dragEnterEvent" << "accepted";
        event->accept();
    } else {
        qDebug() << "dragEnterEvent" << "ignored";
        event->ignore();
    }
}

void PacketWidget::dragLeaveEvent(QDragLeaveEvent *event)
{
    /*QRect updateRect = highlightedRect;
    highlightedRect = QRect();
    update(updateRect);*/
    event->accept();
}

void PacketWidget::dragMoveEvent(QDragMoveEvent *event)
{
    if (event->mimeData()->hasFormat("text/pus-item")) {
        qDebug() << "dragEnterEvent" << "accepted";
        event->setDropAction(Qt::MoveAction);
        event->accept();
    } else {
        qDebug() << "dragEnterEvent" << "ignored";
        event->ignore();
    }
}

void PacketWidget::dropEvent(QDropEvent *event)
{
    if (event->mimeData()->hasFormat("text/pus-item")) {
        qDebug() << "dragEnterEvent" << "accepted";
        event->setDropAction(Qt::MoveAction);
        event->accept();
    } else {
        qDebug() << "dragEnterEvent" << "ignored";
        event->ignore();
    }
}

void PacketWidget::createNewPacket()
{
    packet = new QFrame(this);
    packet->setFrameStyle(QFrame::Box);
    QPalette Pal(palette());
    Pal.setColor(QPalette::Background, Qt::gray);
    packet->setAutoFillBackground(true);
    packet->setPalette(Pal);
    packet->setFixedHeight(50);
    packet->setFixedWidth(200);
}

void PacketWidget::addPUSItem(PUSItem item)
{
    QFrame *item = new QFrame;

}

