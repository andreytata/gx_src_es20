#include <gx_src_es20.h>

const char* gx::vtxa::get_glsl_type_name(const int& n)
{
    static std::map<int, const char*> t_name = {
        { GL_FLOAT             , "float"        },
        { GL_FLOAT_VEC2        , "vec2"         },
        { GL_FLOAT_VEC3        , "vec3"         },
        { GL_FLOAT_VEC4        , "vec4"         },
        { GL_INT               , "int"          },
        { GL_INT_VEC2          , "ivec2"        },
        { GL_INT_VEC3          , "ivec3"        },
        { GL_INT_VEC4          , "ivec4"        },
        { GL_UNSIGNED_INT      , "unsigned int" },
        { GL_BOOL              , "bool"         },
        { GL_BOOL_VEC2         , "bvec2"        },
        { GL_BOOL_VEC3         , "bvec3"        },
        { GL_BOOL_VEC4         , "bvec4"        },
        { GL_FLOAT_MAT2        , "mat2"         },
        { GL_FLOAT_MAT3        , "mat3"         },
        { GL_FLOAT_MAT4        , "mat4"         },
    };

    auto exists = t_name.find(n);

    return t_name.end() == exists ? "UNSUPPORTED_ATTRIBUTE_TYPE" : exists->second;
}

const char* gx::unfa::get_glsl_type_name(const int& n)
{
    static std::map<int, const char*> t_name =
    {
        { GL_FLOAT                                     , "float"                },
        { GL_FLOAT_VEC2                                , "vec2"                 },
        { GL_FLOAT_VEC3                                , "vec3"                 },
        { GL_FLOAT_VEC4                                , "vec4"                 },
        { GL_INT                                       , "int"                  },
        { GL_INT_VEC2                                  , "ivec2"                },
        { GL_INT_VEC3                                  , "ivec3"                },
        { GL_INT_VEC4                                  , "ivec4"                },
        { GL_UNSIGNED_INT                              , "unsigned int"         },
        { GL_BOOL                                      , "bool"                 },
        { GL_BOOL_VEC2                                 , "bvec2"                },
        { GL_BOOL_VEC3                                 , "bvec3"                },
        { GL_BOOL_VEC4                                 , "bvec4"                },
        { GL_FLOAT_MAT2                                , "mat2"                 },
        { GL_FLOAT_MAT3                                , "mat3"                 },
        { GL_FLOAT_MAT4                                , "mat4"                 },
        { GL_SAMPLER_2D                                , "sampler2D"            },
        { GL_SAMPLER_CUBE                              , "samplerCube"          },
    };

    auto exists = t_name.find(n);

    return t_name.end() == exists ? "UNSUPPORTED_UNIFORM_TYPE" : exists->second;
}

//gx::root::root(QWidget* parent) : QOpenGLWidget(parent) {}

//gx::root::~root(){}
