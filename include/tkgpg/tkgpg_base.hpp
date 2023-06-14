#ifndef tkgpg_base_hpp
#define tkgpg_base_hpp

#include <tkbox/tkbox.hpp>
#include <tkgm/tkgm.hpp>
#include <tkgui/tkgui.hpp>
#include <tkcore/tkcore.hpp>

namespace tkht {
namespace tkgpg {
typedef function<void(int, int)> TKGPGShapeChangedCallback;

extern shared_ptr<Graphic> BaseGraphic;
extern shared_ptr<Graphic> CanvasGraphic;

extern int EditingShapeIndex;
extern int EditingVertexIndex;
extern shared_ptr<ShapePoint> EditingVertexesShape;
extern shared_ptr<Graphic> EditingVertexesGraphic;
extern shared_ptr<ShapePoint> EditingVertexShape;
extern shared_ptr<Graphic> EditingVertexGraphic;

void GraphicOpen(const char* path);
void GraphicSave();

void SetShapeChanged(TKGPGShapeChangedCallback callback);
void ShapeChange(int shape_i, int vertex_i);
void ShapeInsert(int shape_i, Shape::Type type);
void ShapeRemove(int shape_i);
void ShapePolygonInsert(int shape_i, int vertex_i, Point* vertex = nullptr);
void ShapePolygonUpdate(int shape_i, int vertex_i, Point* vertex);
void ShapePolygonRemove(int shape_i, int vertex_i);
} // namespace tkgpg
} // namespace tkht

#endif /* tkgpg_base_hpp */
