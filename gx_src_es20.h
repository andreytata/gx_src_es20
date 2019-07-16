#ifndef GX_GLES20_GLSL11_WRAPPER_H
#define GX_GLES20_GLSL11_WRAPPER_H

#include <map>
#include <list>
#include <string>
#include <memory>

//#include <QObject>
#include <QBasicTimer>  //           timer;
//QOpenGLShaderProgram  program;
#include <QOpenGLTexture>  //       *texture;

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QVector2D>
#include <QVector3D>
#include <QVector4D>
#include <QObject>

#define JSON(...) #__VA_ARGS__
/* // HOWTO use this JSON define:
const char* sample_json = JSON ( // comment
{"run_machine":"load_parallel_threads"
//,"0" : "https://godbolt.org?123&123"
,"1" : "https://godbolt.org??123&123"
,"2" : "https://god_bolt.org?123&123"
,"3" : "https://god___bolt.org??123&123"
,"4" : "https://god_____bolt.org?123&123"
,"5" : "https://godbolt.org???123&123"
,"one_success": ["stop_other","print_curr", "sw_machine"]
,"one_failure": ["print_curr","print_fail", "_continue"]
,"all_failure": ["reset_to_initial_state"]
});
*/

namespace gx
{
    struct prog;  // glsl program state machine
    struct indx;  // draw method base class TRIANGLE_FAN, TRIANGLE_STRIP, TRIANGLES, e.t.c.
    struct vtxa;  // glsl program abstract attribute
                  // void set_curr(prog*)
    struct vtxb;  // vertex buffer (possible interlived)
                  // void set_attr(const char* glsl_name, vtxa*);

    struct unfa;  // glsl program abstract uniform attribute
    struct surf;  // immutable surface's description base class
                  // void set_vtxb(const char* glsl_name, std::shared_ptr<vtxa>);
    struct shdg {
        std::shared_ptr<prog> prog_ref;  // self shdg
        std::shared_ptr<vtxb> vtxb_ref;  // self vtxb
        struct vars_map;
        virtual void calculate_vars_map(){}
        std::list<std::shared_ptr<indx> > draw_map;  // ibo bind & draw surface part
    };

    struct tran {    // base class for proj/node/joint with get_mat4 pointer ability
        virtual ~tran() {}
        virtual float* get_mat4() = 0;
    };

    struct surf {    // shared surface ( exported const object )
        std::map<std::string, vtxa*> m_buff;  // exported vertex attributes                (const)
        std::map<std::string, unfa*> m_vars;  // exported dependances (uniform attributes) (const)
                                              // initial textures, weights,
                                              // ...
        std::list<indx*> m_ibo;               // index arrays with draw mode
        std::list<tran*> m_to_export_root;    // const exported scene position
        std::list<tran*> joints;              // skin's fixed exported joints in bind-pos
    };

    struct shgr   // shading group material and surface based(real-time animated view-surface)
    {
        surf* mp_surf;
        prog* mp_prog;

        std::map<std::string, unfa*> m_vars;  // changed dependances (uniform attributes)
                                              // changed textures and other uniforms
                                              // initial contain self mp_surf->m_vars;
        std::list<tran*> m_to_export_root;    // editable exported scene position
        std::list<tran*> m_to_mount_root;     // scene root scene initial - empty
        std::list<tran*> m_joints;            // animated joints, binded to other transformations
        virtual void draw() { }
    };

    // GL index array
    // Surf contain one or more named index arrays. Each faces set can be drawed
    // separately with other draw method, textures, programm, gl-option, e.t.c.
    struct indx
    {
        struct triangles;
        struct triangle_fan;
        struct triangle_strip;
        struct proc
        {   // visitor needed?
            virtual ~proc() {}
            virtual void on(gx::indx::triangles      *) = 0;
            virtual void on(gx::indx::triangle_fan   *) = 0;
            virtual void on(gx::indx::triangle_strip *) = 0;
        };
        virtual ~indx() {}
        virtual unsigned  get_size() const = 0;
        virtual unsigned* get_buff() = 0;  // is can be calculated, deprecate 'const'
        virtual void on(gx::indx*) = 0;
    };

