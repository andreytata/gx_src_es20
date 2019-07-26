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
//    gl_widget.get_program()->qdebug_active_variables();  // TEST INVOCATOR
//    return app.exec();
// 1. Get program pointer TODO: get_prog("program name")
//    gx::prog* p_prog = gl_widget.get_prog();
// 2. Print program variables
//    p_prog->qdebug_active_variables();
// 3. Get surface ??
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

void gx::prog::qdebug_active_variables()
{
    qDebug() << QString::asprintf("\ngx::prog at <%p> gl<%d> {", this, this->program.programId())
                .toStdString().c_str();

    // make simplest static "VERTEX ATTRIBUTE"s visitor
    static struct : gx::vtxa::proc {
        void on(gx::av1f* a) {qDebug() << name << "float        GL_FLOAT        " << a->get_prog_indx();}
        void on(gx::av2f* a) {qDebug() << name << "vec2         GL_FLOAT_VEC2   " << a->get_prog_indx();}
        void on(gx::av3f* a) {qDebug() << name << "vec3         GL_FLOAT_VEC3   " << a->get_prog_indx();}
        void on(gx::av4f* a) {qDebug() << name << "vec4         GL_FLOAT_VEC4   " << a->get_prog_indx();}
        void on(gx::av1i* a) {qDebug() << name << "int          GL_INT          " << a->get_prog_indx();}
        void on(gx::av2i* a) {qDebug() << name << "ivec2        GL_INT_VEC2     " << a->get_prog_indx();}
        void on(gx::av3i* a) {qDebug() << name << "ivec3        GL_INT_VEC3     " << a->get_prog_indx();}
        void on(gx::av4i* a) {qDebug() << name << "ivec4        GL_INT_VEC4     " << a->get_prog_indx();}
        void on(gx::av1u* a) {qDebug() << name << "unsigned int GL_UNSIGNED_INT " << a->get_prog_indx();}
        void on(gx::av1b* a) {qDebug() << name << "bool         GL_BOOL         " << a->get_prog_indx();}
        void on(gx::av2b* a) {qDebug() << name << "bvec2        GL_BOOL_VEC2    " << a->get_prog_indx();}
        void on(gx::av3b* a) {qDebug() << name << "bvec3        GL_BOOL_VEC3    " << a->get_prog_indx();}
        void on(gx::av4b* a) {qDebug() << name << "bvec4        GL_BOOL_VEC4    " << a->get_prog_indx();}
        void on(gx::am2f* a) {qDebug() << name << "mat2         GL_FLOAT_MAT2   " << a->get_prog_indx();}
        void on(gx::am3f* a) {qDebug() << name << "mat3         GL_FLOAT_MAT3   " << a->get_prog_indx();}
        void on(gx::am4f* a) {qDebug() << name << "mat4         GL_FLOAT_MAT4   " << a->get_prog_indx();}
        const char* name;
    }
    vtxa_visitor;
    for(auto pair: this->program_active_attributes)
    {
       //vtxa_visitor.qdebug(pair.first, pair.second);
       //qDebug() << pair.first.c_str();
       QString name = QString("  vtxa: %1 //").arg(pair.first.c_str(), -16, ' ');
       std::string buff = name.toStdString();
       vtxa_visitor.name = buff.c_str();        // pair.first.c_str();
       pair.second->on(&vtxa_visitor);
    }

    // make simplest static UNIFORM variables visitor
    static struct : gx::unfa::prog {
        const char* name;
        void on(gx::unfr* u) {qDebug() << name << "REF          TO UNFA PTR     " << u->get_prog_indx();}
        void on(gx::uv1f* u) {qDebug() << name << "float        GL_FLOAT        " << u->get_prog_indx();}
        void on(gx::uv2f* u) {qDebug() << name << "vec2         GL_FLOAT_VEC2   " << u->get_prog_indx();}
        void on(gx::uv3f* u) {qDebug() << name << "vec3         GL_FLOAT_VEC3   " << u->get_prog_indx();}
        void on(gx::uv4f* u) {qDebug() << name << "vec4         GL_FLOAT_VEC4   " << u->get_prog_indx();}
        void on(gx::uv1i* u) {qDebug() << name << "int          GL_INT          " << u->get_prog_indx();}
        void on(gx::uv2i* u) {qDebug() << name << "ivec2        GL_INT_VEC2     " << u->get_prog_indx();}
        void on(gx::uv3i* u) {qDebug() << name << "ivec3        GL_INT_VEC3     " << u->get_prog_indx();}
        void on(gx::uv4i* u) {qDebug() << name << "ivec4        GL_INT_VEC4     " << u->get_prog_indx();}
        void on(gx::uv1u* u) {qDebug() << name << "unsigned int GL_UNSIGNED_INT " << u->get_prog_indx();}
        void on(gx::uv1b* u) {qDebug() << name << "bool         GL_BOOL         " << u->get_prog_indx();}
        void on(gx::uv2b* u) {qDebug() << name << "bvec2        GL_BOOL_VEC2    " << u->get_prog_indx();}
        void on(gx::uv3b* u) {qDebug() << name << "bvec3        GL_BOOL_VEC3    " << u->get_prog_indx();}
        void on(gx::uv4b* u) {qDebug() << name << "bvec4        GL_BOOL_VEC4    " << u->get_prog_indx();}
        void on(gx::um2f* u) {qDebug() << name << "mat2         GL_FLOAT_MAT2   " << u->get_prog_indx();}
        void on(gx::um3f* u) {qDebug() << name << "mat3         GL_FLOAT_MAT3   " << u->get_prog_indx();}
        void on(gx::um4f* u) {qDebug() << name << "mat4         GL_FLOAT_MAT4   " << u->get_prog_indx();}
        void on(gx::tx2d* u) {qDebug() << name << "sampler2D    GL_SAMPLER_2D   " << u->get_prog_indx();}
        void on(gx::txcb* u) {qDebug() << name << "samplerCube  GL_SAMPLER_CUBE " << u->get_prog_indx();}
    }
    unfa_visitor;
    for(auto pair: this->program_active_uniform)
    {
        QString name = QString("  unfa: %1 //").arg(pair.first.c_str(), -16, ' ');
        std::string buff = name.toStdString();
        unfa_visitor.name = buff.c_str();        // pair.first.c_str();
        pair.second->on(&unfa_visitor);
    }

    qDebug() << "}";
}

