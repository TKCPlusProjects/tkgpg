#include <tkgpg/tkgpg_view_vertex.hpp>

namespace tkht {
namespace tkgpg {
void ViewTableVertexCell::OnDisplay() {
  shared_ptr<ViewTableVertex> table = this->table.lock();

  ImGui::Separator();
  ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.6f, 0.0f, 0.0f, (index == table->select_index) ? 1.0f : 0.0f));
  char buf[32];
  sprintf(buf, "%d", index);
  if (ImGui::Button(buf, ImVec2(50.0f, 30.0f))) {
    table->action = [=](){
      table->select_action(index);
    };
  }
  ImGui::PopStyleColor(1);
  
  ImGui::SameLine(ImGui::GetCursorPosX(), 5.0f);
  ImGui::SetNextItemWidth(100.0f);
  if (ImGui::DragFloat("##coordinate_x", &point.x, 0.01f, 0.0f, 0.0f, "%+.2f")) {
    table->action = [=](){
      table->edit_action(index);
    };
  }
  ImGui::SameLine(ImGui::GetCursorPosX(), 5.0f);
  ImGui::SetNextItemWidth(100.0f);
  if (ImGui::DragFloat("##coordinate_y", &point.y, 0.01f, 0.0f, 0.0f, "%+.2f")) {
    table->action = [=](){
      table->edit_action(index);
    };
  }
  
  ImGui::SameLine();
  if (ImGui::Button("+", ImVec2(30.0f, 30.0f))) {
    table->action = [=](){
      table->add_action(index);
    };
  }
  ImGui::SameLine();
  if (ImGui::Button("-", ImVec2(30.0f, 30.0f))) {
    table->action = [=](){
      table->remove_action(index);
    };
  }

  ImGui::Separator();
}

shared_ptr<ViewTableVertexCell> ViewTableVertex::CreateCell(b2Vec2 point) {
  shared_ptr<ViewTableVertexCell> cell = ViewTable::CreateCell();
  cell->point = point;
  return cell;
}

void ViewTableVertex::OnDisplay() {
  ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
  ImGui::PushFont(Font(FontType_Button));

  ViewTable::OnDisplay();

  ImGui::PopFont();
  ImGui::PopStyleColor(1);
}
} // namespace tkgpg
} // namespace tkht
