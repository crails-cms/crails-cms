#include <sstream>
#include "crails/render_target.hpp"
#include "crails/shared_vars.hpp"
#include "crails/template.hpp"
#include <crails/utils/semantics.hpp>

class render_ProjectConfigRenderers : public Crails::Template
{
public:
  render_ProjectConfigRenderers(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars) :
    Crails::Template(renderer, target, vars), 
    project_name(Crails::cast<std::string>(vars, "project_name"))
  {}

  void render()
  {
ecpp_stream << "#include \"renderers.hpp\"\n#include \"lib/renderers/" << ( Crails::underscore(project_name) );
  ecpp_stream << "_html_renderer.hpp\"\n#include \"lib/renderers/" << ( Crails::underscore(project_name) );
  ecpp_stream << "_json_renderer.hpp\"\n#include <crails/cms/lib/renderers/crails_cms_html_renderer.hpp>\n#include <crails/cms/lib/renderers/crails_cms_json_renderer.hpp>\n#include <crails/cms/views/layout.hpp>\n\nusing namespace Crails;\n\nApplicationRenderers::ApplicationRenderers()\n{\n  const auto& layouts = Crails::Cms::Layouts::singleton::require();\n  CrailsCmsHtmlRenderer html_renderer;\n  CrailsCmsJsonRenderer json_renderer;\n\n  default_format = \"text/html\";\n  layouts.load_renderers(html_renderer);\n  html_renderer.merge(" << ( Crails::camelize(project_name) );
  ecpp_stream << "HtmlRenderer());\n  json_renderer.merge(" << ( Crails::camelize(project_name) );
  ecpp_stream << "JsonRenderer());\n  renderers.push_back(std::make_unique<Crails::HtmlRenderer>(html_renderer));\n  renderers.push_back(std::make_unique<Crails::JsonRenderer>(json_renderer));\n}\n";
    this->target.set_body(ecpp_stream.str());
  }
private:
  std::stringstream ecpp_stream;
  std::string project_name;
};

void render_project_config_renderers(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars)
{
  render_ProjectConfigRenderers(renderer, target, vars).render();
}