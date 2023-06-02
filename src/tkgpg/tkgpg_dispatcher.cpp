#include <tkgpg/tkgpg_dispatcher.hpp>

namespace tkht {
namespace tkgpg {
shared_ptr<SceneEditor> editor;

void SetSize() {
  editor->UpdateSize(Width, Height);
}

void GUIErrorfun(int error_code, const char *description) {
  Err("%d - %s", error_code, description);
}

void GUISizeCallback(int width, int height) {
  tkgm::video->window_width->Set(width);
  tkgm::video->window_height->Set(height);
  tkgm::Write();

  SetSize();
}

void Init() {
  tkgm::Load();

  tkgui::Init(tkgm::video->window_width->Get(),
              tkgm::video->window_height->Get(), "tkgpg");

  SetErrorfun(GUIErrorfun);
  SetSizeCallback(GUISizeCallback);

  editor = make_shared<SceneEditor>();

  SetSize();
}

void Display() {
  tkgui::Display([] {
    editor->Display();
  });
}

void Exit() {
  tkgm::Write();
}
} // namespace tkgpg
} // namespace tkht
