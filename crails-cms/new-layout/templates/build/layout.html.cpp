#include <sstream>
#include "crails/render_target.hpp"
#include "crails/shared_vars.hpp"
#include "crails/template.hpp"

class render_LayoutPluginLayoutHtml : public Crails::Template
{
public:
  render_LayoutPluginLayoutHtml(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars) :
    Crails::Template(renderer, target, vars), 
    assets_classname(Crails::cast<std::string>(vars, "assets_classname")), 
    style_classname(Crails::cast<std::string>(vars, "style_classname"))
  {}

  void render()
  {
ecpp_stream << "#include <crails/i18n.hpp>\n#include <crails/cms/models/settings.hpp>\n#include <crails/cms/views/menu.hpp>\n#include <crails/cms/opengraph.hpp>\n#include \"lib/assets.hpp\"\n#include \"src/style.hpp\"\n\nconst char* @yield;\nconst Crails::Cms::Settings& @settings;\nconst Crails::Cms::OpenGraph* @open_graph = nullptr;\nstd::string @page_title = settings.get_title();\nbool @render_footer = true;" << ( style_classname );
  ecpp_stream << " style;\n\n// END LINKING\n<html lang=\"<%= i18n::Settings::singleton::require().get_current_locale() %>\">\n  <head>\n    <title><%= page_title %></title>\n    <meta charset=\"utf-8\">\n    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\" />\n    <% if (open_graph) do -%>\n      <%= open_graph->render() %>\n    <% end -%>\n    <% if (settings.get_favicon().length()) do -%>\n      <%= tag(\"link\", {{\"rel\",\"icon\"},{\"href\", settings.get_favicon()}}) %>\n    <% end -%>\n    <%= tag(\"link\", {{\"rel\",\"stylesheet\"},{\"href\", " << ( assets_classname );
  ecpp_stream << "::layout_css}}) %>\n  </head>\n  <body>\n    <header>\n      <%= Crails::Cms::RenderMenu(\"main-menu\", this)\n             .with_direction(Crails::Cms::Menu::Horizontal)\n             .with_style(&style)() yields %>\n        <h1><%= settings.get_title() %></h1>\n      <% yields-end %>\n    </header>\n\n    <main>\n      <% if (yield != nullptr) do -%>\n        <%= yield %>\n      <% end -%>\n\n      <% if (render_footer) do -%>\n        <%= settings.get_footer() %>\n      <% end -%>\n    </main>\n  </body>\n</html>\n";
    this->target.set_body(ecpp_stream.str());
  }
private:
  std::stringstream ecpp_stream;
  std::string assets_classname;
  std::string style_classname;
};

void render_layout_plugin_layout_html(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars)
{
  render_LayoutPluginLayoutHtml(renderer, target, vars).render();
}