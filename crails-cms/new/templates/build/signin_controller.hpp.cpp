#include <sstream>
#include "crails/render_target.hpp"
#include "crails/shared_vars.hpp"
#include "crails/template.hpp"
#include <crails/cli/conventions.hpp>

class render_ProjectControllersSigninHpp : public Crails::Template
{
public:
  render_ProjectControllersSigninHpp(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars) :
    Crails::Template(renderer, target, vars), 
    classname( Crails::naming_convention.classnames("SessionController")), 
    super( "Crails::SessionController<"
  + Crails::naming_convention.classnames("User") + ", "
  + "Crails::Odb::Controller<"
  + Crails::naming_convention.classnames("ApplicationController") + ">>")
  {}

  void render()
  {
ecpp_stream << "#include <crails/signin/session_controller.hpp>\n#include <crails/odb/controller.hpp>\n#include \"application.hpp\"\n#include \"../models/user.hpp\"\n#include \"autogen/odb/application-odb.hxx\"\n\nclass " << ( classname );
  ecpp_stream << " : public " << ( super );
  ecpp_stream << "\n{\n  typedef " << ( super );
  ecpp_stream << " Super;\npublic:\n  " << ( classname );
  ecpp_stream << "(Crails::Context&);\n\n  void new_();\n  void on_session_created() override;\n  void on_session_destroyed() override;\n  void on_session_not_created() override;\n\nprivate:\n  std::shared_ptr<" << ( Crails::naming_convention.classnames("User") );
  ecpp_stream << "> find_user() override;\n};\n";
    std::string _out_buffer = ecpp_stream.str();
    _out_buffer = this->apply_post_render_filters(_out_buffer);
    this->target.set_body(_out_buffer);
  }
private:
  std::stringstream ecpp_stream;
  std::string classname;
  std::string super;
};

void render_project_controllers_signin_hpp(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars)
{
  render_ProjectControllersSigninHpp(renderer, target, vars).render();
}