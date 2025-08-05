#pragma once
#include <QWidget>
#include <QString>

class EmptyComponent : public QWidget
{
    Q_OBJECT
public:
    explicit EmptyComponent(QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    ~EmptyComponent();

    void setInput(const QString & input);

protected:
    void initUi();

    virtual void closeEvent(QCloseEvent *event) override;

protected:
    QString _inputIni;
    QString _basePath;
    QList<QString> _types;
};