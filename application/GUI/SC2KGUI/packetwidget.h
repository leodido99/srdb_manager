#ifndef PACKETWIDGET_H
#define PACKETWIDGET_H

#include "pusitem.h"
#include "packetitem.h"

#include <QWidget>
#include <QFrame>
#include <QHBoxLayout>

class PacketWidget : public QWidget
{
    QFrame *packet;
    QHBoxLayout *itemsLayout;
    bool isTC;

    QList<PacketItem> packetItems;

public:
    PacketWidget();
    ~PacketWidget();

    bool getIsTC() const;
    void setIsTC(bool value);
    void addItem(PacketItem newItem);
    void drawItems();

protected:
    void dragEnterEvent(QDragEnterEvent *event) Q_DECL_OVERRIDE;
    void dragLeaveEvent(QDragLeaveEvent *event) Q_DECL_OVERRIDE;
    void dragMoveEvent(QDragMoveEvent *event) Q_DECL_OVERRIDE;
    void dropEvent(QDropEvent *event) Q_DECL_OVERRIDE;

    void createNewPacket();
    void clearItems();
    void updateSize();



    void addPUSItem(PUSItem item);
};

#endif // PACKETWIDGET_H
