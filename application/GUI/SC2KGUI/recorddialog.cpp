#include "recorddialog.h"
#include <QSqlField>

#define DEFAULT_NB_FIELDS_PER_ROW 10
#define NB_WIDGETS_PER_ROW 4
#define LBLNAME_FIXED_WIDTH 80
#define LBLMANDA_FIXED_WIDTH 5
#define LBLTYPE_FIXED_WIDTH 50

RecordDialog::RecordDialog(QString wndName, QSqlRecord record)
{
    setWindowTitle(wndName);

    this->record = QSqlRecord(record);
    this->nbFieldsPerRow = DEFAULT_NB_FIELDS_PER_ROW;

    /* Contains n field */
    QVBoxLayout *fieldsLayout = new QVBoxLayout;
    fieldsLayout->setAlignment(Qt::AlignTop);

    /* Contains n fiedlsLayout */
    QHBoxLayout *colLayout = new QHBoxLayout;
    colLayout->addLayout(fieldsLayout);

    /* Run through all record fields and create the GUI */
    for(int i=0; i < this->record.count(); i++) {
        /* Create new horizontal layout for the fields widgets */
        QHBoxLayout *field = new QHBoxLayout;
        /* Create widgets */
        this->createField(this->record.field(i), field);
        fieldsLayout->addLayout(field);

        if ((i % this->nbFieldsPerRow) == 0 && i != 0) {                     
            /* Add vertical layout and create a new one */
            fieldsLayout = new QVBoxLayout;
            fieldsLayout->setAlignment(Qt::AlignTop);
            colLayout->addLayout(fieldsLayout);
        }
    }

    /* Connect mapper signal to update function so that we can pass the field name */
    connect(&this->mapper, SIGNAL(mapped(QString)), this, SLOT(updateRecord(QString)));

    QPushButton *createButton = new QPushButton(tr("Accept"));
    connect(createButton, SIGNAL(clicked()), this, SLOT(createRecord()));

    QPushButton *closeButton = new QPushButton(tr("Close"));
    connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));

    QVBoxLayout *frame = new QVBoxLayout;
    frame->addLayout(colLayout);
    frame->addWidget(createButton);
    frame->addWidget(closeButton);

    this->setLayout(frame);

    this->updateFields();
}

void RecordDialog::setNbFieldsPerRow(int nbfield)
{
    if (nbfield > 0) {
        this->nbFieldsPerRow = nbfield;
    } else {
        qDebug() << "Cannot set nb field per row to something equal to 0 or below";
    }
}

void RecordDialog::createField(QSqlField field, QHBoxLayout *layout)
{
    /* Create edit */
    QLineEdit *edit = new QLineEdit();
    edit->text() = field.value().toString();
    edit->setMaxLength(field.length());
    qDebug() << field.defaultValue() << field.isGenerated();
    /* Add edit to hash map for value retrieval during update */
    this->hash[field.name()] = edit;
    /* Connect edit finished signal to mapper */
    connect(edit, SIGNAL(editingFinished()), &this->mapper, SLOT(map()));
    /* Send field name on signal */
    mapper.setMapping(edit, field.name());
    /* Create labels */
    QLabel *lblName = new QLabel();
    lblName->setBuddy(edit);
    lblName->setText(field.name());
    lblName->setFixedWidth(LBLNAME_FIXED_WIDTH);
    QLabel *lblType = new QLabel();
    lblType->setFixedWidth(LBLTYPE_FIXED_WIDTH);
    switch(field.type()) {
        case QVariant::String:
            lblType->setText(QString("Char(%1)").arg(field.length()));
        break;
        case QVariant::Int:
            lblType->setText(QString("Int(%1)").arg(field.length()));
            /* Set validator for line edit */
            edit->setValidator(new QIntValidator);
        break;
        default:
            qDebug() << "Unhandled type " << field.type();
        break;
    }
    QLabel *lblMandatory = new QLabel();
    lblMandatory->setFixedWidth(LBLMANDA_FIXED_WIDTH);
    if (field.requiredStatus() == QSqlField::Required) {
        lblMandatory->setText("*");
    }
    /* Add widgets to the layout */
    layout->addWidget(lblName);    
    layout->addWidget(lblType);    
    layout->addWidget(lblMandatory);
    layout->addWidget(edit);
}

void RecordDialog::createRecord()
{
    emit recordUpdated(this->record);
}

void RecordDialog::updateRecord(QString fieldname)
{    
    if (this->hash.contains(fieldname)) {
        qDebug() << "Update " << fieldname << " to " << this->hash[fieldname]->text() << " from " << this->record.value(fieldname);

        switch(this->record.value(fieldname).type()) {
            case QVariant::String:
                this->record.setValue(fieldname, this->hash[fieldname]->text());
            break;
            case QVariant::Int:
                this->record.setValue(fieldname, this->hash[fieldname]->text().toInt());
            break;
            default:
                qDebug() << Q_FUNC_INFO << "Unhandled type " << this->record.value(fieldname).type();
            break;
        }
    } else {
        qDebug() << Q_FUNC_INFO << "Field " << fieldname << " cannot be found in hash table";
    }
}

void RecordDialog::updateFields()
{    
    /* Update all edits with the record value */
    for(int i=0; i < this->record.count(); i++) {
        this->hash[this->record.field(i).name()]->setText(this->record.field(i).value().toString());
    }
}

