#include <tkgpg/tkgpg_scene_editor.hpp>

namespace tkht {
namespace tkgpg {
SceneEditor::SceneEditor() : Scene() {
  drawer = make_shared<tkbox::Drawer>();
  drawer->camera->SetZoom(0.5f);

  world = make_shared<b2World>(b2Vec2(0.0f, 0.0f));
  world->SetSubStepping(true);
  world->SetDebugDraw(drawer.get());

  canvas = make_shared<Graphic>();
  canvas->color = b2Color(0.6f, 0.6f, 0.6f, 1.0f);
  for (int i = -10; i <= 10; i++) {
    int symbol = i % 2 == 0 ? 1 : -1;
    canvas->vertexes.push_back(b2Vec2(symbol * -10.0f, i));
    canvas->vertexes.push_back(b2Vec2(symbol *  10.0f, i));
  }
  for (int i = -10; i <= 10; i++) {
    int symbol = i % 2 == 0 ? 1 : -1;
    canvas->vertexes.push_back(b2Vec2(i, symbol *  10.0f));
    canvas->vertexes.push_back(b2Vec2(i, symbol * -10.0f));
  }

  window_vertex = make_shared<WindowVertex>();
  AddWindow(window_vertex);
}

void SceneEditor::OnUpdateSize(int width, int height) {
  Scene::OnUpdateSize(width, height);
  drawer->SetSize(width, height);
}

void SceneEditor::OnDisplay() {
  world->Step(1.0f / tkgm::video->hertz->Get(),
  tkgm::video->velocity_iterations->Get(),
  tkgm::video->position_iterations->Get());
  world->DebugDraw();
  
  drawer->Draw(canvas.get());
  drawer->point->Push(5.0f, b2Vec2(), b2Color(1.0f, 1.0f, 1.0f, 1.0f));

  if (window_vertex->graphic->vertexes.size() > 0) {
    drawer->Draw(window_vertex->graphic.get());

    for (size_t i = 0; i < window_vertex->graphic->vertexes.size(); i++) {
      b2Vec2 vertex = window_vertex->graphic->vertexes[i];
      if (i == window_vertex->vertex_table->select_index) {
        drawer->point->Push(10.0f, vertex, b2Color(1.0f, 0.0f, 0.0f, 1.0f));
      } else {
        drawer->point->Push(10.0f, vertex, b2Color(0.0f, 1.0f, 0.0f, 1.0f));
      }
    }
    
    if (ImGui::IsKeyPressed(ImGuiKey_MouseLeft)) {
      ImVec2 mouse_pos = ImGui::GetMousePos();
      for (size_t i = 0; i < window_vertex->graphic->vertexes.size(); i++) {
        b2Vec2 vertex = window_vertex->graphic->vertexes[i];
        drawer->camera->ConvertWorldToScreen(&vertex.x, &vertex.y, vertex.x, vertex.y);

        if (abs(mouse_pos.x - vertex.x) < 5 && abs(mouse_pos.y - vertex.y) < 5) {
          window_vertex->vertex_table->select_index = i;
          editing = true;
          break;
        }
      }
    }
    if (ImGui::IsKeyDown(ImGuiKey_MouseLeft) && editing) {
      ImVec2 mouse_pos = ImGui::GetMousePos();
      drawer->camera->ConvertScreenToWorld(&mouse_pos.x, &mouse_pos.y, mouse_pos.x, mouse_pos.y);

      int select_index = window_vertex->vertex_table->select_index;
      window_vertex->graphic->vertexes[select_index] = b2Vec2(mouse_pos.x, mouse_pos.y);
      window_vertex->vertex_table->cell_list[select_index]->point = b2Vec2(mouse_pos.x, mouse_pos.y);
    }
    if (ImGui::IsKeyReleased(ImGuiKey_MouseLeft)) {
      editing = false;
    }
  }

  drawer->Flush();
}
} // namespace tkgpg
} // namespace tkht
