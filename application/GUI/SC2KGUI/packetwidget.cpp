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
    //setMaximumSize(500, 500);
    /* Create base packet widget */
    createNewPacket();
    itemsLayout = new QHBoxLayout;
    packet->setLayout(this->itemsLayout);
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
    qDebug() << "Create new packet";
    packet = new QFrame(this);
    packet->setFrameStyle(QFrame::Box);
    QPalette Pal(palette());
    Pal.setColor(QPalette::Background, Qt::gray);
    packet->setAutoFillBackground(true);
    packet->setPalette(Pal);
    packet->setFixedHeight(70);
    //packet->setFixedWidth(500);
}

void PacketWidget::drawItems()
{
    if (this->packetItems.size() == 0) {
        return;
    }

    this->clearItems();

    qDebug() << "Items in list: " << this->packetItems.count();

    QPalette Pal(palette());
    Pal.setColor(QPalette::Background, Qt::blue);

    for(int i=0; i < packetItems.size(); i++) {
        QFrame *packetItem = new QFrame;
        packetItem->setFixedHeight(40);
        packetItem->setFixedWidth(180);
        packetItem->setAutoFillBackground(true);
        packetItem->setPalette(Pal);
        itemsLayout->addWidget(packetItem);
        /*QFrame *packetItem = new QFrame;


        packetItem->setAutoFillBackground(true);
        packetItem->setPalette(Pal);
        packetItem->setFixedHeight(40);
        packetItem->setFixedWidth(180);
        itemsLayout->addWidget(packetItem);*/
        qDebug() << "Adding item " << packetItem;
    }

    updateSize();
}

void PacketWidget::addItem(PacketItem newItem)
{
    qDebug() << "Adding new item to list ";
    packetItems << newItem;
    this->drawItems();
}

void PacketWidget::addPUSItem(PUSItem item)
{
    //QFrame *item = new QFrame;

}

void PacketWidget::clearItems()
{
    while(QLayoutItem *item = itemsLayout->takeAt(0)) {
        delete item->widget();
        delete item;
        //QWidget *w = item->widget();
    }
}

void PacketWidget::updateSize()
{
    packet->setFixedWidth(packetItems.count() * 200);
}

