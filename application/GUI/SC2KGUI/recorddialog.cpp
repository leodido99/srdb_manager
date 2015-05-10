#include "recorddialog.h"
#include <QSqlField>

#define DEFAULT_NB_FIELDS_PER_ROW 10

RecordDialog::RecordDialog(QString wndName, QSqlRecord record)
{
    setWindowTitle(wndName);

    this->record = record;
    this->nbFieldsPerRow = DEFAULT_NB_FIELDS_PER_ROW;

    QFormLayout *formLayout = new QFormLayout;
    QHBoxLayout *mainLayout = new QHBoxLayout;

    mainLayout->addLayout(formLayout);

    for(int i=0; i < this->record.count(); i++) {
        /*qDebug() << QString("Creating %1").arg(record.field(i).name());*/
        this->createField(this->record.field(i), formLayout);
        if ((i % this->nbFieldsPerRow) == 0 && i != 0) {
            /* Number of fields per row */
            mainLayout->addLayout(formLayout);
            formLayout = new QFormLayout;
        }
    }

    /* Connect mapper signal to update function */
    connect(&this->mapper, SIGNAL(mapped(QString)), this, SLOT(updateRecord(QString)));

    QPushButton *createButton = new QPushButton(tr("Accept"));
    connect(createButton, SIGNAL(clicked()), this, SLOT(createRecord()));

    QPushButton *closeButton = new QPushButton(tr("Close"));
    connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));

    QVBoxLayout *frame = new QVBoxLayout;
    frame->addLayout(mainLayout);
    frame->addWidget(createButton);
    frame->addWidget(closeButton);

    setLayout(frame);



    /* Form Layout */


    /*formLayout->addRow(tr("&Email:"), emailLineEdit);
    formLayout->addRow(tr("&Age:"), ageSpinBox);
    */


    /*QListWidget *contentsWidget = new QListWidget;
    contentsWidget->setViewMode(QListView::IconMode);
    contentsWidget->setIconSize(QSize(96, 84));
    contentsWidget->setMovement(QListView::Static);
    contentsWidget->setMaximumWidth(128);
    contentsWidget->setSpacing(12);*/

  /*  QStackedWidget *pagesWidget = new QStackedWidget;
    pagesWidget->addWidget(new ConfigurationPage);
    pagesWidget->addWidget(new UpdatePage);
    pagesWidget->addWidget(new QueryPage);*/

   // QPushButton *closeButton = new QPushButton(tr("Close"));

    //createIcons();
  /*  contentsWidget->setCurrentRow(0);

    connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));

    QHBoxLayout *horizontalLayout = new QHBoxLayout;
    horizontalLayout->addWidget(contentsWidget);
   /* horizontalLayout->addWidget(pagesWidget, 1);*/

  /*  QHBoxLayout *buttonsLayout = new QHBoxLayout;
    buttonsLayout->addStretch(1);
    buttonsLayout->addWidget(closeButton);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(horizontalLayout);
    mainLayout->addStretch(1);
    mainLayout->addSpacing(12);
    mainLayout->addLayout(buttonsLayout);
    setLayout(mainLayout);

    setWindowTitle(tr("Config Dialog"));*/
}

void RecordDialog::setNbFieldsPerRow(int nbfield)
{
    if (nbfield > 0) {
        this->nbFieldsPerRow = nbfield;
    } else {
        qDebug() << "Cannot set nb field per row to something equal to 0 or below";
    }
}

void RecordDialog::createField(QSqlField field, QFormLayout *layout)
{
    /* Create edit */
    QLineEdit *edit = new QLineEdit();
    edit->text() = field.value().toString();
    /* Connect edit finished signal to mapper */
    connect(edit, SIGNAL(editingFinished()), &this->mapper, SLOT(map()));
    /* Send field name on signal */
    mapper.setMapping(edit, field.name());
    /* new row */
    layout->addRow(field.name(), edit);    
}

void RecordDialog::createRecord()
{
    qDebug() << "tst";
}

void RecordDialog::updateRecord(QString fieldname)
{
    bool updated = false;

    /* We must find the value of the field */
    QListIterator<QLabel*> iter(this->findChildren<QLabel*>());
    /* Iterate through all children labels to find the correct one */
    while(iter.hasNext()) {
        QLabel* lbl = iter.next();
        if (lbl->text() == fieldname) {
            /* Update record */
            QLineEdit *edit =(QLineEdit*)lbl->buddy();
            this->record.value(fieldname).setValue(edit->text());
            qDebug() << "Update " << lbl->text() << " to " << edit->text();
            updated = true;
        }
    }

    if (!updated) {
        qDebug() << Q_FUNC_INFO << " Could not update record" << fieldname;
    } else {
        this->updateFields();
    }
}

void RecordDialog::updateFields()
{
    QListIterator<QLabel*> iter(this->findChildren<QLabel*>());
    while(iter.hasNext()) {
        QLabel* lbl = iter.next();
        QLineEdit *edit =(QLineEdit*)lbl->buddy();
        edit->setText(this->record.value(lbl->text()).toString());
        qDebug() << lbl->text() << this->record.value(lbl->text()).toString();
    }
}

