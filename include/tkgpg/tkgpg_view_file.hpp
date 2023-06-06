#ifndef tkgpg_view_file_hpp
#define tkgpg_view_file_hpp

#include <tkgpg/tkgpg_base.hpp>

namespace tkht {
namespace tkgpg {
class ViewFile : public View {
public:
  char* name;
  function<void(const char*)> open_action;
  function<void()> save_action;

  void OnDisplay() override;
};
} // namespace tkgpg
} // namespace tkht

#endif /* tkgpg_view_file_hpp */
