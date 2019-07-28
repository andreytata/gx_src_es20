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

gx::vtxa* gx::vtxa::make_new(const int& gl_type_id)
{
    switch (gl_type_id)
    {
    case GL_FLOAT             : return new gx::av1f;  // "float"
    case GL_FLOAT_VEC2        : return new gx::av2f;  // "vec2"
    case GL_FLOAT_VEC3        : return new gx::av3f;  // "vec3"
    case GL_FLOAT_VEC4        : return new gx::av4f;  // "vec4"
    case GL_INT               : return new gx::av1i;  // "int"
    case GL_INT_VEC2          : return new gx::av2i;  // "ivec2"
    case GL_INT_VEC3          : return new gx::av3i;  // "ivec3"
    case GL_INT_VEC4          : return new gx::av4i;  // "ivec4"
    case GL_UNSIGNED_INT      : return new gx::av1u;  // "unsigned int"
    case GL_BOOL              : return new gx::av1b;  // "bool"
    case GL_BOOL_VEC2         : return new gx::av2b;  // "bvec2"
    case GL_BOOL_VEC3         : return new gx::av3b;  // "bvec3"
    case GL_BOOL_VEC4         : return new gx::av4b;  // "bvec4"
    case GL_FLOAT_MAT2        : return new gx::am2f;  // "mat2"
    case GL_FLOAT_MAT3        : return new gx::am3f;  // "mat3"
    case GL_FLOAT_MAT4        : return new gx::am4f;  // "mat4"
    };

    return nullptr;
}

gx::unfa* gx::unfa::make_new(const int& gl_type_id)
{
    switch (gl_type_id)
    {
    case GL_FLOAT             : return new gx::uv1f;  // "float"
    case GL_FLOAT_VEC2        : return new gx::uv2f;  // "vec2"
    case GL_FLOAT_VEC3        : return new gx::uv3f;  // "vec3"
    case GL_FLOAT_VEC4        : return new gx::uv4f;  // "vec4"
    case GL_INT               : return new gx::uv1i;  // "int"
    case GL_INT_VEC2          : return new gx::uv2i;  // "ivec2"
    case GL_INT_VEC3          : return new gx::uv3i;  // "ivec3"
    case GL_INT_VEC4          : return new gx::uv4i;  // "ivec4"
    case GL_UNSIGNED_INT      : return new gx::uv1u;  // "unsigned int"
    case GL_BOOL              : return new gx::uv1b;  // "bool"
    case GL_BOOL_VEC2         : return new gx::uv2b;  // "bvec2"
    case GL_BOOL_VEC3         : return new gx::uv3b;  // "bvec3"
    case GL_BOOL_VEC4         : return new gx::uv4b;  // "bvec4"
    case GL_FLOAT_MAT2        : return new gx::um2f;  // "mat2"
    case GL_FLOAT_MAT3        : return new gx::um3f;  // "mat3"
    case GL_FLOAT_MAT4        : return new gx::um4f;  // "mat4"
    case GL_SAMPLER_2D        : return new gx::tx2d;  // "sampler2D"
    case GL_SAMPLER_CUBE      : return new gx::txcb;  // "samplerCube"
    };

    return nullptr;
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

// EXAMPLE: HOW TO USE VISITORS:
//
//#include <QApplication>
//#include <QLabel>
//#include <QSurfaceFormat>
//#ifndef QT_NO_OPENGL
//#include <gx_src_es20.h>
//#endif
//int main(int argc, char *argv[]) {
//    QApplication app(argc, argv);
//    QSurfaceFormat format;
//    format.setDepthBufferSize(24);
//    QSurfaceFormat::setDefaultFormat(format);
//    app.setApplicationName("TEST VISITORS");
//    app.setApplicationVersion("0.1");
//#ifndef QT_NO_OPENGL
//    gx::root gl_widget;  // can be replaced with gx::gap_generated widget
//    gl_widget.show();
//#else
//    QLabel note("OpenGL Support required");
//    note.show();
//#endif
//    gl_widget.get_prog()->qdebug_active_variables();  // TEST INVOCATOR
//    return app.exec();
// 1. Get program pointer:  get_prog("program name")
//    gx::prog* p_prog = gl_widget.get_prog();
// 2. Print program variables
//    p_prog->qdebug_active_variables();
// 3. Get surface:
//    gx::shgr test;
//    struct test_surf_t : gx::surf
//    {
//    } test_surf;
//    test.mp_prog = p_prog;
//    test.mp_data = &test_surf;  // default variables data
//    add shading group to draw-loop;
//    gl_widget.add_shgr("test", &test);
//    qDebug() << "Activated shading-groups:";
//    for(auto active_shgr: gl_widget.m_shgr_dict) {
//        qDebug() << active_shgr.first.c_str() << (void*)active_shgr.second;
//    }
//    return app.exec();
//}

void gx::root::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    qDebug() << "Activated shading-groups:" << m_shgr_dict.size();

    for(auto view_pair: m_shgr_dict) {
        qDebug() << view_pair.first.c_str() << (void*)view_pair.second;
        gx::shgr* curr = view_pair.second;
        curr->bind();
    }
    qDebug() << "--Activated shading-groups\n";
}
