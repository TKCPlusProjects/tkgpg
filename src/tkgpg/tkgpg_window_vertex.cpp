#include <tkgpg/tkgpg_window_vertex.hpp>

namespace tkht {
namespace tkgpg {
WindowVertex::WindowVertex() : Window("TKGPG_WINDOW_VERTEX") {
  vertex_table = make_shared<ViewTableVertex>();
  vertex_table->height_func = [=](int index) {
    return 32.0f;
  };
  vertex_table->select_action = [=](int i){
    vertex_table->select_index = i;
  };
  vertex_table->add_action = [=](int i){
    b2Vec2 curr = vertex_lst[i];
    b2Vec2 next = i+1 < vertex_lst.size() ? vertex_lst[i+1] : vertex_lst[0];
    b2Vec2 mid = 0.5f * (curr + next);
    InsertVertex(mid, i + 1);
  };
  vertex_table->remove_action = [=](int i){
    RemoveVertex(i);
  };
  
  InsertVertex(b2Vec2(-1.0f, -1.0f));
  InsertVertex(b2Vec2( 1.0f, -1.0f));
  InsertVertex(b2Vec2( 1.0f,  1.0f));
  InsertVertex(b2Vec2(-1.0f,  1.0f));

  Show(); 
}

void WindowVertex::InsertVertex(b2Vec2 vertex, int index) {
  vertex_lst.insert(vertex_lst.begin() + index, vertex);
  vertex_table->cell_list.insert(vertex_table->cell_list.begin() + index, vertex_table->CreateCell(vertex));
}

void WindowVertex::RemoveVertex(int index) {
  vertex_lst.erase(vertex_lst.begin() + index);
  vertex_table->cell_list.erase(vertex_table->cell_list.begin() + index);
}

void WindowVertex::OnUpdateSize(int width, int height) {
  pos = ImVec2(width * 0.7f, 0.0f);
  size = ImVec2(width * 0.3f, height);
  content_pos = ImVec2();
  content_size = size;

  float margin = 5.0f;
  vertex_table->pos = ImVec2(margin, margin);
  vertex_table->size = ImVec2(content_size.x - margin * 2.0f, content_size.y - margin * 2.0f);
}

void WindowVertex::OnDisplay() {
  Window::Begin(true);
  {
    vertex_table->Display();
  }
  Window::End();
}
} // namespace tkgpg
} // namespace tkht
