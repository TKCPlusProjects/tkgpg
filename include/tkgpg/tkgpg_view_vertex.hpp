#ifndef tkgpg_view_vertex_hpp
#define tkgpg_view_vertex_hpp

#include <tkgpg/tkgpg_base.hpp>

namespace tkht {
namespace tkgpg {
class ViewTableVertexCell;
class ViewTableVertex;

class ViewTableVertexCell : public ViewTableCell<ViewTableVertex> {
public:
  b2Vec2 point;

  void OnDisplay() override;
};
class ViewTableVertex : public ViewTable<ViewTableVertex, ViewTableVertexCell> {
public:
  int select_index;
  function<void(int)> select_action;
  function<void(int)> edit_action;
  function<void(int)> add_action;
  function<void(int)> remove_action;

  shared_ptr<ViewTableVertexCell> CreateCell(b2Vec2 point);
  void OnDisplay() override;
};
} // namespace tkgpg
} // namespace tkht

#endif /* tkgpg_view_vertex_hpp */
