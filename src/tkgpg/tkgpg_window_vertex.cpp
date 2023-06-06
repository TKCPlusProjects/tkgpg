#include <tkgpg/tkgpg_window_vertex.hpp>

namespace tkht {
namespace tkgpg {
WindowVertex::WindowVertex() : Window("TKGPG_WINDOW_VERTEX") {
  graphic = make_shared<Graphic>();
  graphic->color = b2Color(0.0f, 1.0f, 0.0f, 1.0f);
  
  file_view = make_shared<ViewFile>();
  file_view->open_action = [=](const char* path){
    if (graphic->path) free((void*)graphic->path);
    graphic->path = strdup(path);
    graphic->Read();
    for (b2Vec2 vertex : graphic->vertexes) {
      vertex_table->cell_list.push_back(vertex_table->CreateCell(vertex));
    }
    vertex_table->select_index = 0;
  };
  file_view->save_action = [=](){
    graphic->Write();
  };

  vertex_table = make_shared<ViewTableVertex>();
  vertex_table->height_func = [=](int index) {
    return 32.0f;
  };
  vertex_table->select_action = [=](int i){
    vertex_table->select_index = i;
  };
  vertex_table->edit_action = [=](int i){
    graphic->vertexes[i] = vertex_table->cell_list[i]->point;
  };
  vertex_table->add_action = [=](int i){
    b2Vec2 curr = graphic->vertexes[i];
    b2Vec2 next = i+1 < graphic->vertexes.size() ? graphic->vertexes[i+1] : graphic->vertexes[0];
    b2Vec2 mid = 0.5f * (curr + next);
    InsertVertex(mid, i + 1);
  };
  vertex_table->remove_action = [=](int i){
    RemoveVertex(i);
  };

  Show(); 
}

void WindowVertex::InsertVertex(b2Vec2 vertex, int index) {
  graphic->vertexes.insert(graphic->vertexes.begin() + index, vertex);
  vertex_table->cell_list.insert(vertex_table->cell_list.begin() + index, vertex_table->CreateCell(vertex));
  if (index == vertex_table->select_index) vertex_table->select_index++;
}

void WindowVertex::RemoveVertex(int index) {
  graphic->vertexes.erase(graphic->vertexes.begin() + index);
  vertex_table->cell_list.erase(vertex_table->cell_list.begin() + index);
}

void WindowVertex::OnUpdateSize(int width, int height) {
  pos = ImVec2(width - 330.0f, 0.0f);
  size = ImVec2(330.0f, height);
  content_pos = ImVec2();
  content_size = size;

  float margin = 5.0f;
  file_view->pos = ImVec2(margin, margin);
  file_view->size = ImVec2(content_size.x - margin * 2.0f, 40.0f);
  vertex_table->pos = ImVec2(margin, margin + 40.0f);
  vertex_table->size = ImVec2(content_size.x - margin * 2.0f, content_size.y - 40.0f - margin * 2.0f);
}

void WindowVertex::OnDisplay() {
  Window::Begin(true);
  {
    file_view->Display();
    vertex_table->Display();
  }
  Window::End();
}
} // namespace tkgpg
} // namespace tkht
