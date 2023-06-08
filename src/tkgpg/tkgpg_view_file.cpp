#include <tkgpg/tkgpg_view_file.hpp>
#include <nfd.h>

namespace tkht {
namespace tkgpg {
void ViewFile::OnDisplay() {
  ImGui::PushFont(Font(FontType_Button));
  {
    if (ImGui::Button(name ? name : "Open", ImVec2(250.0f, 30.0f))) {
      nfdchar_t *path = nullptr;
      nfdresult_t result = NFD_OpenDialog(nullptr, nullptr, &path);

      if ( result == NFD_OKAY ) {
        if (name) free(name);
        name = strdup(filesystem::path(path).filename().c_str());
        open_action(path);
        free(path);
      } else if ( result == NFD_CANCEL ) {
        Msg("User pressed cancel.");
      } else {
        Err("Error: %s", NFD_GetError());
      }
    }
    ImGui::SameLine(ImGui::GetCursorPosX(), 10.0f);
    if (ImGui::Button("Save", ImVec2(60.0f, 30.0f))) {
      save_action();
    }
  }
  ImGui::PopFont();
}
} // namespace tkgpg
} // namespace tkht
