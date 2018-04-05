#include "my_graphics_scene.h"

My_graphics_scene::My_graphics_scene(): QGraphicsScene() {}

void My_graphics_scene::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    last = event->scenePos().toPoint();
}

void My_graphics_scene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    first = event->scenePos().toPoint();
}

void My_graphics_scene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    last = event->scenePos().toPoint();
}

QPoint My_graphics_scene::get_first() {
    return first;
}

QPoint My_graphics_scene::get_last() {
    return last;
}
