#include "puslist.h"

#include <QDebug>

#include <QMimeData>
#include <QDragEnterEvent>
#include <QDrag>

PUSlist::PUSlist()
{
    setDragEnabled(true);
    setAcceptDrops(true);
    setDropIndicatorShown(true);
}

PUSlist::~PUSlist()
{

}

/* Adds a new piece to the list */
void PUSlist::addPiece(QString name)
{
    QListWidgetItem *newItem = new QListWidgetItem;
    newItem->setText(name);
    newItem->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled);
    this->addItem(newItem);
}

/* Event which is sent to a widget when a drag and drop action enters it */
void PUSlist::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("text/pus-item")) {
        qDebug() << "dragEnterEvent" << "accepted";
        event->accept();
    } else {
        qDebug() << "dragEnterEvent" << "ignored";
        event->ignore();
    }
}

/* Event which is sent while a drag and drop action is in progress */
void PUSlist::dragMoveEvent(QDragMoveEvent *event)
{
    if (event->mimeData()->hasFormat("text/pus-item")) {
        qDebug() << "dragMoveEvent" << "accepted";
        event->setDropAction(Qt::MoveAction);
        event->accept();
    } else {
        qDebug() << "dragMoveEvent" << "ignored";
        event->ignore();
    }
}

/* Event which is sent when a drag and drop action is completed */
void PUSlist::dropEvent(QDropEvent *event)
{
    if (event->mimeData()->hasFormat("image/x-puzzle-piece")) {
        qDebug() << "dropEvent" << "accepted";
        /*QByteArray pieceData = event->mimeData()->data("image/x-puzzle-piece");
        QDataStream dataStream(&pieceData, QIODevice::ReadOnly);
        QPixmap pixmap;
        QPoint location;
        dataStream >> pixmap >> location;

        addPiece(pixmap, location);*/

        event->setDropAction(Qt::MoveAction);
        event->accept();
    } else {
        qDebug() << "dropEvent" << "ignored";
        event->ignore();
    }
}

/* Starts a drag by calling drag->exec() using the given supportedActions.
 * This method is called before anything else is done when the user wants to drag an item */
void PUSlist::startDrag(Qt::DropActions supportedActions)
{
    /* Get current item */
    QListWidgetItem *item = currentItem();

    qDebug() << "startDrag" << item->text();

    /* Create new mime for drag/drop */
    QMimeData *mimeData = new QMimeData;
    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    /* Add name of object to create */
    dataStream << item->text();

    mimeData->setData("text/pus-item", itemData);

    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    //drag->setHotSpot(QPoint(pixmap.width()/2, pixmap.height()/2));
    //drag->setPixmap(pixmap);

    drag->exec(Qt::MoveAction);
    /*if (drag->exec(Qt::MoveAction) == Qt::MoveAction)
        delete takeItem(row(item));*/
}

