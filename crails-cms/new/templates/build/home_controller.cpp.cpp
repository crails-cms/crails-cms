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
ecpp_stream << "#include <crails/cms/views/layout.hpp>\n#include \"home.hpp\"\n#include \"app/models/homepage.hpp\"\n#include \"app/autogen/odb/application-odb.hpp\"\n\nusing namespace std;\n" << ( classname );
  ecpp_stream << "::" << ( classname );
  ecpp_stream << "(Crails::Context& context) : " << ( parent_class );
  ecpp_stream << "(context)\n{\n  vars[\"layout\"] = std::string(\"layouts/application\");\n}\n\nvoid " << ( classname );
  ecpp_stream << "::initialize()\n{\n  " << ( parent_class );
  ecpp_stream << "::initialize();\n  if (!settings)\n    redirect_to(\"/admin/wizard\");\n}\n\nvoid " << ( classname );
  ecpp_stream << "::index()\n{\n  if (page)\n  {\n    const Crails::Cms::Layout& layout = page->get_layout();\n    string layout_path = layout.get_layout_path();\n    string page_view = \"pages/show\";\n\n    if (!layout_path.length()) \n      layout_path = settings->get_layout().get_layout_path();\n    if (layout.get_type() == Crails::Cms::DocumentLayoutType)\n      page_view = \"pages/document\";\n    prepare_open_graph(*page);\n    vars[\"layout\"] = layout_path;\n    vars[\"render_footer\"] = !page->get_has_footer();\n    render(page_view, {\n      {\"page\", reinterpret_cast<const Crails::Cms::Page*>(page.get())}\n    });\n  }\n  else\n    render(TEXT, \"No homepage set\");\n}\n\nshared_ptr<Crails::Cms::Settings> " << ( classname );
  ecpp_stream << "::find_settings()\n{\n  shared_ptr<" << ( Crails::naming_convention.classnames("SettingsHomepageQuery") );
  ecpp_stream << "> query;\n\n  database.find_one(query);\n  if (query)\n  {\n    settings = query->settings;\n    page = query->page;\n  }\n  return settings;\n}\n";
    std::string _out_buffer = ecpp_stream.str();
    _out_buffer = this->apply_post_render_filters(_out_buffer);
    this->target.set_body(_out_buffer);
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