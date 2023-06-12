#include <tkgpg/tkgpg_view_shape.hpp>

namespace tkht {
namespace tkgpg {
void ViewTableShapeCell::OnDisplay() {
  shared_ptr<ViewTableShape> table = this->table.lock();

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
  if (ImGui::Button(text, ImVec2(265.0f, 30.0f))) {
    table->action = [=](){
      table->select_action(index);
    };
  }

  ImGuiID menu_id = tkgui::ViewID();
  if (ImGui::IsMouseReleased(ImGuiMouseButton_Right)) {
    ImGui::OpenPopupEx(menu_id, ImGuiPopupFlags_None);
  }
  if (ImGui::BeginPopupEx(menu_id, tkgui::UIFlags | ImGuiWindowFlags_AlwaysAutoResize)) {
    if (ImGui::MenuItem("Edit")) {
      table->action = [=](){
        table->edit_action(index);
      };
    }
    if (ImGui::BeginMenu("Add")) {
      if (ImGui::MenuItem("Point")) {
        table->action = [=](){
          table->add_action(index, Shape::TypePoint);
        };
      }
      if (ImGui::MenuItem("Segment")) {
        table->action = [=](){
          table->add_action(index, Shape::TypeSegment);
        };
      }
      if (ImGui::MenuItem("Polygon")) {
        table->action = [=](){
          table->add_action(index, Shape::TypePolygon);
        };
      }
      if (ImGui::MenuItem("Circle")) {
        table->action = [=](){
          table->add_action(index, Shape::TypeCircle);
        };
      }
      ImGui::EndMenu();
    }
    if (ImGui::MenuItem("Remove")) {
      table->action = [=](){
        table->remove_action(index);
      };
    }
    ImGui::EndPopup();
  }

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
