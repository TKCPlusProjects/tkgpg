#include <tkgpg/tkgpg_scene_editor.hpp>

namespace tkht {
namespace tkgpg {
SceneEditor::SceneEditor() : Scene() {
  drawer = make_shared<tkbox::Drawer>();

  world = make_shared<b2World>(b2Vec2(0.0f, 0.0f));
  world->SetSubStepping(true);
  world->SetDebugDraw(drawer.get());

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
  drawer->Flush();
}
} // namespace tkgpg
} // namespace tkht