    struct indx::triangles:indx {
        void on(indx::proc*o){o->on(this);}
        virtual ~triangles() {}
    };

    struct indx::triangle_strip:indx {
        void on(indx::proc*o){o->on(this);}
        virtual ~triangle_strip() {}
    };

    struct indx::triangle_fan:indx {
        void on(indx::proc*o){o->on(this);}
        virtual ~triangle_fan() {}
    };

    // GLES2.0 GLSL1.1 vertex attributes

    struct av1f;    struct av2f;    struct av3f;    struct av4f;
    struct av1i;    struct av2i;    struct av3i;    struct av4i;
    struct av1b;    struct av2b;    struct av3b;    struct av4b;
    struct av1u;    struct am2f;    struct am3f;    struct am4f;

    // GLSL vertex attribute abstract base class

    struct vtxa
    {
        // program -> get attribute location by name
        // program -> enable attribute array at attribute location
        // program -> set variable attribute location in binded VBO use offset and size"step"buffer
        struct proc
        {
            virtual ~proc() {}
            virtual void on(gx::av1f*) = 0;  // "float"         GL_FLOAT
            virtual void on(gx::av2f*) = 0;  // "vec2"          GL_FLOAT_VEC2
            virtual void on(gx::av3f*) = 0;  // "vec3"          GL_FLOAT_VEC3
            virtual void on(gx::av4f*) = 0;  // "vec4"          GL_FLOAT_VEC4
            virtual void on(gx::av1i*) = 0;  // "int"           GL_INT
            virtual void on(gx::av2i*) = 0;  // "ivec2"         GL_INT_VEC2
            virtual void on(gx::av3i*) = 0;  // "ivec3"         GL_INT_VEC3
            virtual void on(gx::av4i*) = 0;  // "ivec4"         GL_INT_VEC4
            virtual void on(gx::av1u*) = 0;  // "unsigned int"  GL_UNSIGNED_INT
            virtual void on(gx::av1b*) = 0;  // "bool"          GL_BOOL
            virtual void on(gx::av2b*) = 0;  // "bvec2"         GL_BOOL_VEC2
            virtual void on(gx::av3b*) = 0;  // "bvec3"         GL_BOOL_VEC3
            virtual void on(gx::av4b*) = 0;  // "bvec4"         GL_BOOL_VEC4
            virtual void on(gx::am2f*) = 0;  // "mat2"          GL_FLOAT_MAT2
            virtual void on(gx::am3f*) = 0;  // "mat3"          GL_FLOAT_MAT3
            virtual void on(gx::am4f*) = 0;  // "mat4"          GL_FLOAT_MAT4
        };

        virtual void on(vtxa::proc*) = 0;

        virtual int get_glsl_type_id() const = 0;

        virtual const char* get_glsl_type_name() const = 0;

        // virtual int get_size() const = 0;

        virtual ~vtxa(){}

        static const char* get_glsl_type_name(const int& n);
    };                                                            // vtxa

    // GLES2.0 GLSL1.1 uniform attributes

    struct uv1f;    struct uv2f;    struct uv3f;    struct uv4f;  // float, vec*
    struct uv1i;    struct uv2i;    struct uv3i;    struct uv4i;  // int, ivec*
    struct uv1b;    struct uv2b;    struct uv3b;    struct uv4b;  // bool, bvec*
    struct uv1u;    struct um2f;    struct um3f;    struct um4f;  // unsigned int, mat*
    struct tx2d;  // sampler2D     GL_SAMPLER_2D
    struct txcb;  // samplerCube   GL_SAMPLER_CUBE

