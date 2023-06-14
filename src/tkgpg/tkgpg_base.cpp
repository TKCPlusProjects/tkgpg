#include <tkgpg/tkgpg_base.hpp>

namespace tkht {
namespace tkgpg {
shared_ptr<Graphic> BaseGraphic = make_shared<Graphic>();
shared_ptr<Graphic> CanvasGraphic = make_shared<Graphic>();

int EditingShapeIndex = 0;
int EditingVertexIndex = 0;
shared_ptr<ShapePoint> EditingVertexesShape = make_shared<ShapePoint>();
shared_ptr<Graphic> EditingVertexesGraphic = make_shared<Graphic>();
shared_ptr<ShapePoint> EditingVertexShape = make_shared<ShapePoint>();
shared_ptr<Graphic> EditingVertexGraphic = make_shared<Graphic>();

vector<TKGPGShapeChangedCallback> ShapeChangedCallbacks;

void GraphicOpen(const char* path) {
  if (BaseGraphic->path) {
    free((void*)BaseGraphic->path);
  }
  BaseGraphic->path = strdup(path);
  BaseGraphic->color = Color(0.0f, 1.0f, 0.0f, 1.0f);
  BaseGraphic->fillcolor = Color(0.0f, 0.5f, 0.0f, 1.0f);
  BaseGraphic->shapes.clear();
  BaseGraphic->Read();

  CanvasGraphic->shapes.clear();
  CanvasGraphic->color = Color(0.6f, 0.6f, 0.6f, 1.0f);
  shared_ptr<ShapeSegment> segment = make_shared<ShapeSegment>();
  for (int i = -10; i <= 10; i++) {
    int symbol = i % 2 == 0 ? 1 : -1;
    segment->vertexes.push_back(Point(symbol * -10.0f, i));
    segment->vertexes.push_back(Point(symbol *  10.0f, i));
    segment->vertexes.push_back(Point(i, symbol * -10.0f));
    segment->vertexes.push_back(Point(i, symbol *  10.0f));
  }
  CanvasGraphic->shapes.push_back(segment);
  CanvasGraphic->shapes.push_back(make_shared<ShapePoint>(5.0f, vector<Point>{
    Point(),
  }));

  EditingVertexesShape->size = 10.0f;
  EditingVertexesGraphic->shapes.clear();
  EditingVertexesGraphic->color = Color(0.0f, 1.0f, 0.0f, 1.0f);
  EditingVertexesGraphic->shapes.push_back(EditingVertexesShape);

  EditingVertexShape->size = 10.0f;
  EditingVertexGraphic->shapes.clear();
  EditingVertexGraphic->color = Color(1.0f, 0.0f, 0.0f, 1.0f);
  EditingVertexGraphic->shapes.push_back(EditingVertexShape);
}
void GraphicSave() {
  BaseGraphic->Write();
}

void SetShapeChanged(TKGPGShapeChangedCallback callback) {
  ShapeChangedCallbacks.push_back(callback);
}
void ShapeChange(int shape_i, int vertex_i) {
  for (TKGPGShapeChangedCallback callback : ShapeChangedCallbacks) {
    callback(shape_i, vertex_i);
  }
  shared_ptr<Shape> shape = BaseGraphic->shapes[shape_i];
  switch (shape->type) {
  case Shape::TypePoint: {} break;
  case Shape::TypeSegment: {} break;
  case Shape::TypePolygon: {
    shared_ptr<ShapePolygon> type_shape = static_pointer_cast<ShapePolygon>(shape);
    EditingVertexesShape->vertexes = type_shape->vertexes;
    EditingVertexShape->vertexes.clear();
    EditingVertexShape->vertexes.push_back(EditingVertexesShape->vertexes[vertex_i]);
  } break;
  case Shape::TypeCircle: {} break;
  }
}
void ShapeInsert(int shape_i, Shape::Type type) {
  int select_i = shape_i + 1;
  switch (type) {
  case Shape::TypePoint: {} break;
  case Shape::TypeSegment: {} break;
  case Shape::TypePolygon: {
    shared_ptr<ShapePolygon> type_shape = make_shared<ShapePolygon>(vector<Point>{
      Point(-1.0f,  1.0f),
      Point( 1.0f,  1.0f),
      Point( 1.0f, -1.0f),
      Point(-1.0f, -1.0f),
    });
    BaseGraphic->shapes.insert(BaseGraphic->shapes.begin() + select_i, type_shape);
    ShapeChange(select_i, 0);
  } break;
  case Shape::TypeCircle: {} break;
  }
}
void ShapeRemove(int shape_i) {
  int select_i = shape_i;
  BaseGraphic->shapes.erase(BaseGraphic->shapes.begin() + shape_i);
  if (select_i > 0 && select_i >= BaseGraphic->shapes.size()) {
    select_i = BaseGraphic->shapes.size() - 1;
  }
  ShapeChange(select_i, 0);
}
void ShapePolygonInsert(int shape_i, int vertex_i, Point* vertex) {
  int select_i = vertex_i + 1;
  shared_ptr<ShapePolygon> type_shape = static_pointer_cast<ShapePolygon>(BaseGraphic->shapes[shape_i]);
  if (vertex == nullptr) {
    Point curr = type_shape->vertexes[vertex_i];
    Point next = select_i < type_shape->vertexes.size() ? type_shape->vertexes[select_i] : type_shape->vertexes[0];
    Point point = 0.5f * (curr + next);
    vertex = &point;
  }
  type_shape->vertexes.insert(type_shape->vertexes.begin() + select_i, *vertex);
  ShapeChange(shape_i, select_i);
}
void ShapePolygonUpdate(int shape_i, int vertex_i, Point* vertex) {
  int select_i = vertex_i;
  shared_ptr<Shape> shape = BaseGraphic->shapes[shape_i];
  shared_ptr<ShapePolygon> type_shape = static_pointer_cast<ShapePolygon>(shape);
  type_shape->vertexes[vertex_i] = *vertex;
  ShapeChange(shape_i, select_i);
}
void ShapePolygonRemove(int shape_i, int vertex_i) {
  int select_i = vertex_i;
  shared_ptr<ShapePolygon> type_shape = static_pointer_cast<ShapePolygon>(BaseGraphic->shapes[shape_i]);
  type_shape->vertexes.erase(type_shape->vertexes.begin() + vertex_i);
  if (select_i > 0 && select_i >= type_shape->vertexes.size()) {
    select_i = type_shape->vertexes.size() - 1;
  }
  ShapeChange(shape_i, vertex_i);
}
} // namespace tkgpg
} // namespace tkht
