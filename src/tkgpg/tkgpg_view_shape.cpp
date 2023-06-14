#include <tkgpg/tkgpg_view_shape.hpp>

namespace tkht {
namespace tkgpg {
ViewTableShapeCell::ViewTableShapeCell() : ViewTableCell() {
  popup = make_shared<Popup>(vector<shared_ptr<MenuItem>>{
    make_shared<MenuItem>("Edit", [=](){ 
      SetTableAction([=](auto table){ table->edit_action(index); });
    }),
    make_shared<MenuItem>("Add", vector<shared_ptr<MenuItem>>{
      make_shared<MenuItem>("Point", [=](){ 
        SetTableAction([=](auto table){ table->add_action(index, Shape::TypePoint); });
      }),
      make_shared<MenuItem>("Segment", [=](){ 
        SetTableAction([=](auto table){ table->add_action(index, Shape::TypeSegment); });
      }),
      make_shared<MenuItem>("Polygon", [=](){ 
        SetTableAction([=](auto table){ table->add_action(index, Shape::TypePolygon); });
      }),
      make_shared<MenuItem>("Circle", [=](){ 
        SetTableAction([=](auto table){ table->add_action(index, Shape::TypeCircle); });
      }),
    }),
    make_shared<MenuItem>("Remove", [=](){ 
      SetTableAction([=](auto table){ table->remove_action(index); });
    }),
  });
}

void ViewTableShapeCell::OnDisplay() {
  ImGui::Separator();
  ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.6f, 0.0f, 0.0f, is_select ? 1.0f : 0.0f));
  char buf[32] = {0};
  sprintf(buf, "%d", index);
  if (ImGui::Button(buf, ImVec2(50.0f, 30.0f))) {
    SetTableAction([=](auto table){ table->select_action(index); });
  }
  ImGui::PopStyleColor(1);
  
  ImGui::SameLine(ImGui::GetCursorPosX(), 5.0f);
  if (ImGui::Button(text, ImVec2(265.0f, 30.0f))) {
    SetTableAction([=](auto table){ table->select_action(index); });
  }
  popup->Pin();

  ImGui::Separator();
}

shared_ptr<ViewTableShapeCell> ViewTableShape::CreateCell(const char* text) {
  shared_ptr<ViewTableShapeCell> cell = ViewTable::CreateCell();
  cell->text = text;
  return cell;
}

void ViewTableShape::OnDisplay() {
  ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
  ImGui::PushFont(Font(FontType_Button));

  ViewTable::OnDisplay();

  ImGui::PopFont();
  ImGui::PopStyleColor(1);
}
} // namespace tkgpg
} // namespace tkht