    struct unfa
    {
        struct prog
        {
            virtual ~prog(){}
            virtual void on(gx::uv1f*) = 0;  // float         GL_FLOAT
            virtual void on(gx::uv2f*) = 0;  // vec2          GL_FLOAT_VEC2
            virtual void on(gx::uv3f*) = 0;  // vec3          GL_FLOAT_VEC3
            virtual void on(gx::uv4f*) = 0;  // vec4          GL_FLOAT_VEC4
            virtual void on(gx::uv1i*) = 0;  // int           GL_INT
            virtual void on(gx::uv2i*) = 0;  // ivec2         GL_INT_VEC2
            virtual void on(gx::uv3i*) = 0;  // ivec3         GL_INT_VEC3
            virtual void on(gx::uv4i*) = 0;  // ivec4         GL_INT_VEC4
            virtual void on(gx::uv1u*) = 0;  // unsigned int  GL_UNSIGNED_INT
            virtual void on(gx::uv1b*) = 0;  // bool          GL_BOOL
            virtual void on(gx::uv2b*) = 0;  // bvec2         GL_BOOL_VEC2
            virtual void on(gx::uv3b*) = 0;  // bvec3         GL_BOOL_VEC3
            virtual void on(gx::uv4b*) = 0;  // bvec4         GL_BOOL_VEC4
            virtual void on(gx::um2f*) = 0;  // mat2          GL_FLOAT_MAT2
            virtual void on(gx::um3f*) = 0;  // mat3          GL_FLOAT_MAT3
            virtual void on(gx::um4f*) = 0;  // mat4          GL_FLOAT_MAT4
            virtual void on(gx::tx2d*) = 0;  // sampler2D     GL_SAMPLER_2D
            virtual void on(gx::txcb*) = 0;  // samplerCube   GL_SAMPLER_CUBE
        };

        virtual void on(unfa::prog*) = 0;

        virtual ~unfa() {}

        virtual const char* get_glsl_type_id() = 0;

        virtual const char* get_glsl_type_name() = 0;

        static const char* get_glsl_type_name(const int& n);
    };                                                            // unfa

    struct av1f : vtxa
    {
        virtual ~av1f() {}
        virtual float* get_buff() = 0;
        virtual int    get_size() = 0;

        void on(vtxa::proc* o) { o->on(this); }

        int  get_glsl_type_id() const { return GL_FLOAT; }

        const char* get_glsl_type_name() const { return "float"; }
    };

    struct av2f : vtxa
    {
        virtual ~av2f() {}
        virtual float* get_buff() = 0;
        virtual int    get_size() = 0;

        void on(vtxa::proc* o) { o->on(this); }

        int  get_glsl_type_id() const { return GL_FLOAT_VEC2; }

        const char* get_glsl_type_name() const { return "vec2"; }
    };

    struct av3f : vtxa
    {
        virtual ~av3f() {}
        virtual float* get_buff() = 0;
        virtual int    get_size() = 0;

        void on(vtxa::proc* o) { o->on(this); }

        int  get_glsl_type_id() const { return GL_FLOAT_VEC3; }

        const char* get_glsl_type_name() const { return "vec3"; }
    };

    struct av4f : vtxa
    {
        virtual ~av4f() {}
        virtual float* get_buff() = 0;
        virtual int    get_size() = 0;

        void on(vtxa::proc* o) { o->on(this); }

        int  get_glsl_type_id() const { return GL_FLOAT_VEC4; }

        const char* get_glsl_type_name() const { return "vec4"; }
    };

    struct av1i : vtxa
    {
        virtual ~av1i() {}
        virtual int*   get_buff() = 0;
        virtual int    get_size() = 0;

        void on(vtxa::proc* o) { o->on(this); }

        int  get_glsl_type_id() const { return GL_INT; }

        const char* get_glsl_type_name() const { return "int"; }
    };

    struct av2i : vtxa
    {
        virtual ~av2i() {}
        virtual int*   get_buff() = 0;
        virtual int    get_size() = 0;

        void on(vtxa::proc* o) { o->on(this); }

        int  get_glsl_type_id() const { return GL_INT_VEC2; }

        const char* get_glsl_type_name() const { return "ivec2"; }
    };

    struct av3i : vtxa
    {
        virtual ~av3i() {}
        virtual int*   get_buff() = 0;
        virtual int    get_size() = 0;

        void on(vtxa::proc* o) { o->on(this); }

        int  get_glsl_type_id() const { return GL_INT_VEC3; }

        const char* get_glsl_type_name() const { return "ivec3"; }
    };

    struct av4i : vtxa
    {
        virtual ~av4i() {}
        virtual int*   get_buff() = 0;
        virtual int    get_size() = 0;

