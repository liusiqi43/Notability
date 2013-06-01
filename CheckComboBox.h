#include <QStyledItemDelegate>
#include <QCheckBox>

#include <QStyleOptionViewItemV4>

class CheckComboBoxDelegate : public QStyledItemDelegate {
public:
    CheckComboBoxDelegate(QObject *parent = 0) : QStyledItemDelegate(parent) {

    }

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
        const bool value = index.data(Qt::UserRole).toBool();
        const QString text = index.data(Qt::DisplayRole).toString();

        const QStyleOptionViewItemV4 sov = static_cast<const QStyleOptionViewItemV4>(option);

        const QStyle *style = sov.widget->style();
        QStyleOptionButton opt;
        opt.state |= value ? QStyle::State_On : QStyle::State_Off;
        opt.state |= QStyle::State_Enabled;
        opt.text = text;
        opt.rect = option.rect;

        style->drawControl(QStyle::CE_CheckBox, &opt,painter);

    }

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const {
        Q_UNUSED(option);
        Q_UNUSED(index);

        QCheckBox *checkBox = new QCheckBox(parent);
        return checkBox;
    }

    void setEditorData(QWidget *editor, const QModelIndex &index) const {
        QCheckBox *checkBox = qobject_cast<QCheckBox *>(editor);
        if (checkBox) {
            const QString text = index.data(Qt::DisplayRole).toString();
            const bool checked = index.data(Qt::UserRole).toBool();
            checkBox->setText(text);
            checkBox->setChecked(checked);
        }
    }

    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const {
        QCheckBox *checkBox = qobject_cast<QCheckBox *>(editor);
        if (checkBox) {
            model->setData(index, checkBox->isChecked(), Qt::UserRole);
        }
    }

    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const {
        Q_UNUSED(index);
        editor->setGeometry(option.rect);
    }


};

class CheckComboBox : public QComboBox {
public:
    CheckComboBox(QWidget *parent = 0) : QComboBox(parent) {
        view()->setItemDelegate(new CheckComboBoxDelegate(this));
        view()->setEditTriggers(QAbstractItemView::CurrentChanged);

        view()->viewport()->installEventFilter(this);
    }

protected:
    bool eventFilter(QObject *obj, QEvent *ev) {
        if (obj == view()->viewport() && ev->type() == QEvent::MouseButtonRelease) {
            return true;
        }

        return QComboBox::eventFilter(obj, ev);
    }


};
