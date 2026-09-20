#include <crails/template_stream.hpp>
#include "crails/render_target.hpp"
#include "crails/shared_vars.hpp"
#include "crails/template.hpp"
#include <crails/cli/conventions.hpp>

class render_ProjectControllersAdminOpengraphHpp : public Crails::Template
{
public:
  render_ProjectControllersAdminOpengraphHpp(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars) :
    Crails::Template(renderer, target, vars), 
    class_name( Crails::naming_convention.classnames("OpenGraphController")), 
    user_class( Crails::naming_convention.classnames("User")), 
    super( Crails::naming_convention.classnames("AdminApplicationController"))
  {}

  void render()
  {
    ecpp_stream.reserve(1118);
    // BEGIN TEMPLATE BODY
ecpp_stream << "#pragma once\n#include <crails/cms/controllers/admin/opengraph.hpp>\n#include \"app/models/user.hpp\"\n#include \"application.hpp\"\n\nclass " << ( class_name );
  ecpp_stream << " : public Crails::Cms::OpenGraphController<" << ( user_class );
  ecpp_stream << ", " << ( super );
  ecpp_stream << ">\n{\n  typedef Crails::Cms::OpenGraphController<" << ( user_class );
  ecpp_stream << ", " << ( super );
  ecpp_stream << "> Super;\npublic:\n  " << ( class_name );
  ecpp_stream << "(Crails::Context& context) : Super(context)\n  {\n  }\n};\n";
    // END TEMPLATE BODY
    std::string _out_buffer = std::move(ecpp_stream).extract();
    this->target.set_body(this->apply_post_render_filters(std::move(_out_buffer)));
  }
private:
  Crails::TemplateStream ecpp_stream;
  std::string class_name;
  std::string user_class;
  std::string super;
};

void render_project_controllers_admin_opengraph_hpp(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars)
{
  render_ProjectControllersAdminOpengraphHpp(renderer, target, vars).render();
}