        void on(vtxa::proc* o) { o->on(this); }

        int  get_glsl_type_id() const { return GL_INT_VEC4; }

        const char* get_glsl_type_name() const { return "ivec4"; }
    };

    struct av1u : vtxa
    {
        virtual ~av1u() {}
        virtual unsigned int* get_buff() = 0;
        virtual int           get_size() = 0;

        void on(vtxa::proc* o) { o->on(this); }

        int  get_glsl_type_id() const { return GL_UNSIGNED_INT; }

        const char* get_glsl_type_name() const { return "unsigned int"; }
    };

    struct av1b : vtxa
    {
        virtual ~av1b() {}
        virtual bool* get_buff() = 0;
        virtual int   get_size() = 0;


        void on(vtxa::proc* o) { o->on(this); }

        int  get_glsl_type_id() const { return GL_BOOL; }

        const char* get_glsl_type_name() const { return "bool"; }
    };

    struct av2b : vtxa
    {
        virtual ~av2b() {}
        virtual bool* get_buff() = 0;
        virtual int   get_size() = 0;

        void on(vtxa::proc* o) { o->on(this); }

        int  get_glsl_type_id() const { return GL_BOOL_VEC2; }

        const char* get_glsl_type_name() const { return "bvec2"; }
    };

    struct av3b : vtxa
    {
        virtual ~av3b() {}
        virtual bool* get_buff() = 0;
        virtual int   get_size() = 0;

        void on(vtxa::proc* o) { o->on(this); }

        int  get_glsl_type_id() const { return GL_BOOL_VEC3; }

        const char* get_glsl_type_name() const { return "bvec3"; }
    };

    struct av4b : vtxa
    {
        virtual ~av4b() {}
        virtual bool* get_buff() = 0;
        virtual int   get_size() = 0;

        void on(vtxa::proc* o) { o->on(this); }

        int  get_glsl_type_id() const { return GL_BOOL_VEC4; }

        const char* get_glsl_type_name() const { return "bvec4"; }
    };

    struct am2f : vtxa
    {
        virtual ~am2f() {}
        virtual float* get_buff() = 0;
        virtual int    get_size() = 0;

        void on(vtxa::proc* o) { o->on(this); }

        int  get_glsl_type_id() const { return GL_FLOAT_MAT2; }

        const char* get_glsl_type_name() const { return "mat2"; }
    };

    struct am3f : vtxa
    {
        virtual ~am3f() {}
        virtual float* get_buff() = 0;
        virtual int    get_size() = 0;

        void on(vtxa::proc* o) { o->on(this); }

        int  get_glsl_type_id() const { return GL_FLOAT_MAT3; }

        const char* get_glsl_type_name() const { return "mat3"; }
    };

    struct am4f : vtxa
    {
        virtual ~am4f() {}
        virtual float* get_buff() = 0;
        virtual int    get_size() = 0;

        void on(vtxa::proc* o) { o->on(this); }

        int  get_glsl_type_id() const { return GL_FLOAT_MAT4; }

        const char* get_glsl_type_name() const { return "mat4"; }
    };

    // GLSL uniform attributes abstract base class


    struct uv1f : unfa
    {
        virtual ~uv1f() {}
        virtual float* get_buff() = 0;
        virtual int    get_size() = 0;

        void on(unfa::prog* o) { o->on(this); }

        int  get_glsl_type_id() const { return GL_FLOAT; }

        const char* get_glsl_type_name() const { return "float"; }
    };

    struct uv2f : unfa
    {
        virtual ~uv2f() {}
        virtual float* get_buff() = 0;
        virtual int    get_size() = 0;

        void on(unfa::prog* o) { o->on(this); }

        int  get_glsl_type_id() const { return GL_FLOAT_VEC2; }

        const char* get_glsl_type_name() const { return "vec2"; }
    };

    struct uv3f : unfa
    {
        virtual ~uv3f() {}
        virtual float* get_buff() = 0;
        virtual int    get_size() = 0;

        void on(unfa::prog* o) { o->on(this); }

        int  get_glsl_type_id() const { return GL_FLOAT_VEC3; }

