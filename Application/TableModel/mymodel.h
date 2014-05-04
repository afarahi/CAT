#include <QAbstractTableModel>
#include <QDebug>
#include <QBrush>
#include <QFont>


 class MyModel : public QAbstractTableModel
 {

     Q_OBJECT

 public:

     MyModel(QObject *parent);

     int rowCount(const QModelIndex &parent = QModelIndex()) const ;

     int columnCount(const QModelIndex &parent = QModelIndex()) const;

     QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

     QVariant headerData(int section, Qt::Orientation orientation, int role) const;

 };
