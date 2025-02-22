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
    project_name(Crails::cast< std::string >(vars, "project_name"))
  {}

  void render()
  {
ecpp_stream << "#include \"renderers.hpp\"\n#include \"autogen/renderers/" << ( Crails::underscore(project_name) );
  ecpp_stream << "_html_renderer.hpp\"\n#include \"autogen/renderers/" << ( Crails::underscore(project_name) );
  ecpp_stream << "_json_renderer.hpp\"\n#include \"autogen/renderers/" << ( Crails::underscore(project_name) );
  ecpp_stream << "_rss_renderer.hpp\"\n#include <crails/cms/autogen/renderers/crails_cms_html_renderer.hpp>\n#include <crails/cms/autogen/renderers/crails_cms_json_renderer.hpp>\n#include <crails/cms/autogen/renderers/crails_cms_rss_renderer.hpp>\n#include <crails/cms/views/layout.hpp>\n\nusing namespace Crails;\n\nApplicationRenderers::ApplicationRenderers()\n{\n  const auto& layouts = Crails::Cms::Layouts::singleton::require();\n  auto html_renderer = std::make_unique<CrailsCmsHtmlRenderer>();\n  auto json_renderer = std::make_unique<CrailsCmsJsonRenderer>();\n  auto rss_renderer = std::make_unique<CrailsCmsRssRenderer>();\n\n  default_format = \"text/html\";\n  layouts.load_renderers(*html_renderer);\n  html_renderer->merge(" << ( Crails::camelize(project_name) );
  ecpp_stream << "HtmlRenderer());\n  json_renderer->merge(" << ( Crails::camelize(project_name) );
  ecpp_stream << "JsonRenderer());\n  rss_renderer->merge(" << ( Crails::camelize(project_name) );
  ecpp_stream << "RssRenderer());\n  renderers.push_back(std::move(html_renderer));\n  renderers.push_back(std::move(json_renderer));\n  renderers.push_back(std::move(rss_renderer));\n}\n";
    std::string _out_buffer = ecpp_stream.str();
    _out_buffer = this->apply_post_render_filters(_out_buffer);
    this->target.set_body(_out_buffer);
  }
private:
  std::stringstream ecpp_stream;
  std::string project_name;
};

void render_project_config_renderers(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars)
{
  render_ProjectConfigRenderers(renderer, target, vars).render();
}