gx::prog::prog_state* gx::prog::get_init_state()
{
    static struct : prog_state
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

gx::shgr::shgr_state* gx::shgr::get_init_state() // prepare prog and vbo (not inited)
{
        static struct: gx::shgr::shgr_state
        {
            void draw(shgr* p_shgr, const int& ibo_id) const
            {
                 // p_shgr->mp_prog->set_current();  // need bind program before draw
                 bind(p_shgr);           // bind change p_shgr's state to "fail" or "bind" state
                 p_shgr->draw(ibo_id);   // delegate "draw" to state choosen in "bind" method
                                         // of this "initial state"
            }

            void bind(shgr* p_shgr) const
            {
                // p_shgr->mp_prog->set_current();  // need bind program before detect variables locations

                // static program's vertex attributes sources
                static struct: gx::vtxa::proc
                {
                    void on(gx::av1f* a){qDebug() << name << "float        GL_FLOAT        " << a->get_prog_indx();}
                    void on(gx::av2f* a){qDebug() << name << "vec2         GL_FLOAT_VEC2   " << a->get_prog_indx();}
                    void on(gx::av3f* a){qDebug() << name << "vec3         GL_FLOAT_VEC3   " << a->get_prog_indx();}
                    void on(gx::av4f* a){
                        // Enter here on each [active-attribute-with-type-vec4]
                        // - UNKNOWN IS, exists or not apropriate vec4 buffer on data-source side
                        // - Active GLSL attribute has valid name, all other fields are unknown
                        // -
                        // Find attribute's offset in surface data source "gx::surf* this->data"
                        // vtxb.bind() =>
                        //
                        qDebug() << name << "vec4         GL_FLOAT_VEC4   " << a->get_prog_indx();
                    }
                    void on(gx::av1i* a){qDebug() << name << "int          GL_INT          " << a->get_prog_indx();}
                    void on(gx::av2i* a){qDebug() << name << "ivec2        GL_INT_VEC2     " << a->get_prog_indx();}
                    void on(gx::av3i* a){qDebug() << name << "ivec3        GL_INT_VEC3     " << a->get_prog_indx();}
                    void on(gx::av4i* a){qDebug() << name << "ivec4        GL_INT_VEC4     " << a->get_prog_indx();}
                    void on(gx::av1u* a){qDebug() << name << "unsigned int GL_UNSIGNED_INT " << a->get_prog_indx();}
                    void on(gx::av1b* a){qDebug() << name << "bool         GL_BOOL         " << a->get_prog_indx();}
                    void on(gx::av2b* a){qDebug() << name << "bvec2        GL_BOOL_VEC2    " << a->get_prog_indx();}
                    void on(gx::av3b* a){qDebug() << name << "bvec3        GL_BOOL_VEC3    " << a->get_prog_indx();}
                    void on(gx::av4b* a){qDebug() << name << "bvec4        GL_BOOL_VEC4    " << a->get_prog_indx();}
                    void on(gx::am2f* a){qDebug() << name << "mat2         GL_FLOAT_MAT2   " << a->get_prog_indx();}
                    void on(gx::am3f* a){qDebug() << name << "mat3         GL_FLOAT_MAT3   " << a->get_prog_indx();}
                    void on(gx::am4f* a){qDebug() << name << "mat4         GL_FLOAT_MAT4   " << a->get_prog_indx();}
                    gx::surf*   data = nullptr;  // data source root, where "link" find data sources;
                    shgr*       view = nullptr;  // target connections info storage instance
                    const char* name = nullptr;  // current vertex attribute name
                }
                for_each_vtxa_in_prog;
                for_each_vtxa_in_prog.data = p_shgr->mp_data;
                for_each_vtxa_in_prog.view = p_shgr;
                for(auto pair: p_shgr->mp_prog->program_active_attributes)
                {
                   for_each_vtxa_in_prog.name = pair.first.c_str();  // append pointer to attr name
                   pair.second->on(&for_each_vtxa_in_prog);          // use visitor to try link
                }
                // vbo stored at mp_data side, use on_paint() bind buffer
                // TODO: copy all uniform attributes in to this (here), to create dynamic namespace for
                // variables data sources switching. So, each created copy store self original data-ptr
                // and self own editable(inserted) data-ptr.
            }
        }
        init_bind_state; return &init_bind_state;
}

void gx::shgr::link_together()
{
        // static program's vertex attributes sources
        static struct: gx::vtxa::proc
        {
            void on(gx::av1f* a){qDebug() << name << "float        GL_FLOAT        " << a->get_prog_indx();}
            void on(gx::av2f* a){qDebug() << name << "vec2         GL_FLOAT_VEC2   " << a->get_prog_indx();}
            void on(gx::av3f* a){qDebug() << name << "vec3         GL_FLOAT_VEC3   " << a->get_prog_indx();}
            void on(gx::av4f* a){qDebug() << name << "vec4         GL_FLOAT_VEC4   " << a->get_prog_indx();}
            void on(gx::av1i* a){qDebug() << name << "int          GL_INT          " << a->get_prog_indx();}
            void on(gx::av2i* a){qDebug() << name << "ivec2        GL_INT_VEC2     " << a->get_prog_indx();}
            void on(gx::av3i* a){qDebug() << name << "ivec3        GL_INT_VEC3     " << a->get_prog_indx();}
            void on(gx::av4i* a){qDebug() << name << "ivec4        GL_INT_VEC4     " << a->get_prog_indx();}
            void on(gx::av1u* a){qDebug() << name << "unsigned int GL_UNSIGNED_INT " << a->get_prog_indx();}
            void on(gx::av1b* a){qDebug() << name << "bool         GL_BOOL         " << a->get_prog_indx();}
            void on(gx::av2b* a){qDebug() << name << "bvec2        GL_BOOL_VEC2    " << a->get_prog_indx();}
            void on(gx::av3b* a){qDebug() << name << "bvec3        GL_BOOL_VEC3    " << a->get_prog_indx();}
            void on(gx::av4b* a){qDebug() << name << "bvec4        GL_BOOL_VEC4    " << a->get_prog_indx();}
            void on(gx::am2f* a){qDebug() << name << "mat2         GL_FLOAT_MAT2   " << a->get_prog_indx();}
            void on(gx::am3f* a){qDebug() << name << "mat3         GL_FLOAT_MAT3   " << a->get_prog_indx();}
            void on(gx::am4f* a){qDebug() << name << "mat4         GL_FLOAT_MAT4   " << a->get_prog_indx();}
            gx::surf*   data = nullptr;  // data source root, where "link" find data sources;
            shgr*       view = nullptr;  // target connections info storage instance
            const char* name = nullptr;  // current vertex attribute name
        }
        for_each_vtxa_in_prog;
        for_each_vtxa_in_prog.data = mp_data;
        for_each_vtxa_in_prog.view = this;
        for(auto pair: mp_prog->program_active_attributes)
        {
           for_each_vtxa_in_prog.name = pair.first.c_str();  // append pointer to attr name
           pair.second->on(&for_each_vtxa_in_prog);          // use visitor to try link
        }
        // vbo stored at mp_data side, use on_paint() bind buffer
        // TODO: copy all uniform attributes in to this (here), to create dynamic namespace for
        // variables data sources switching. So, each created copy store self original data-ptr
        // and self own editable(inserted) data-ptr.
}

// Если текстура или шейдер получены динамически, то и монтировать его прийдется
// из цикла рисования, в этом методе. Т.е. некая структура содержит автомат поведения
// шейдера и автомат поведения текстуры и автомат вершинного буфера. Каждый из них
// может находиться в разных состояниях готовности к рисованию. Собственно не готов -
// - готовится а затем рисуется, а если готов, то сразу рисуется.
// РИСУЕМОЕ
//   флаги которые нужно установить до рисования и сбросить после рисования
//   программа (шейдеры) которые нужно выбрать, скомпилить и установить до рисования
//   vbo|ibo вершинные атрибуты которые нужно установить до рисования
//   переменные которые нужно вычислить на момент рисования и послать в программу
// is  some way to detect invacate order:
// -- some visitor inspect scene "node's", on detect "shgr" in nodes, visitor get
// program info (is_back_order or is_direct_order)
// -- store world transform and projection pointers in some (final order) pop ir push
// -- some other visitor visit final order and detect "shgr's" programs state (compile/bind)
//    and compile/bind prog. Then, with current "prog's" attributes bind curr "shgr's"
// Prog - with potentisl variables store
// Clear color and depth buffer
void gx::root::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    qDebug() << "Activated shading-groups:";

    for(auto view_pair: m_shgr_dict) {
        qDebug() << view_pair.first.c_str() << (void*)view_pair.second;
        gx::shgr* curr = view_pair.second;
        curr->bind();
    }
}

//gx::root::root(QWidget* parent) : QOpenGLWidget(parent) {}

//gx::root::~root(){}
