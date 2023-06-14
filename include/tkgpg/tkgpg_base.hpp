#ifndef tkgpg_base_hpp
#define tkgpg_base_hpp

#include <tkbox/tkbox.hpp>
#include <tkgm/tkgm.hpp>
#include <tkgui/tkgui.hpp>
#include <tkcore/tkcore.hpp>

namespace tkht {
namespace tkgpg {
extern shared_ptr<Graphic> BaseGraphic;

void GraphicOpen(const char* path);
void GraphicSave();

void SetShapeChanged(function<void(int)> callback);
void ShapeChange(int shape_i);
void ShapePolygonInsert(int shape_i, int vertex_i, Point* vertex = nullptr);
void ShapePolygonRemove(int shape_i, int vertex_i);
} // namespace tkgpg
} // namespace tkht

#endif /* tkgpg_base_hpp */
