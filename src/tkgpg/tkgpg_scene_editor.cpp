#include <tkgpg/tkgpg_scene_editor.hpp>

namespace tkht {
namespace tkgpg {
SceneEditor::SceneEditor() : Scene() {
  camera = make_shared<Camera>(25.0f);
  camera->SetZoom(0.5f);
  
  drawer = make_shared<tkbox::Drawer>(camera, 0.0f);

  graphic_window = make_shared<WindowGraphic>();
  AddWindow(graphic_window);
}

void SceneEditor::OnUpdateSize(int width, int height) {
  camera->SetSize(width, height);
  Point offset((width - 330.0f) / 2.0f, height / 2.0f);
  camera->ConvertScreenToWorld(&offset);
  camera->SetCenter(-offset.x, offset.y);
}

void SceneEditor::KeyPressed() {
  if (!editing && ImGui::IsKeyPressed(ImGuiKey_MouseLeft)) {
    ImVec2 mouse_pos = ImGui::GetMousePos();
    
    for (int i = 0; i < BaseGraphic->shapes.size(); i++) {
      shared_ptr<Shape> shape = BaseGraphic->shapes[i];
      switch (shape->type) {
      case Shape::TypePoint: {} break;
      case Shape::TypeSegment: {} break;
      case Shape::TypePolygon: {
        shared_ptr<ShapePolygon> type_shape = static_pointer_cast<ShapePolygon>(shape);
        for (int j = 0; j < type_shape->vertexes.size(); j++) {
          Point vertex = type_shape->vertexes[j];
          camera->ConvertWorldToScreen(&vertex);
          
          if (abs(mouse_pos.x - vertex.x) < 5 && abs(mouse_pos.y - vertex.y) < 5) {
            EditingShapeIndex = i;
            EditingVertexIndex = j;
            ShapeChange(EditingShapeIndex, EditingVertexIndex);
            editing = true; return;
          }
        }
      } break;
      case Shape::TypeCircle: {} break;
      }
    }
  }
}
void SceneEditor::KeyDown() {
  if (editing && ImGui::IsKeyDown(ImGuiKey_MouseLeft)) {
    ImVec2 mouse_pos = ImGui::GetMousePos();
    camera->ConvertScreenToWorld((Point*)&mouse_pos);
    
    ShapePolygonUpdate(EditingShapeIndex, EditingVertexIndex, (Point*)&mouse_pos);
  }
}
void SceneEditor::KeyReleased() {
  if (editing && ImGui::IsKeyReleased(ImGuiKey_MouseLeft)) {
    editing = false;
  }
}

void SceneEditor::OnDisplay() {
  drawer->DrawGraphic(CanvasGraphic.get());
  drawer->DrawGraphic(BaseGraphic.get());
  drawer->DrawGraphic(EditingVertexesGraphic.get());
  drawer->DrawGraphic(EditingVertexGraphic.get());

  KeyPressed();
  KeyDown();
  KeyReleased();

  drawer->Flush();
}
} // namespace tkgpg
} // namespace tkht
