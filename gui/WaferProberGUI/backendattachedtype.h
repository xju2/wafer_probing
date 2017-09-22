#ifndef BACKENDATTACHEDTYPE_H
#define BACKENDATTACHEDTYPE_H

#include <QObject>

class BackendAttachedType : public QObject
{
    Q_OBJECT
public:
    explicit BackendAttachedType(QObject *parent = nullptr);

signals:
    void posXChanged();
    void posYChanged();

public slots:
};

#endif // BACKENDATTACHEDTYPE_H
