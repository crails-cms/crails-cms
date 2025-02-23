#include <sstream>
#include "crails/render_target.hpp"
#include "crails/shared_vars.hpp"
#include "crails/template.hpp"

class render_LayoutPluginPrebuildSh : public Crails::Template
{
public:
  render_LayoutPluginPrebuildSh(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars) :
    Crails::Template(renderer, target, vars), 
    project_name(Crails::cast< std::string >(vars, "project_name")), 
    assets_classname(Crails::cast< std::string >(vars, "assets_classname")), 
    renderer_classname(Crails::cast< std::string >(vars, "renderer_classname"))
  {}

  void render()
  {
ecpp_stream << "#!/bin/sh\n\nexport SASS_COMMAND=node_modules/.bin/sass\nexport WEBPACK_COMMAND=node_modules/.bin/webpack\nexport CRAILS_AUTOGEN_DIR=autogen\n\ncrails templates build \\\n  -r html \\\n  -i views \\\n  -t Crails::HtmlTemplate \\\n  -z crails/html_template.hpp \\\n  -n " << ( renderer_classname );
  ecpp_stream << " \\\n  -p \\.html$ \\\n  -v\n\nmkdir -p build/javascripts\nmkdir -p build/sass\n\nnpm install\n$WEBPACK_COMMAND\ncp javascripts/editor.js build/javascripts/editor.js\n\n$SASS_COMMAND -s compressed \"stylesheets/layout.scss\" > build/sass/layout.css\n$SASS_COMMAND -s compressed \"stylesheets/admin.scss\"  > build/sass/admin.css\n\ncrails-builtin-assets \\\n  --inputs \"javascripts\" \"build/sass\" \"stylesheets/fonts\" \\\n  --output \"autogen/assets\" \\\n  --classname \"" << ( assets_classname );
  ecpp_stream << "\" \\\n  --compression \"gzip\" \\\n  --uri-root \"/cms/plugins/" << ( project_name );
  ecpp_stream << "/assets/\"\n";
    std::string _out_buffer = ecpp_stream.str();
    _out_buffer = this->apply_post_render_filters(_out_buffer);
    this->target.set_body(_out_buffer);
  }
private:
  std::stringstream ecpp_stream;
  std::string project_name;
  std::string assets_classname;
  std::string renderer_classname;
};

void render_layout_plugin_prebuild_sh(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars)
{
  render_LayoutPluginPrebuildSh(renderer, target, vars).render();
}