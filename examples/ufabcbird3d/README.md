<div>
<h1>UfabcBirds 3D - Relatório do Projeto</h1>
<img src="" alt="Imagem do projeto">
</div>

## Disciplina
**Computação Gráfica**  
**Professor**: Celso Setsuo Kurashima  
**Período**: 2024.3  

---

## Desenvolvedores
- Leonardo Pires de Oliveira - 11201920744  
- Leopoldo Kenji Sugata Naves - 11201722022  

---

## Descrição do Projeto
O **UfabcBirds3D** é um projeto desenvolvido como parte da disciplina de Computação Gráfica, que implementa uma aplicação com gráficos 3D utilizando **OpenGL** e a biblioteca **ABCg**. O projeto inclui transformações geométricas para manipulação e animação de objetos 3D, bem como a gestão de estados do jogo, como `gameOver` e `playing`.

Além do aspecto técnico, o projeto tem um caráter educativo, destacando a fauna e a flora brasileiras. Os jogadores poderão controlar espécies de pássaros brasileiros, como o tucano, e interagir com frutas características da flora nacional, promovendo conscientização ambiental e cultural.

### Objetivos do Projeto:
1. **Renderização de gráficos 3D**: Criação de modelos tridimensionais e renderização no espaço 3D.
2. **Transformações geométricas**: Implementação de translações, rotações e escalas nos objetos.
3. **Animações**: Manipulação contínua de objetos e câmera para criar uma experiência dinâmica.
4. **Jogabilidade**:
   - Controle de pássaros 3D que coletam frutas espalhadas pelo cenário.
   - Disponibilidade de pelo menos **duas espécies jogáveis de pássaros brasileiros**.
   - Inclusão futura de frutas representativas da flora brasileira.
5. **Estados do jogo**: Inclusão de `gameOver` e `playing`, controlando o fluxo da aplicação.
6. **Educação**: 
   - Promover conhecimento sobre a biodiversidade brasileira, com destaque inicial para o **tucano**.
   - Criar uma experiência interativa que incentive o aprendizado sobre espécies de aves e frutas brasileiras.

---

## Funcionalidades
- **Gráficos 3D**: Representação visual de modelos tridimensionais, como aves brasileiras.
- **Transformações geométricas**:
  - Controle de posição (translação), escala e rotação dos objetos em tempo real.
  - Movimentação da câmera no ambiente tridimensional.
- **Animação**: Alteração contínua das propriedades dos objetos para criar movimento.
- **Jogabilidade**:
  - Coleta de frutas pelo chão, contabilizando a pontuação do jogador.
  - Escolha entre duas espécies de pássaros brasileiros, cada uma com animações e características específicas.
- **Estados do jogo**:
  - **`playing`**: Estado principal, onde o jogador interage com o ambiente 3D para coletar frutas.
  - **`gameOver`**: Estado de término, ativado ao alcançar uma condição específica no jogo (ex.: limite de tempo ou colisão).
- **Educação**:
  - Representação do **tucano** como exemplo de ave brasileira.
  - Planejamento para adicionar frutas nativas, como o açaí e a jabuticaba, para enriquecer o cenário e promover o aprendizado.

---

## Estrutura do Projeto
### Arquivos principais:
- **Código-Fonte**:
  - `animation.cpp` e `animation.hpp`: Controlam animações específicas de elementos no jogo.
  - `cena.cpp` e `cena.hpp`: Gerenciamento e renderização do cenário.
  - `fruta.cpp` e `fruta.hpp`: Implementação das frutas que os pássaros coletam.
  - `gamedata.cpp` e `gamedata.hpp`: Gerenciamento de estados e dados do jogo.
  - `camera.hpp` e `camera.cpp`: Classe responsável pela projeção e movimentação da câmera.
  - `model.hpp` e `model.cpp`: Base para a criação de modelos com suporte a translação, rotação e escala.
  - `modelObj.hpp` e `modelObj.cpp`: Carregamento e manipulação de modelos OBJ.
<<<<<<< HEAD
  - `window.hpp` e `window.cpp`: Controle do ciclo de vida da aplicação, eventos do usuário, lógica de renderização e gerenciamento de estados.

- **Assets**:
  - **Modelos para cada passaro**:
    - `asa_direita.obj`, `asa_direita.mtl`: Modelo e material da asa direita.
    - `asa_esquerda.obj`, `asa_esquerda.mtl`: Modelo e material da asa esquerda.
    - `bico.obj`: Modelo do bico.
    - `corpo.obj`, `corpo.mtl`: Modelo e material do corpo.
    - `rabo.obj`: Modelo do rabo.
  - **Shaders**:
    - `model.vert`: Vertex shader para renderização de objetos.
    - `model.frag`: Fragment shader para renderização de objetos.
=======
- **Cenário**:
  - `ground.hpp` e `ground.cpp`: Renderização de um solo base no plano XZ.
- **Interface gráfica**:
  - `window.hpp` e `window.cpp`: Controle do ciclo de vida da aplicação, eventos do usuário, lógica de renderização e gerenciamento de estados.
- Diretório `assets/`:
  - `tucano/`: Modelo de pássaro utilizado no projeto.
  - `arara/`: Modelo de pássaro utilizado no projeto.
  - `model.vert` e `model.frag`: Shaders para renderização de objetos.
>>>>>>> e84fbf9 (camera)

---

## Como Executar o Projeto
1. Clone este repositório:
   ```bash
   git clone https://github.com/LeonOliveir4/UfabcBirds_3D.git

2. Rodar o código:
   ```bash
   ./build.sh (Linux) ou build.bat (Windows)

3. Executar o jogo:
   ```bash
   ./build/bin/ufabcbird3d/ufabcbird3d
