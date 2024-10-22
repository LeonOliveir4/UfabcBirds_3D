#include "window.hpp"
#include <abcgOpenGL.hpp>

void Window::onCreate() {
  // Inicializar qualquer configuração gráfica básica
  abcg::glClearColor(0.53f, 0.81f, 0.92f, 1.0f);  // Azul claro
}

void Window::onPaintUI() {
  // Limpar a tela com a cor de fundo definida
  abcg::glClear(GL_COLOR_BUFFER_BIT);
  abcg::OpenGLWindow::onPaintUI();  // Certifica-se de que o FPS está sendo desenhado

  /*// Desenhar nuvens na tela
  drawCloud(-0.5f, 0.5f);  // Nuvem à esquerda
  drawCloud(0.2f, 0.6f);   // Nuvem ao centro
  drawCloud(0.6f, 0.4f);   // Nuvem à direita
  */
}

void Window::onResize(glm::ivec2 const &size) {
  abcg::glViewport(0, 0, size.x, size.y);  // Ajustar a viewport ao redimensionar a janela
}
