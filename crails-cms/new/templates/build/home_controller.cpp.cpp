#include <sstream>
#include "crails/render_target.hpp"
#include "crails/shared_vars.hpp"
#include "crails/template.hpp"
#include <crails/cli/conventions.hpp>

class render_ProjectControllersHomeCpp : public Crails::Template
{
public:
  render_ProjectControllersHomeCpp(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars) :
    Crails::Template(renderer, target, vars), 
    classname( Crails::naming_convention.classnames("HomeController")), 
    parent_class( Crails::naming_convention.classnames("ApplicationController"))
  {}

  void render()
  {
ecpp_stream << "#include <crails/cms/views/layout.hpp>\n#include \"home.hpp\"\n#include \"app/models/homepage.hpp\"\n#include \"lib/odb/application-odb.hxx\"\n\nusing namespace std;\n" << ( classname );
  ecpp_stream << "::" << ( classname );
  ecpp_stream << "(Crails::Context& context) : " << ( parent_class );
  ecpp_stream << "(context)\n{\n  vars[\"layout\"] = std::string(\"layouts/application\");\n}\n\nvoid " << ( classname );
  ecpp_stream << "::initialize()\n{\n  " << ( parent_class );
  ecpp_stream << "::initialize();\n  if (!settings)\n    redirect_to(\"/admin/wizard\");\n}\n\nvoid " << ( classname );
  ecpp_stream << "::index()\n{\n  if (page)\n  {\n    vars[\"layout\"] = page->get_layout().get_layout_path();\n    render(\"pages/show\", {\n      {\"page\", reinterpret_cast<const Crails::Cms::Page*>(page.get())}\n    });\n  }\n  else\n    render(TEXT, \"No homepage set\");\n}\n\nshared_ptr<Crails::Cms::Settings> " << ( classname );
  ecpp_stream << "::find_settings()\n{\n  shared_ptr<" << ( Crails::naming_convention.classnames("SettingsHomepageQuery") );
  ecpp_stream << "> query;\n\n  database.find_one(query);\n  if (query)\n  {\n    settings = query->settings;\n    page = query->page;\n  }\n  return settings;\n}\n";
    this->target.set_body(ecpp_stream.str());
  }
private:
  std::stringstream ecpp_stream;
  std::string classname;
  std::string parent_class;
};

void render_project_controllers_home_cpp(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars)
{
  render_ProjectControllersHomeCpp(renderer, target, vars).render();
}