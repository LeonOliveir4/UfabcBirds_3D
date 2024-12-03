#ifndef MODEL2_CUBE_
#define MODEL2_CUBE_


#include "abcgOpenGL.hpp"
#include "model.hpp" 

class Model2: public Model{
protected:
    void create(GLuint program) override;
};
#endif