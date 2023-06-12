#include <tkgpg/tkgpg_window_graphic.hpp>

namespace tkht {
namespace tkgpg {
WindowVertex::WindowVertex() : Window("TKGPG_WINDOW_VERTEX") {
  graphic = make_shared<Graphic>();
  graphic->color = Color(0.0f, 1.0f, 0.0f, 1.0f);
  
  file_view = make_shared<ViewFile>();
  file_view->open_action = [=](const char* path){
    if (graphic->path) free((void*)graphic->path);
    graphic->path = strdup(path);
    graphic->Read();
    for (shared_ptr<Shape> shape : graphic->shapes) {
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
    graphic->Write();
  };

  vertex_table = make_shared<ViewTableShape>();
  vertex_table->height_func = [=](int index) {
    return 32.0f;
  };
  vertex_table->select_action = [=](int i){
    vertex_table->select_index = i;
  };
  vertex_table->edit_action = [=](int i){
    shared_ptr<Shape> shape = graphic->shapes[vertex_table->select_index];
    switch (shape->type) {
      case Shape::TypePoint: {} break;
      case Shape::TypeSegment: {} break;
      case Shape::TypePolygon: {
        shared_ptr<ShapePolygon> type_shape = static_pointer_cast<ShapePolygon>(graphic->shapes[vertex_table->select_index]);
        for (Point vertex : type_shape->vertexes) {
          polygon_table->cell_list.push_back(polygon_table->CreateCell(vertex));
        }
        polygon_table->select_index = 0;
      } break;
      case Shape::TypeCircle: {} break;
    }
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
    RemoveVertex(i);
  };

  polygon_table = make_shared<ViewTablePolygon>();
  polygon_table->height_func = [=](int index) {
    return 32.0f;
  };
  polygon_table->select_action = [=](int i){
    polygon_table->select_index = i;
  };
  polygon_table->edit_action = [=](int i){
    shared_ptr<ShapePolygon> type_shape = static_pointer_cast<ShapePolygon>(graphic->shapes[vertex_table->select_index]);
    type_shape->vertexes[i] = polygon_table->cell_list[i]->point;
  };
  polygon_table->add_action = [=](int i){
    shared_ptr<ShapePolygon> type_shape = static_pointer_cast<ShapePolygon>(graphic->shapes[vertex_table->select_index]);
    Point curr = type_shape->vertexes[i];
    Point next = i+1 < type_shape->vertexes.size() ? type_shape->vertexes[i+1] : type_shape->vertexes[0];
    Point mid = 0.5f * (curr + next);
    InsertVertex(mid, i + 1);
  };
  polygon_table->remove_action = [=](int i){
    RemoveVertex(i);
  };

  Show(); 
}

void WindowVertex::InsertVertex(Point vertex, int index) {
  shared_ptr<ShapePolygon> type_shape = static_pointer_cast<ShapePolygon>(graphic->shapes[vertex_table->select_index]);
  type_shape->vertexes.insert(type_shape->vertexes.begin() + index, vertex);
  polygon_table->cell_list.insert(polygon_table->cell_list.begin() + index, polygon_table->CreateCell(vertex));
  if (index == polygon_table->select_index) polygon_table->select_index++;
}

void WindowVertex::RemoveVertex(int index) {
  shared_ptr<ShapePolygon> type_shape = static_pointer_cast<ShapePolygon>(graphic->shapes[polygon_table->select_index]);
  type_shape->vertexes.erase(type_shape->vertexes.begin() + index);
  polygon_table->cell_list.erase(polygon_table->cell_list.begin() + index);
}

void WindowVertex::OnUpdateSize(int width, int height) {
  pos = ImVec2(width - 330.0f, 0.0f);
  size = ImVec2(330.0f, height);
  content_pos = ImVec2();
  content_size = size;

  float margin = 5.0f;
  file_view->pos = ImVec2(margin, margin);
  file_view->size = ImVec2(content_size.x - margin * 2.0f, 40.0f);
  vertex_table->pos = ImVec2(margin, margin + 40.0f);
  vertex_table->size = ImVec2(content_size.x - margin * 2.0f, 100.0f);
  polygon_table->pos = ImVec2(margin, margin + 40.0f + 100.0f);
  polygon_table->size = ImVec2(content_size.x - margin * 2.0f, content_size.y - 40.0f - 100.0f - margin * 2.0f);
}

void WindowVertex::OnDisplay() {
  Window::Begin(true);
  {
    file_view->Display();
    ImGui::Separator();
    vertex_table->Display();
    ImGui::Separator();
    polygon_table->Display();
  }
  Window::End();
}
} // namespace tkgpg
} // namespace tkht
