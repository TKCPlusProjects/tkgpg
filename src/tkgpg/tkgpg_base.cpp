#include <tkgpg/tkgpg_base.hpp>

namespace tkht {
namespace tkgpg {
shared_ptr<Graphic> BaseGraphic = make_shared<Graphic>();
function<void(int)> ShapeChangedCallback = nullptr;

void GraphicOpen(const char* path) {
  if (BaseGraphic->path) {
    free((void*)BaseGraphic->path);
  }
  BaseGraphic->path = strdup(path);
  BaseGraphic->color = Color(0.0f, 1.0f, 0.0f, 1.0f);
  BaseGraphic->fillcolor = Color(0.0f, 0.5f, 0.0f, 1.0f);
  BaseGraphic->shapes.clear();
  BaseGraphic->Read();
}
void GraphicSave() {
  BaseGraphic->Write();
}

void SetShapeChanged(function<void(int)> callback) {
  ShapeChangedCallback = callback;
}
void ShapeChange(int shape_i) {
  if (ShapeChangedCallback) ShapeChangedCallback(shape_i);
}
void ShapePolygonInsert(int shape_i, int vertex_i, Point* vertex) {
  shared_ptr<ShapePolygon> type_shape = static_pointer_cast<ShapePolygon>(BaseGraphic->shapes[shape_i]);
  if (vertex == nullptr) {
    Point curr = type_shape->vertexes[vertex_i];
    Point next = vertex_i+1 < type_shape->vertexes.size() ? type_shape->vertexes[vertex_i+1] : type_shape->vertexes[0];
    Point point = 0.5f * (curr + next);
    vertex = &point;
  }
  type_shape->vertexes.insert(type_shape->vertexes.begin() + vertex_i + 1, *vertex);
  if (ShapeChangedCallback) ShapeChangedCallback(shape_i);
}
void ShapePolygonRemove(int shape_i, int vertex_i) {
  shared_ptr<ShapePolygon> type_shape = static_pointer_cast<ShapePolygon>(BaseGraphic->shapes[shape_i]);
  type_shape->vertexes.erase(type_shape->vertexes.begin() + vertex_i);
  if (ShapeChangedCallback) ShapeChangedCallback(shape_i);
}
} // namespace tkgpg
} // namespace tkht
