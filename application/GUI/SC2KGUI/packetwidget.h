#ifndef PACKETWIDGET_H
#define PACKETWIDGET_H

#include "pusitem.h"

#include <QWidget>
#include <QFrame>

class PacketWidget : public QWidget
{
    QFrame *packet;
    bool isTC;

public:
    PacketWidget();
    ~PacketWidget();

    bool getIsTC() const;
    void setIsTC(bool value);

protected:
    void dragEnterEvent(QDragEnterEvent *event) Q_DECL_OVERRIDE;
    void dragLeaveEvent(QDragLeaveEvent *event) Q_DECL_OVERRIDE;
    void dragMoveEvent(QDragMoveEvent *event) Q_DECL_OVERRIDE;
    void dropEvent(QDropEvent *event) Q_DECL_OVERRIDE;

    void createNewPacket();
    void addPUSItem(PUSItem item);
};

#endif // PACKETWIDGET_H
