#pragma once
#include <QQuickItem>
#include <QSGImageNode>
#include <QTimer>
#include <QMutex>
#include <QImage>

class StreamView : public QQuickItem
{
    Q_OBJECT
    QML_ELEMENT
public:

    StreamView(QQuickItem *parent = nullptr);

protected:
    QSGNode* updatePaintNode(QSGNode* old, UpdatePaintNodeData*) override;
private:
    QTimer _timer;
    QMutex _mutex;
    QImage _img{QSize{500, 500}, QImage::Format_ARGB32};
    bool _st = false;
};
