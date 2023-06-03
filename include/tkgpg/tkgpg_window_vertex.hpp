#ifndef tkgpg_window_vertex_hpp
#define tkgpg_window_vertex_hpp

#include <tkgpg/tkgpg_base.hpp>
#include <tkgpg/tkgpg_view_vertex.hpp>

namespace tkht {
namespace tkgpg {
class WindowVertex : public tkgui::Window {
public:
  vector<b2Vec2> vertex_lst;
  shared_ptr<ViewTableVertex> vertex_table;

  WindowVertex();

  void InsertVertex(b2Vec2 vertex, int index = 0);
  void RemoveVertex(int index = 0);
  
  void OnUpdateSize(int width, int height) override;
  void OnDisplay() override;
};
} // namespace tkgpg
} // namespace tkht

#endif /* tkgpg_window_vertex_hpp */
