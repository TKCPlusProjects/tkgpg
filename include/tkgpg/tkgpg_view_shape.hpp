#ifndef tkgpg_view_shape_hpp
#define tkgpg_view_shape_hpp

#include <tkgpg/tkgpg_base.hpp>

namespace tkht {
namespace tkgpg {
class ViewTableShapeCell;
class ViewTableShape;

class ViewTableShapeCell : public ViewTableCell<ViewTableShape> {
public:
  const char* text;

  shared_ptr<Popup> popup;

  ViewTableShapeCell();
  void OnDisplay() override;
};
class ViewTableShape : public ViewTable<ViewTableShape, ViewTableShapeCell> {
public:
  int select_index;
  function<void(int)> select_action;
  function<void(int)> edit_action;
  function<void(int, Shape::Type)> add_action;
  function<void(int)> remove_action;

  shared_ptr<ViewTableShapeCell> CreateCell(const char* text);
  void OnDisplay() override;
};
} // namespace tkgpg
} // namespace tkht

#endif /* tkgpg_view_shape_hpp */
