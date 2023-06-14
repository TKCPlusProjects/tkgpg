#include <tkgpg/tkgpg_window_graphic.hpp>

namespace tkht {
namespace tkgpg {
WindowVertex::WindowVertex() : Window("TKGPG_WINDOW_VERTEX") {
  file_view = make_shared<ViewFile>();
  file_view->open_action = [=](const char* path){
    GraphicOpen(path);
    vertex_table->cell_list.clear();
    for (shared_ptr<Shape> shape : BaseGraphic->shapes) {
      const char* type = "";
      switch (shape->type) {
      case Shape::TypePoint   : type = "TypePoint"  ; break;
      case Shape::TypeSegment : type = "TypeSegment"; break;
      case Shape::TypePolygon : type = "TypePolygon"; break;
      case Shape::TypeCircle  : type = "TypeCircle" ; break;
      }
      vertex_table->cell_list.push_back(vertex_table->CreateCell(type));
    }
    vertex_table->select_action(0);
    vertex_table->edit_action(0);
  };
  file_view->save_action = [=](){
    GraphicSave();
  };

  vertex_table = make_shared<ViewTableShape>();
  vertex_table->height_func = [=](int index) {
    return 32.0f;
  };
  vertex_table->select_action = [=](int i){
    vertex_table->select_index = i;
  };
  vertex_table->edit_action = [=](int i){
    ShapeChange(i);
  };
  vertex_table->add_action = [=](int i, Shape::Type type){
    switch (type) {
      case Shape::TypePoint: {} break;
      case Shape::TypeSegment: {} break;
      case Shape::TypePolygon: {} break;
      case Shape::TypeCircle: {} break;
    }
  };
  vertex_table->remove_action = [=](int i){
    vertex_table->cell_list.erase(vertex_table->cell_list.begin() + i);
  };

  polygon_table = make_shared<ViewTablePolygon>();
  polygon_table->height_func = [=](int index) {
    return 32.0f;
  };
  polygon_table->select_action = [=](int i){
    polygon_table->select_index = i;
  };
  polygon_table->edit_action = [=](int i){
    shared_ptr<ShapePolygon> type_shape = static_pointer_cast<ShapePolygon>(BaseGraphic->shapes[vertex_table->select_index]);
    type_shape->vertexes[i] = polygon_table->cell_list[i]->point;
  };
  polygon_table->add_action = [=](int i){
    ShapePolygonInsert(vertex_table->select_index, i);
    polygon_table->select_index = i+1;
  };
  polygon_table->remove_action = [=](int i){
    ShapePolygonRemove(vertex_table->select_index, i);
  };

  SetShapeChanged([=](int shape_i) {
    if (vertex_table->select_index == shape_i) {
      shared_ptr<Shape> shape = BaseGraphic->shapes[shape_i];
      switch (shape->type) {
        case Shape::TypePoint: {} break;
        case Shape::TypeSegment: {} break;
        case Shape::TypePolygon: {
          shared_ptr<ShapePolygon> type_shape = static_pointer_cast<ShapePolygon>(BaseGraphic->shapes[vertex_table->select_index]);
          polygon_table->cell_list.clear();
          for (Point vertex : type_shape->vertexes) {
            polygon_table->cell_list.push_back(polygon_table->CreateCell(vertex));
          }
          if (polygon_table->select_index > polygon_table->cell_list.size()) {
            polygon_table->select_index = polygon_table->cell_list.size() - 1;
          }
        } break;
        case Shape::TypeCircle: {} break;
      }
    }
  });
}

void WindowVertex::OnUpdateSize(int width, int height) {
  pos = ImVec2(width - 330.0f, 0.0f);
  size = ImVec2(330.0f, height);

  float margin = 5.0f;
  file_view->pos = ImVec2(margin, margin);
  file_view->size = ImVec2(size.x - margin * 2.0f, 40.0f);
  vertex_table->pos = ImVec2(margin, margin + 40.0f);
  vertex_table->size = ImVec2(size.x - margin * 2.0f, 100.0f);
  polygon_table->pos = ImVec2(margin, margin + 40.0f + 100.0f);
  polygon_table->size = ImVec2(size.x - margin * 2.0f, size.y - 40.0f - 100.0f - margin * 2.0f);
}

void WindowVertex::OnDisplay() {
  file_view->Display();
  ImGui::Separator();
  vertex_table->Display();
  ImGui::Separator();
  polygon_table->Display();
}
} // namespace tkgpg
} // namespace tkht
