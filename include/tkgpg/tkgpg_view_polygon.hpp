#ifndef tkgpg_view_polygon_hpp
#define tkgpg_view_polygon_hpp

#include <tkgpg/tkgpg_base.hpp>

namespace tkht {
namespace tkgpg {
class ViewTablePolygonCell;
class ViewTablePolygon;

class ViewTablePolygonCell : public ViewTableCell<ViewTablePolygon> {
public:
  Point point;

  void OnDisplay() override;
};
class ViewTablePolygon : public ViewTable<ViewTablePolygon, ViewTablePolygonCell> {
public:
  int select_index;
  function<void(int)> select_action;
  function<void(int)> edit_action;
  function<void(int)> add_action;
  function<void(int)> remove_action;

  shared_ptr<ViewTablePolygonCell> CreateCell(Point point);
  void OnDisplay() override;
};
} // namespace tkgpg
} // namespace tkht

#endif /* tkgpg_view_polygon_hpp */
