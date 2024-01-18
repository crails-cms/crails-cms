#include <sstream>
#include "crails/render_target.hpp"
#include "crails/shared_vars.hpp"
#include "crails/template.hpp"

class render_PluginPrebuildSh : public Crails::Template
{
public:
  render_PluginPrebuildSh(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars) :
    Crails::Template(renderer, target, vars), 
    project_name(Crails::cast<std::string>(vars, "project_name")), 
    html_renderer_classname(Crails::cast<std::string>(vars, "html_renderer_classname")), 
    json_renderer_classname(Crails::cast<std::string>(vars, "json_renderer_classname")), 
    rss_renderer_classname(Crails::cast<std::string>(vars, "rss_renderer_classname")), 
    with_javascript(Crails::cast<bool>(vars, "with_javascript",  true)), 
    with_json(Crails::cast<bool>(vars, "with_json",  true)), 
    with_rss(Crails::cast<bool>(vars, "with_rss",  true))
  {}

  void render()
  {
ecpp_stream << "#!/bin/sh\n\n##\n## Renderers\n##\ncrails templates build \\\n  -r html \\\n  -i app/views \\\n  -t Crails::HtmlTemplate \\\n  -z crails/html_template.hpp \\\n  -n " << ( html_renderer_classname );
  ecpp_stream << " \\\n  -p \\.html$ \\\n  -v\n";
 if (with_json){
  ecpp_stream << "\ncrails templates build \\\n  -r json \\\n  -i app/views \\\n  -t Crails::JsonTemplate \\\n  -z crails/json_template.hpp \\\n  -n " << ( json_renderer_classname );
  ecpp_stream << " \\\n  -p \\.json$ \\\n  -v";
 };
  ecpp_stream << "";
 if (with_rss){
  ecpp_stream << "\ncrails templates build \\\n  -r rss \\\n  -i app/views \\\n  -t Crails::RssTemplate \\\n  -z crails/rss_template.hpp \\\n  -n " << ( rss_renderer_classname );
  ecpp_stream << " \\\n  -p \\.rss$ \\\n  -v";
 };
  ecpp_stream << "";
 if (with_javascript){
  ecpp_stream << "\n##\n## JavaScript\n##\nnpm install\nnode_modules/.bin/webpack\nxxd -i -n " << ( project_name );
  ecpp_stream << "_plugin_application_js lib/application.js lib/application.js.cpp\nxxd -i -n " << ( project_name );
  ecpp_stream << "_plugin_admin_js lib/admin.js lib/admin.js.cpp";
 };
  ecpp_stream << "\n##\n## Database\n##\nodb \\\n  -I. -I../.. -I$CRAILS_CMS_INCLUDE_DIRS \\\n  --std c++17 \\\n  --default-pointer std::shared_ptr \\\n  -d pgsql \\\n  --table-prefix \"" << ( project_name );
  ecpp_stream << "_\" \\\n  --generate-schema --schema-format sql \\\n  --generate-query \\\n  --output-dir lib \\\n  app/models/*.hpp\n\n##\n## Fix ODB include paths, and generate plugin-odb.hxx\n##\nplugin_odb_hxx=\"`pwd`/lib/plugin-odb.hxx\"\ncd app/models\nrm \"$plugin_odb_hxx\"\necho \"#pragma once\" >> \"$plugin_odb_hxx\"\necho \"#include \\\"lib/odb/application-odb.hxx\\\"\" >> \"$plugin_odb_hxx\"\nfor filename in `find . -name \"*.h*\"` ; do\n  filename=`echo \"$filename\" | cut -d/ -f2`\n  part=`echo \"${filename%.*}\"`\n  regex=\"s/$filename/app\\\\/models\\\\/$filename/g\"\n  target=\"`pwd`/../../lib/$part-odb.hxx\"\n\n  echo \"#include \\\"$part-odb.hxx\\\"\" >> \"$plugin_odb_hxx\"\n\n  # Fix include path for the model class\n  sed \"$regex\" \"$target\" > .tmp.txt\n  mv .tmp.txt \"$target\"\n\n  # Removes includes to odb files, unless these files were generated by the compiler\n  odb_includes=`grep \"odb.hxx\" \"$target\" | cut -d' ' -f2 | tr -d '\"'`\n  for odb_include in $odb_includes ; do\n    if [ ! -f \"`pwd`/../../lib/$odb_include\" ] ; then\n      pattern=`echo \"$odb_include\" | sed -e 's/\\//\\\\\\\\\\//g'`\n      sed \"/$pattern/d\" \"$target\" > .tmp.txt\n      mv .tmp.txt \"$target\"\n    fi\n  done\n\n  # Replace these broken includes with an include to application-odb.hxx\n  sed '9 a#include \"lib/odb/application-odb.hxx\"' \"$target\" > .tmp.txt\n  mv .tmp.txt \"$target\"\ndone\ncd -\n\n";
    std::string _out_buffer = ecpp_stream.str();
    _out_buffer = this->apply_post_render_filters(_out_buffer);
    this->target.set_body(_out_buffer);
  }
private:
  std::stringstream ecpp_stream;
  std::string project_name;
  std::string html_renderer_classname;
  std::string json_renderer_classname;
  std::string rss_renderer_classname;
  bool with_javascript;
  bool with_json;
  bool with_rss;
};

void render_plugin_prebuild_sh(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars)
{
  render_PluginPrebuildSh(renderer, target, vars).render();
}