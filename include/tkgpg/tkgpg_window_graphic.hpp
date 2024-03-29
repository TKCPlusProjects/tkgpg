#ifndef tkgpg_window_graphic_hpp
#define tkgpg_window_graphic_hpp

#include <tkgpg/tkgpg_base.hpp>
#include <tkgpg/tkgpg_view_file.hpp>
#include <tkgpg/tkgpg_view_shape.hpp>
#include <tkgpg/tkgpg_view_polygon.hpp>

namespace tkht {
namespace tkgpg {
class WindowGraphic : public Window {
public:  
  shared_ptr<ViewFile> file_view;
  shared_ptr<ViewTableShape> shape_table;
  shared_ptr<ViewTablePolygon> polygon_table;

  WindowGraphic();
    
  void OnUpdateSize(int width, int height) override;
  void OnDisplay() override;
};
} // namespace tkgpg
} // namespace tkht

#endif /* tkgpg_window_graphic_hpp */
