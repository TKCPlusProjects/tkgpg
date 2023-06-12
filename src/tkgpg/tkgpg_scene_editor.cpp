#include <tkgpg/tkgpg_scene_editor.hpp>

namespace tkht {
namespace tkgpg {
SceneEditor::SceneEditor() : Scene() {
  camera = make_shared<Camera>(25.0f);
  camera->SetZoom(0.5f);
  
  drawer = make_shared<tkbox::Drawer>(camera, 0.0f);

  canvas = make_shared<Graphic>();
  canvas->color = Color(0.6f, 0.6f, 0.6f, 1.0f);
  for (int i = -10; i <= 10; i++) {
    int symbol = i % 2 == 0 ? 1 : -1;
    canvas->shapes.push_back(make_shared<ShapeSegment>(Point(symbol * -10.0f, i), Point(symbol *  10.0f, i)));
  }
  for (int i = -10; i <= 10; i++) {
    int symbol = i % 2 == 0 ? 1 : -1;
    canvas->shapes.push_back(make_shared<ShapeSegment>(Point(i, symbol * -10.0f), Point(i, symbol *  10.0f)));
  }
  canvas->shapes.push_back(make_shared<ShapePoint>(5.0f, Point()));

  window_vertex = make_shared<WindowVertex>();
  AddWindow(window_vertex);
}

void SceneEditor::OnUpdateSize(int width, int height) {
  Scene::OnUpdateSize(width, height);

  camera->SetSize(width, height);
  Point offset((width - 330.0f) / 2.0f, height / 2.0f);
  camera->ConvertScreenToWorld(&offset);
  camera->SetCenter(-offset.x, offset.y);
}

void SceneEditor::OnDisplay() {
  drawer->DrawGraphic(canvas.get());
  
  drawer->DrawGraphic(window_vertex->graphic.get());
  for (shared_ptr<Shape> shape : window_vertex->graphic->shapes) {
    switch (shape->type) {
    case Shape::TypePoint: {} break;
    case Shape::TypeSegment: {} break;
    case Shape::TypePolygon: {
      shared_ptr<ShapePolygon> type_shape = static_pointer_cast<ShapePolygon>(shape);
      if (type_shape->vertexes.size() > 0) {
        for (size_t i = 0; i < type_shape->vertexes.size(); i++) {
          Point vertex = type_shape->vertexes[i];
          if (i == window_vertex->polygon_table->select_index) {
            Color color(1.0f, 0.0f, 0.0f, 1.0f);
            drawer->point->Push(10.0f, &vertex, &color);
          } else {
            Color color(0.0f, 1.0f, 0.0f, 1.0f);
            drawer->point->Push(10.0f, &vertex, &color);
          }
        }
        
        if (ImGui::IsKeyPressed(ImGuiKey_MouseLeft)) {
          ImVec2 mouse_pos = ImGui::GetMousePos();
          for (size_t i = 0; i < type_shape->vertexes.size(); i++) {
            Point vertex = type_shape->vertexes[i];
            camera->ConvertWorldToScreen(&vertex);

            if (abs(mouse_pos.x - vertex.x) < 5 && abs(mouse_pos.y - vertex.y) < 5) {
              window_vertex->polygon_table->select_index = i;
              editing = true;
              break;
            }
          }
        }
        if (ImGui::IsKeyDown(ImGuiKey_MouseLeft) && editing) {
          ImVec2 mouse_pos = ImGui::GetMousePos();
          camera->ConvertScreenToWorld((Point*)&mouse_pos);

          int select_index = window_vertex->polygon_table->select_index;
          type_shape->vertexes[select_index] = Point(mouse_pos.x, mouse_pos.y);
          window_vertex->polygon_table->cell_list[select_index]->point = Point(mouse_pos.x, mouse_pos.y);
        }
        if (ImGui::IsKeyReleased(ImGuiKey_MouseLeft)) {
          editing = false;
        }
      }
    } break;
    case Shape::TypeCircle: {} break;
    } 
  }

  drawer->Flush();
}
} // namespace tkgpg
} // namespace tkht
