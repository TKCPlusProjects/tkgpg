#include <tkgpg/tkgpg_window_graphic.hpp>

namespace tkht {
namespace tkgpg {
WindowGraphic::WindowGraphic() : Window("TKGPG_WINDOW_VERTEX") {
  file_view = make_shared<ViewFile>();
  file_view->open_action = [=](const char* path){
    GraphicOpen(path);
    ShapeChange(0, 0);
  };
  file_view->save_action = [=](){
    GraphicSave();
  };

  shape_table = make_shared<ViewTableShape>();
  shape_table->height_func = [=](int index) {
    return 32.0f;
  };
  shape_table->select_action = [=](int i){
    shape_table->select_index = i;
  };
  shape_table->edit_action = [=](int i){
    ShapeChange(i, 0);
  };
  shape_table->add_action = [=](int i, Shape::Type type){
    ShapeInsert(i, type);
  };
  shape_table->remove_action = [=](int i){
    ShapeRemove(i);
  };

  polygon_table = make_shared<ViewTablePolygon>();
  polygon_table->height_func = [=](int index) {
    return 32.0f;
  };
  polygon_table->select_action = [=](int i){
    polygon_table->select_index = i;
  };
  polygon_table->edit_action = [=](int i){
    ShapePolygonUpdate(EditingShapeIndex, i, &polygon_table->cell_list[i]->point);
  };
  polygon_table->add_action = [=](int i){
    ShapePolygonInsert(shape_table->select_index, i);
  };
  polygon_table->remove_action = [=](int i){
    ShapePolygonRemove(shape_table->select_index, i);
  };

  SetShapeChanged([=](int shape_i, int vertex_i) {
    shape_table->cell_list.clear();
    for (int i = 0; i < BaseGraphic->shapes.size(); i++) {
      shared_ptr<Shape> shape = BaseGraphic->shapes[i];
      const char* type = "";
      switch (shape->type) {
      case Shape::TypePoint   : type = "TypePoint"  ; break;
      case Shape::TypeSegment : type = "TypeSegment"; break;
      case Shape::TypePolygon : type = "TypePolygon"; break;
      case Shape::TypeCircle  : type = "TypeCircle" ; break;
      }
      shape_table->cell_list.push_back(shape_table->CreateCell(type));
      shape_table->select_index = shape_i;
      
      if (i == shape_i) {
        shared_ptr<Shape> shape = BaseGraphic->shapes[shape_i];
        switch (shape->type) {
          case Shape::TypePoint: {} break;
          case Shape::TypeSegment: {} break;
          case Shape::TypePolygon: {
            shared_ptr<ShapePolygon> type_shape = static_pointer_cast<ShapePolygon>(BaseGraphic->shapes[shape_table->select_index]);
            polygon_table->cell_list.clear();
            for (Point vertex : type_shape->vertexes) {
              polygon_table->cell_list.push_back(polygon_table->CreateCell(vertex));
            }
            polygon_table->select_index = vertex_i;
          } break;
          case Shape::TypeCircle: {} break;
        }
      }
    }
  });
}

void WindowGraphic::OnUpdateSize(int width, int height) {
  pos = ImVec2(width - 330.0f, 0.0f);
  size = ImVec2(330.0f, height);

  float margin = 5.0f;
  file_view->pos = ImVec2(margin, margin);
  file_view->size = ImVec2(size.x - margin * 2.0f, 40.0f);
  shape_table->pos = ImVec2(margin, margin + 40.0f);
  shape_table->size = ImVec2(size.x - margin * 2.0f, 100.0f);
  polygon_table->pos = ImVec2(margin, margin + 40.0f + 100.0f);
  polygon_table->size = ImVec2(size.x - margin * 2.0f, size.y - 40.0f - 100.0f - margin * 2.0f);
}

void WindowGraphic::OnDisplay() {
  file_view->Display();
  ImGui::Separator();
  shape_table->Display();
  ImGui::Separator();
  polygon_table->Display();
}
} // namespace tkgpg
} // namespace tkht
