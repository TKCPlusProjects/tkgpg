#include <tkbox/tkbox.hpp>
#include <tkgm/tkgm.hpp>
#include <tkgui/tkgui.hpp>
#include <tkgpg/tkgpg.hpp>
#include <tkcore/tkcore.hpp>

using namespace std;
using namespace tkht;

int main(int argc, char *argv[]) {
  filesystem::path root_path = filesystem::absolute(argv[0]).parent_path();
  filesystem::path font_path = root_path.append("fonts/Cubic.ttf");

  tkht::Debug = true;
  tkht::SubscribeSignalCrash();

  tkgpg::Init();
  SetFont(font_path.string().c_str(),
                  map<FontType, float>({
                      {FontType_Title, 50.0f},
                      {FontType_Button, 20.0f},
                      {FontType_Text, 20.0f},
                  }));
  tkgpg::Display();
  tkgpg::Exit();

  return 0;
}