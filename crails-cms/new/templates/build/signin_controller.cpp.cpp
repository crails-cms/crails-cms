#include <sstream>
#include "crails/render_target.hpp"
#include "crails/shared_vars.hpp"
#include "crails/template.hpp"
#include <crails/cli/conventions.hpp>

class render_ProjectControllersSigninCpp : public Crails::Template
{
public:
  render_ProjectControllersSigninCpp(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars) :
    Crails::Template(renderer, target, vars), 
    classname( Crails::naming_convention.classnames("SessionController")), 
    userclass( Crails::naming_convention.classnames("User"))
  {}

  void render()
  {
ecpp_stream << "#include \"signin.hpp\"\n\nusing namespace std;\n" << ( classname );
  ecpp_stream << "::" << ( classname );
  ecpp_stream << "(Crails::Context& context) : Super(context)\n{\n}\n\nvoid " << ( classname );
  ecpp_stream << "::new_()\n{\n  render(\"session/new\");\n}\n\nvoid " << ( classname );
  ecpp_stream << "::on_session_created()\n{\n  if (params[\"redirect_to\"].exists())\n    redirect_to(params[\"redirect_to\"].as<string>());\n  else\n    redirect_to(\"/\");\n}\n\nvoid " << ( classname );
  ecpp_stream << "::on_session_destroyed()\n{\n  redirect_to(\"/\");\n}\n\nvoid " << ( classname );
  ecpp_stream << "::on_session_not_created()\n{\n  flash[\"error\"] = \"Invalid credentials\";\n  if (params[\"redirect_to\"].exists())\n    redirect_to(params[\"redirect_to\"].as<string>());\n  else\n    render(\"session/new\");\n}\n\nshared_ptr<" << ( userclass );
  ecpp_stream << "> " << ( classname );
  ecpp_stream << "::find_user()\n{\n  shared_ptr<" << ( userclass );
  ecpp_stream << "> user;\n  Crails::Password password(params[\"password\"].as<string>());;\n\n  database.find_one(\n    user,\n    odb::query<" << ( userclass );
  ecpp_stream << ">::email == params[\"email\"].as<string>() &&\n    odb::query<" << ( userclass );
  ecpp_stream << ">::password == password.c_str()\n  );\n  return user;\n}\n";
    this->target.set_body(ecpp_stream.str());
  }
private:
  std::stringstream ecpp_stream;
  std::string classname;
  std::string userclass;
};

void render_project_controllers_signin_cpp(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars)
{
  render_ProjectControllersSigninCpp(renderer, target, vars).render();
}