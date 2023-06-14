#include <tkgpg/tkgpg_view_polygon.hpp>

namespace tkht {
namespace tkgpg {
void ViewTablePolygonCell::OnDisplay() {
  shared_ptr<ViewTablePolygon> table = this->table.lock();

  ImGui::Separator();
  ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.6f, 0.0f, 0.0f, (index == table->select_index) ? 1.0f : 0.0f));
  char buf[32] = {0};
  sprintf(buf, "%d", index);
  if (ImGui::Button(buf, ImVec2(50.0f, 30.0f))) {
    SetTableAction([=](auto table){ table->select_action(index); });
  }
  ImGui::PopStyleColor(1);
  
  bool edit = false;
  ImGui::SameLine(ImGui::GetCursorPosX(), 5.0f);
  ImGui::SetNextItemWidth(100.0f);
  edit |= ImGui::DragFloat("##coordinate_x", &point.x, 0.01f, 0.0f, 0.0f, "%+.2f");

  ImGui::SameLine(ImGui::GetCursorPosX(), 5.0f);
  ImGui::SetNextItemWidth(100.0f);
  edit |= ImGui::DragFloat("##coordinate_y", &point.y, 0.01f, 0.0f, 0.0f, "%+.2f");
  
  if (edit) {
    SetTableAction([=](auto table){ 
      table->select_action(index);
      table->edit_action(index);
    });
  }
  
  ImGui::SameLine();
  if (ImGui::Button("+", ImVec2(30.0f, 30.0f))) {
    SetTableAction([=](auto table){ table->add_action(index); });
  }
  ImGui::SameLine();
  if (ImGui::Button("-", ImVec2(30.0f, 30.0f))) {
    SetTableAction([=](auto table){ table->remove_action(index); });
  }

  ImGui::Separator();
}

shared_ptr<ViewTablePolygonCell> ViewTablePolygon::CreateCell(Point point) {
  shared_ptr<ViewTablePolygonCell> cell = ViewTable::CreateCell();
  cell->point = point;
  return cell;
}

void ViewTablePolygon::OnDisplay() {
  ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
  ImGui::PushFont(Font(FontType_Button));

  ViewTable::OnDisplay();

  ImGui::PopFont();
  ImGui::PopStyleColor(1);
}
} // namespace tkgpg
} // namespace tkht
