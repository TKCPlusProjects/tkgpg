#ifndef tkgpg_scene_editor_hpp
#define tkgpg_scene_editor_hpp

#include <tkgpg/tkgpg_base.hpp>
#include <tkgpg/tkgpg_window_vertex.hpp>

namespace tkht {
namespace tkgpg {
class SceneEditor : public tkgui::Scene {
public:
  shared_ptr<WindowVertex> window_vertex;

  shared_ptr<tkbox::Drawer> drawer;
  shared_ptr<b2World> world;
  shared_ptr<Graphic> canvas;

  bool editing = false;
  
  SceneEditor();
  
  void OnUpdateSize(int width, int height) override;
  void OnDisplay() override;
};
} // namespace tkgpg
} // namespace tkht

#endif /* tkgpg_scene_editor_hpp */
