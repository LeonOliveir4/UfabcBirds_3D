<div>
<h1>UfabcBirds 3D - Relatório do Projeto</h1>
<img src="cdace589-9c7e-4f97-81d4-d0c13c92c76e.jpg" alt="Imagem do projeto">
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
  - Controle de pássaros com teclas de movimentação e rotação (`W`, `A`, `S`, `D`, `Q`, `E`).
  - Gerenciamento de colisões, incluindo limites do cenário e colisões com o solo.
  - Exibição de estado `gameOver` e reinício com tecla `ESPAÇO`.
  - Textos explicativos com informações sobre as aves.
- **Estados do jogo**:
  - **`playing`**: Estado principal, onde o jogador interage com o ambiente 3D.
  - **`gameOver`**: Estado de término, ativado ao alcançar uma condição específica no jogo (ex.: limite do terreno ou colisão com o solo).
- **Educação**:
  - Informações sobre as aves aparecem como um popup no jogo, promovendo conhecimento.
  - Representação inicial do **tucano**, com planos para expandir para outras espécies, como o papagaio.

---

## Estrutura do Projeto
### Arquivos principais:
- **Código-Fonte**:
  - `animation.cpp` e `animation.hpp`: Controlam animações específicas de elementos no jogo.
  - `bird.cpp` e `bird.hpp`: Implementação dos pássaros jogáveis, incluindo reset, movimentação e lógica de colisão.
  - `camera.cpp` e `camera.hpp`: Classe responsável pela projeção e movimentação da câmera.
  - `gamedata.cpp` e `gamedata.hpp`: Gerenciamento de estados e dados do jogo.
  - `window.cpp` e `window.hpp`: Controle do ciclo de vida da aplicação, eventos do usuário, lógica de renderização e gerenciamento de estados.
  - `modelObj.cpp` e `modelObj.hpp`: Carregamento e manipulação de modelos OBJ.
  - `ground.cpp` e `ground.hpp`: Gerenciamento do cenário do chão.
  - `main.cpp`: Entrada principal do programa.

- **Assets**:
  - **Modelos para cada pássaro**:
    - `asa_direita.obj`, `asa_direita.mtl`: Modelo e material da asa direita.
    - `asa_esquerda.obj`, `asa_esquerda.mtl`: Modelo e material da asa esquerda.
    - `bico.obj`: Modelo do bico.
    - `corpo.obj`, `corpo.mtl`: Modelo e material do corpo.
    - `rabo.obj`: Modelo do rabo.
  - **Shaders**:
    - `model.vert`: Vertex shader para renderização de objetos.
    - `model.frag`: Fragment shader para renderização de objetos.

---

## Adições Recentes
- Implementação de popups educativos:
  - Exibição de mensagens informativas no início do jogo, relacionadas ao pássaro selecionado.
  - Textos são exibidos gradualmente, com a opção de alterar a velocidade de exibição.
- Correções de colisões:
  - A lógica foi aprimorada para detectar corretamente colisões laterais e frontais dos pássaros com o chão.
- Movimentação e câmera:
  - A câmera foi ajustada para seguir suavemente o pássaro.
  - Limites do terreno foram corrigidos para refletir o tamanho real do cenário.
- Novo sistema de reset:
  - Reseta o estado e posicionamento dos pássaros corretamente após o estado `gameOver`.

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
