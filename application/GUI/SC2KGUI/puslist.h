#ifndef PUSLIST_H
#define PUSLIST_H

#include <QListWidget>

/**
 * @brief The PUSlist class
 * This class contains the base pieces the user can drag/drop on the packetwidget
 */
class PUSlist : public QListWidget
{
public:
    PUSlist();
    ~PUSlist();
    void addPiece(QString name);

protected:
    void dragEnterEvent(QDragEnterEvent *event) Q_DECL_OVERRIDE;
    void dragMoveEvent(QDragMoveEvent *event) Q_DECL_OVERRIDE;
    void dropEvent(QDropEvent *event) Q_DECL_OVERRIDE;
    void startDrag(Qt::DropActions supportedActions) Q_DECL_OVERRIDE;
};

#endif // PUSLIST_H
