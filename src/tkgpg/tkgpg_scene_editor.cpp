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

  graphic = make_shared<Graphic>();
  graphic->path = "output.tkgp";
  graphic->color = b2Color(0.0f, 1.0f, 0.0f, 1.0f);
  
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

  graphic->vertexes = window_vertex->vertex_lst;
  drawer->Draw(graphic.get());

  drawer->Flush();
}
} // namespace tkgpg
} // namespace tkht