        const char* get_glsl_type_name() const { return "vec3"; }
    };

    struct uv4f : unfa
    {
        virtual ~uv4f() {}
        virtual float* get_buff() = 0;
        virtual int    get_size() = 0;

        void on(unfa::prog* o) { o->on(this); }

        int  get_glsl_type_id() const { return GL_FLOAT_VEC4; }

        const char* get_glsl_type_name() const { return "vec4"; }
    };

    struct uv1i : unfa
    {
        virtual ~uv1i() {}
        virtual int* get_buff() = 0;
        virtual int  get_size() = 0;

        void on(unfa::prog* o) { o->on(this); }

        int  get_glsl_type_id() const { return GL_INT; }

        const char* get_glsl_type_name() const { return "int"; }
    };

    struct uv2i : unfa
    {
        virtual ~uv2i() {}
        virtual int* get_buff() = 0;
        virtual int  get_size() = 0;

        void on(unfa::prog* o) { o->on(this); }

        int  get_glsl_type_id() const { return GL_INT_VEC2; }

        const char* get_glsl_type_name() const { return "ivec2"; }
    };

    struct uv3i : unfa
    {
        virtual ~uv3i() {}
        virtual int* get_buff() = 0;
        virtual int  get_size() = 0;

        void on(unfa::prog* o) { o->on(this); }

        int  get_glsl_type_id() const { return GL_INT_VEC3; }

        const char* get_glsl_type_name() const { return "ivec3"; }
    };

    struct uv4i : unfa
    {
        virtual ~uv4i() {}
        virtual int* get_buff() = 0;
        virtual int  get_size() = 0;

        void on(unfa::prog* o) { o->on(this); }

        int  get_glsl_type_id() const { return GL_INT_VEC4; }

        const char* get_glsl_type_name() const { return "ivec4"; }
    };

    struct uv1u : unfa
    {
        virtual ~uv1u() {}
        virtual unsigned int* get_buff() = 0;
        virtual int  get_size() = 0;

        void on(unfa::prog* o) { o->on(this); }

        int  get_glsl_type_id() const { return GL_UNSIGNED_INT; }

        const char* get_glsl_type_name() const { return "unsigned int"; }
    };

    struct uv1b : unfa
    {
        virtual ~uv1b() {}
        virtual bool* get_buff() = 0;
        virtual int   get_size() = 0;

        void on(unfa::prog* o) { o->on(this); }

        int  get_glsl_type_id() const { return GL_BOOL; }

        const char* get_glsl_type_name() const { return "bool"; }
    };

    struct uv2b : unfa
    {
        virtual ~uv2b() {}
        virtual bool* get_buff() = 0;
        virtual int   get_size() = 0;

        void on(unfa::prog* o) { o->on(this); }

        int  get_glsl_type_id() const { return GL_BOOL_VEC2; }

        const char* get_glsl_type_name() const { return "bvec2"; }
    };

    struct uv3b : unfa
    {
        virtual ~uv3b() {}
        virtual bool* get_buff() = 0;
        virtual int   get_size() = 0;

        void on(unfa::prog* o) { o->on(this); }

        int  get_glsl_type_id() const { return GL_BOOL_VEC3; }

        const char* get_glsl_type_name() const { return "bvec3"; }
    };

    struct uv4b : unfa
    {
        virtual ~uv4b() {}
        virtual bool* get_buff() = 0;
        virtual int   get_size() = 0;

        void on(unfa::prog* o) { o->on(this); }

        int  get_glsl_type_id() const { return GL_BOOL_VEC4; }

        const char* get_glsl_type_name() const { return "bvec4"; }
    };

    struct um2f : unfa
    {
        virtual ~um2f() {}
        virtual float* get_buff() = 0;
        virtual int    get_size() = 0;

        void on(unfa::prog* o) { o->on(this); }

        int  get_glsl_type_id() const { return GL_FLOAT_MAT2; }

        const char* get_glsl_type_name() const { return "mat2"; }
    };

    struct um3f : unfa
    {
        virtual ~um3f() {}
        virtual float* get_buff() = 0;
        virtual int    get_size() = 0;

