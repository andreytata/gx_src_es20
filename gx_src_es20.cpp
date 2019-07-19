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

gx::prog::some_state* gx::prog::get_init_state()
{
    static struct : some_state
    {
        void set_current(prog* p)
        {
            initializeOpenGLFunctions();
            qDebug() << "!!!!!!!!!!!!";

            if (!p->program.addShaderFromSourceFile(
                        QOpenGLShader::Vertex, ":/vshader.glsl"))
            {
                p->current_state = p->get_fail_state();
                qDebug() << "BAD VERTEX SHADER CODE?";
                return;
            }

            qDebug() << "VSHADER_ADDED_FROM_CODE";

            // Compile fragment shader
            if (!p->program.addShaderFromSourceFile(
                        QOpenGLShader::Fragment, ":/fshader.glsl"))
            {
                qDebug() << "BAD FRAGMENT SHADER CODE?";
                p->current_state = p->get_fail_state();
                return;
            }
            qDebug() << "FSHADER_ADDED_FROM_CODE";


            // Link shader pipeline
            if (!p->program.link())
            {
                p->current_state = p->get_fail_state();
                return;
            }
            qDebug() << "GLSL SHADER PROGRAM LINKED";

            // Bind shader pipeline for use
            if (!p->program.bind())
            {
                p->current_state = p->get_fail_state();
                return;
            }

            qDebug() << "program max geom output vertices => " << p->program.maxGeometryOutputVertices();

            GLuint program_id = p->program.programId();

            qDebug() << "program.programId() => " << program_id;

            GLint i;                    // var's id
            GLint count;                // active vars count
            GLint size;                 // size of the variable

            GLenum type;                // type of the variable (float, vec3 or mat4, etc)

            const GLsizei bufSize = 1024; // maximum name length
            GLchar name[bufSize];         // variable GLSL name
            GLsizei length;               // variable name length

            glGetProgramiv(program_id, GL_ACTIVE_ATTRIBUTES, &count);

            qDebug() << "Active Attributes:" << count;

            for (i = 0; i < count; i++)
            {
                glGetActiveAttrib(program_id, (GLuint)i, bufSize, &length, &size, &type, name);
                // WHAT THE HELL WE DOING HERE? Collect ACTIVE vertex attributes
                // WHY WE MUST DOING SOMETHING LIKE THIS? Some attributes declared at GLSL
                // shader code, maybe not ACTIVE! This depend both used GPU, and OpenGL
                // driver version. So:
                vtxa* attr = gx::vtxa::make_new(type);
                attr->set_prog_indx(i);
                attr->set_prog_size(size);
                p->program_active_attributes[name] = attr;
                printf ( "ATTRIBUTE #%d Type: '%s' Name: '%s' Size: %d\n", attr->get_prog_indx()
                         , vtxa::get_glsl_type_name(attr->get_glsl_type_id())
                         , name
                         , attr->get_prog_size()
                       );
            }

            glGetProgramiv(program_id, GL_ACTIVE_UNIFORMS, &count);

            qDebug() << "Active Uniforms:" << count;

            for (i = 0; i < count; i++)
            {
                // WHAT THE HELL WE DOING HERE? Collect ACTIVE UNIFORMS
                // Все значения таких переменных будут замещаться на реальные значения в два этапа
                // - первый - интроспекция, результаты которой нужно сохранить на всё время работы
                //   слинкованной программы. Имя, тип, размер, и индекс каждого атрибута неизменны
                //   до конца работы данной программы. Попытки изменить исходный код шейдеров, как
                //   и попытки скомпилировать/слинковать программу полностью игнорируются.
                // - второй - линковка с инстанцией шейдинг-группы. В результате "линковки" каждой
                //   активной uniform переменной будет поставлен в соответствие источник данных.
                glGetActiveUniform(program_id, (GLuint)i, bufSize, &length, &size, &type, name);
                unfa* attr = gx::unfa::make_new(type);
                attr->set_prog_indx(i);
                attr->set_prog_size(size);
                p->program_active_uniform[name] = attr;
                printf ( "UNIFORM #%d Type: '%s' Name: '%s' Size: %d\n", attr->get_prog_indx()
                         , unfa::get_glsl_type_name(attr->get_glsl_type_id())
                         , name
                         , attr->get_prog_size()
                       );
            }
        }
        virtual const char* get_failure(prog*) { return "empty INIT state"; }
    } ss; return &ss;
}

//gx::root::root(QWidget* parent) : QOpenGLWidget(parent) {}

//gx::root::~root(){}
