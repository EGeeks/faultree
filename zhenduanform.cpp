#include "zhenduanform.h"
#include "ui_zhenduanform.h"

ZhenDuanForm::ZhenDuanForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ZhenDuanForm)
{
    ui->setupUi(this);

    listAllNode();
}

ZhenDuanForm::~ZhenDuanForm()
{
    delete ui;
}


void ZhenDuanForm::listAllNode()
{
    QSqlQuery query;
    int count = 0;

    query.exec("SELECT COUNT(*) FROM tree");
    while (query.next()) {
        count = query.value(0).toInt();
    }

    QStandardItemModel *model = new QStandardItemModel(count,3);
    model->setHeaderData(0, Qt::Horizontal, tr("root"));
    model->setHeaderData(1, Qt::Horizontal, tr("two"));
    model->setHeaderData(2, Qt::Horizontal, tr("Err"));

    int index = 0;
    query.exec("SELECT nodeID,parentNodeID,ErrDesc FROM tree");
    while (query.next()) {
        qDebug() << "SELECT:" << query.value(0).toInt() << query.value(1).toInt() << query.value(2).toString();

        int nodeID = query.value(0).toInt();
        int parentNodeID = query.value(1).toInt();
        QString ErrDesc = query.value(2).toString();

        QStandardItem *item = new QStandardItem(ErrDesc);
        item->setData(nodeID,  Qt::UserRole + 100);

        if(parentNodeID == 0) {
            model->setItem(index, 0, item);
            index++;

            continue;
        }

        for(int i = 0; i < index - 1; i++) {
            int node_id = model->item(i)->data(Qt::UserRole + 100).toInt();
            if(node_id == parentNodeID) {
                model->item(i)->appendRow(item);
            }
        }
    }


    //    QStandardItemModel *model = new QStandardItemModel(count,3);
    //    model->setHeaderData(0, Qt::Horizontal, tr("root"));
    //    model->setHeaderData(1, Qt::Horizontal, tr("two"));
    //    model->setHeaderData(1, Qt::Horizontal, tr("Err"));
    //    QStandardItem *item1 = new QStandardItem("avahi-daemon");
    //    QStandardItem *item2 = new QStandardItem("bluetooth");
    //    QStandardItem *item3 = new QStandardItem("crond");
    //    QStandardItem *item4 = new QStandardItem("cups");
    //    model->setItem(0, 0, item1);
    //    model->setItem(1, 0, item2);
    //    model->setItem(2, 0, item3);
    //    model->setItem(3, 0, item4);
    //    QStandardItem *item5 = new QStandardItem("fifth");
    //    item4->appendRow(item5);
    //    QModelIndex parent;
    //    for (int i = 0; i < 4; ++i) {
    //        parent = model->index(0, 0, parent);
    //        model->insertRows(0, 1, parent);
    //        model->insertColumns(0, 1, parent);
    //        QModelIndex index = model->index(0, 0, parent);
    //        model->setData(index, i);
    //    }
    ui->treeView->setModel(model);
}