        void on(unfa::prog* o) { o->on(this); }

        int  get_glsl_type_id() const { return GL_FLOAT_MAT3; }

        const char* get_glsl_type_name() const { return "mat3"; }
    };

    struct um4f : unfa
    {
        virtual ~um4f() {}
        virtual float* get_buff() = 0;
        virtual int    get_size() = 0;

        void on(unfa::prog* o) { o->on(this); }

        int  get_glsl_type_id() const { return GL_FLOAT_MAT4; }

        const char* get_glsl_type_name() const { return "mat4"; }
    };

    struct tx2d : unfa
    {
        virtual ~tx2d() {}

        void on(unfa::prog* o) { o->on(this); }

        int  get_glsl_type_id() const { return GL_SAMPLER_2D; }

        const char* get_glsl_type_name() const { return "sampler2D"; }
    };

    struct txcb : unfa
    {
        virtual ~txcb() {}

        void on(unfa::prog* o) { o->on(this); }

        int  get_glsl_type_id() const { return GL_SAMPLER_CUBE; }

        const char* get_glsl_type_name() const { return "samplerCube"; }
    };

    struct stse
    {
        struct item; struct tran; struct draw;
        struct proc
        {
            virtual ~proc(){}
            virtual void on(item*) = 0;
            virtual void on(tran*) = 0;
            virtual void on(draw*) = 0;
        };
        struct item {
            virtual ~item(){}
            virtual void on(stse::proc*) = 0;
        };
    };

    struct vtxb : stse::item {
        virtual ~vtxb(){}
        virtual float* get_buff() const = 0;
        virtual std::map<std::string, std::pair<vtxa*, int> >* get_vars() = 0;
        void on(stse::proc*p){p->on(this);}
    };

    struct example
    {
        static vtxb* get_vtxb()
        {
            static struct : vtxb
            {
                float* get_buff() const { static float a[] = {1.f,2.f,3.f}; return a; }
                int get_size() const { return 3*sizeof(float); }
                std::map<std::string, std::pair<vtxa*, int > >* get_vars()
                {
                    static struct a_position: av4f  {
                        vtxb* vbo;
                        a_position(vtxb* interleaved):vbo(interleaved){}
                        float* get_buff() { return vbo->get_buff(); }
                        int    get_size() { return 1; }
                    } attr0(this);
                    static struct a_normals: av4f  {
                        vtxb* vbo;
                        a_normals(vtxb* interleaved):vbo(interleaved){}
                        float* get_buff() { return vbo->get_buff(); }
                        int    get_size() { return 1; }
                    } attr1(this);
                    static std::map<std::string, std::pair<vtxa*, int> > vars = {
                       {"a_position", { &attr0, 0 } },
                       {"a_normals" , { &attr1, 0 } },
                    };
                    return &vars;
                }
            } mapped_vbo; return &mapped_vbo;
        }
    };
}

namespace gx
{
    struct prog  // shared program fsm, some set of the prog* stored at GL-widget side
    {
        QOpenGLShaderProgram program;  // qt-shader program implementation

        struct some_state: protected QOpenGLFunctions {
            virtual ~some_state() {}
            virtual void set_current(prog*) = 0;
            virtual const char* get_failure(prog*) = 0;
        };

        static some_state* get_fail_state() {
            static struct : some_state {
                virtual void set_current(prog*){}
                virtual const char* get_failure(prog*) {return "empty FAIL state"; }
            }ss; return &ss;
        }

        static some_state* get_init_state()
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

                        printf ( "Attribute #%d Type: '%s' Name: '%s'\n" , i
                               , gx::vtxa::get_glsl_type_name(type)
                               , name
                               );
                    }

                    glGetProgramiv(program_id, GL_ACTIVE_UNIFORMS, &count);

                    qDebug() << "Active Uniforms:" << count;

