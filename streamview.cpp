#include "streamview.hpp"
#include <QSGTexture>
#include <QSGImageNode>
#include <QBuffer>
#include <QSGRendererInterface>
#include <QSGMaterialShader>
#include <QSGTextureMaterial>
#include <QDateTime>

StreamView::StreamView(QQuickItem *parent) : QQuickItem(parent)
{
    connect(this, &StreamView::visibleChanged, this, [=]() {this->update(); });
    setFlag(ItemHasContents, true);
    _timer.setInterval(1000);
    _timer.setSingleShot(false);
    _timer.start();
    connect(&_timer, &QTimer::timeout, this, [=]() {
        update();
    });
}

QSGNode* StreamView::updatePaintNode(QSGNode* old, UpdatePaintNodeData*)
{
    QMutexLocker ml(&_mutex);
    static QSGImageNode *imgnode = nullptr;

    _img.fill(_st ? Qt::red : Qt::blue);
    auto texture = window()->createTextureFromImage(_img);

    if (old == nullptr) {
        old = new QSGNode();
        imgnode = window()->createImageNode();
        imgnode->setRect(boundingRect());
        imgnode->setSourceRect(QRectF(QPointF(0.0, 0.0), texture->textureSize()));
        imgnode->setTexture(texture);
        imgnode->setOwnsTexture(true);
        old->appendChildNode(imgnode);
        imgnode->markDirty(QSGNode::DirtyGeometry);
        imgnode->setFlag(QSGNode::OwnedByParent, true);
    }
    else {
        imgnode->setTexture(texture);
        imgnode->setOwnsTexture(true);

    }
    imgnode->markDirty(QSGNode::DirtyGeometry);
    imgnode->setFlag(QSGNode::OwnedByParent, true);
    _st = !_st;
    return old;
}
