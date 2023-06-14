#ifndef tkgpg_scene_editor_hpp
#define tkgpg_scene_editor_hpp

#include <tkgpg/tkgpg_base.hpp>
#include <tkgpg/tkgpg_window_graphic.hpp>

namespace tkht {
namespace tkgpg {
class SceneEditor : public Scene {
public:
  shared_ptr<Camera> camera;
  shared_ptr<tkbox::Drawer> drawer;

  shared_ptr<WindowGraphic> graphic_window;

  bool editing = false;
  
  SceneEditor();

  void KeyPressed();
  void KeyDown();
  void KeyReleased();
  
  void OnUpdateSize(int width, int height) override;
  void OnDisplay() override;
};
} // namespace tkgpg
} // namespace tkht

#endif /* tkgpg_scene_editor_hpp */
