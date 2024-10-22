#ifndef WINDOW_HPP_
#define WINDOW_HPP_

#include "abcgOpenGL.hpp"

class Window : public abcg::OpenGLWindow {
protected:
  void onCreate() override;   // Inicialização da janela e configurações
  void onPaintUI() override;    // Apenas desenhar a tela, sem elementos do jogo
  void onResize(glm::ivec2 const &size) override; // Redimensionamento da janela

  /*private:
    void drawCloud(float x, float y);   // Função para desenhar nuvens simples
    */
};

#endif