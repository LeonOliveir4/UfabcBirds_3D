    std::array vertices{
      // Ship body
      glm::vec2{0.43f,0.f}, //0 C
      glm::vec2{0.76f,0.f}, // 1 D
      glm::vec2{0.44f,0.11f}, //2 e
      glm::vec2{0.8f,0.06f}, //3 F
      glm::vec2{0.9f,0.f}, //4 G
      glm::vec2{0.96f,-0.15f},  //5 H
      glm::vec2{0.42f,-0.08f},  //6 I
      glm::vec2{0.5f,-0.08f}, //7 J
      glm::vec2{0.82f,-0.11f}, //8 K
      glm::vec2{-0.12f,-0.18f}, //9 L
      glm::vec2{0.08f,-0.07f},  // 10 M
      glm::vec2{0.31f,0.01f},  // 11 N
      glm::vec2{0.34f,0.17f},  //12 0
      glm::vec2{-0.39f,0.01f},  //13 P
      glm::vec2{-0.29f,-0.17f}, //14 Q
      glm::vec2{-0.52f,-0.07f},  //15 R
      glm::vec2{-0.85f,-0.15f}, //16 S
      glm::vec2{-0.95f,-0.02f},  //17 T
      glm::vec2{0.01f,0.01f},  // 18 U
      glm::vec2{-0.08f,0.23f},  //19 V
      glm::vec2{-0.51f,0.19f},  //20 W
      glm::vec2{-0.52f,0.44f},  //21  Z
      glm::vec2{-0.06,0.61f} //22 Z2
    };  


    std::array const indices{
                          //bico
                          0, 1, 2, //cde
                          2, 3, 1, //efd
                          3, 4, 1, //fgd
                          4, 5, 1, //ghd
                          8, 5, 1, //khd
                          7, 8, 1, //jkd
                          0, 1, 7, //cdj
                          0, 6, 7,
                          //corpo
                          6, 2, 11,
                          11, 10, 6,
                          6, 9, 10,
                          2, 12, 11,
                          12, 11, 10,
                          12, 13, 10,
                          13, 9, 10,
                          13, 9, 14,
                          13, 15, 14,
                          17, 13, 15,
                          15, 16, 16,
                          //asa
                          18, 19, 13, // uvp
                          20, 13, 19, //wpv 
                          20, 19, 22, //wvz2
                          20, 21, 22 //cij

                          }; 