                    for (i = 0; i < count; i++)
                    {
                        glGetActiveUniform(program_id, (GLuint)i, bufSize, &length, &size, &type, name);

                        printf ( "Uniform #%d Type: '%s' Name: '%s' Size:%d\n" , i
                               , gx::unfa::get_glsl_type_name(type)
                               , name
                               , size
                               );
                    }
                }
                virtual const char* get_failure(prog*) { return "empty INIT state"; }
            } ss; return &ss;
        }
        static some_state* get_draw_state() {
            static struct : some_state {
                virtual void set_current(prog*) {}
                virtual const char* get_failure(prog*) { return "empty DRAW state"; }
            } ss; return &ss;
        }
        static some_state* get_free_state() {
            static struct : some_state {
                virtual void set_current(prog*) {}
                virtual const char* get_failure(prog*) { return "empty FREE state"; }
            } ss; return &ss;
        }
        some_state *current_state = get_init_state();

        void set_current()        {        current_state->set_current(this); }
        const char* get_failure() { return current_state->get_failure(this); }

    };

    class root : public QOpenGLWidget, protected QOpenGLFunctions
    {
        Q_OBJECT

    public:
        root(QWidget* parent = 0):QOpenGLWidget(parent){}

        virtual ~root(){}

        virtual gx::prog* get_program(const char* = nullptr) { return &prog0; }
    protected:
        virtual void mousePressEvent   (QMouseEvent *e){qDebug()<<e;}  // override;

        virtual void mouseReleaseEvent (QMouseEvent *e){qDebug()<<e;}  // override;

        virtual void timerEvent        (QTimerEvent *e){qDebug()<<e;}  // override;

        virtual void initializeGL ()              {
            initializeOpenGLFunctions();

            glClearColor(0, 0, 0, 1);

            initShaders();
            initTextures();

        //! [2]
            // Enable depth buffer
            glEnable(GL_DEPTH_TEST);

            // Enable back face culling
            glEnable(GL_CULL_FACE);
        //! [2]
            // timer.start(120, this);
        }

        virtual void resizeGL     (int w, int h)  { qDebug()<<"resizeGL"<<w<<h; }  // override;

        virtual void paintGL      () {  // override;
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


        }

        virtual void initShaders  ()
        {
            // TODO: REMOVE FROM HERE
            prog0.set_current();

            // Compile vertex shader
            if (!program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vshader.glsl"))
                close();

            // Compile fragment shader
            if (!program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fshader.glsl"))
                close();

            // Link shader pipeline
            if (!program.link())
                close();

            // Bind shader pipeline for use
            if (!program.bind())
                close();

            qDebug() << "program max geom output vertices => " << program.maxGeometryOutputVertices();

            GLuint program_id = program.programId();

            qDebug() << "program.programId() => " << program_id;

            GLint i;                    // var's id
            GLint count;                // active vars count
            GLint size;                 // size of the variable

            GLenum type;                // type of the variable (float, vec3 or mat4, etc)

            const GLsizei bufSize = 64; // maximum name length
            GLchar name[bufSize];       // variable GLSL name
            GLsizei length;             // variable name length

            glGetProgramiv(program_id, GL_ACTIVE_ATTRIBUTES, &count);

            qDebug() << "Active Attributes:" << count;

            for (i = 0; i < count; i++)
            {
                glGetActiveAttrib(program_id, (GLuint)i, bufSize, &length, &size, &type, name);

                printf ( "Attribute #%d Type: '%s' Name: '%s'\n" , i
                       , gx::vtxa::get_glsl_type_name(type)
                       , name
                       );
            }

            glGetProgramiv(program_id, GL_ACTIVE_UNIFORMS, &count);

            qDebug() << "Active Uniforms:" << count;

            for (i = 0; i < count; i++)
            {
                glGetActiveUniform(program_id, (GLuint)i, bufSize, &length, &size, &type, name);

                printf ( "Uniform #%d Type: '%s' Name: '%s' Size:%d\n" , i
                       , gx::unfa::get_glsl_type_name(type)
                       , name
                       , size
                       );
            }
        }

        void initTextures ()
        {

        }

    private:
        gx::prog              prog0;
        QBasicTimer           timer;
        QOpenGLShaderProgram  program;
        QOpenGLTexture       *texture;
        QMatrix4x4            projection;
    };
}       // end namespace gx

#endif //  GX_GLES20_GLSL11_WRAPPER_H
