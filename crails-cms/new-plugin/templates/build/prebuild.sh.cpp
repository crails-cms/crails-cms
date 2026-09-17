#include <sstream>
#include "crails/render_target.hpp"
#include "crails/shared_vars.hpp"
#include "crails/template.hpp"

class render_PluginPrebuildSh : public Crails::Template
{
public:
  render_PluginPrebuildSh(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars) :
    Crails::Template(renderer, target, vars), 
    project_name(Crails::cast< std::string >(vars, "project_name")), 
    html_renderer_classname(Crails::cast< std::string >(vars, "html_renderer_classname")), 
    json_renderer_classname(Crails::cast< std::string >(vars, "json_renderer_classname")), 
    rss_renderer_classname(Crails::cast< std::string >(vars, "rss_renderer_classname")), 
    with_javascript(Crails::cast< bool >(vars, "with_javascript",  true)), 
    with_json(Crails::cast< bool >(vars, "with_json",  true)), 
    with_rss(Crails::cast< bool >(vars, "with_rss",  true))
  {}

  void render()
  {
ecpp_stream << "#!/bin/sh\n\n##\n## Renderers\n##\ncrails templates build \\\n  -r html \\\n  -i app/views \\\n  -t Crails::HtmlTemplate \\\n  -z crails/html_template.hpp \\\n  -n " << ( html_renderer_classname );
  ecpp_stream << " \\\n  -p \\.html$ \\\n  -v\n";
 if (with_json){
  ecpp_stream << "\ncrails templates build \\\n  -r json \\\n  -m raw \\\n  -i app/views \\\n  -t Crails::JsonTemplate \\\n  --stream-property stream \\\n  -z crails/json_template.hpp \\\n  -n " << ( json_renderer_classname );
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
  ecpp_stream << "\n##\n## Database\n##\nODB_AUTOGEN_PATH=\"app/autogen/odb\"\nODB_CXX_INCLUDES=\"-I. -I../..\"\nif [ ! -z \"$CRAILS_CMS_INCLUDE_DIRS\" ] ; then\n  ODB_CXX_INCLUDES=\"$odb_includes -I$CRAILS_CMS_INCLUDE_DIRS\"\nfi\n\nodb \\\n  $ODB_CXX_INCLUDES \\\n  --std c++20 \\\n  --default-pointer std::shared_ptr \\\n  -d pgsql \\\n  --table-prefix \"" << ( project_name );
  ecpp_stream << "_\" \\\n  --generate-schema --schema-format sql \\\n  --generate-query \\\n  --output-dir \"$ODB_AUTOGEN_PATH\" \\\n  app/models/*.hpp\n\n##\n## Fix ODB include paths\n##\nplugin_odb_hxx=\"`pwd`/lib/plugin-odb.hxx\"\nsearch_dirs=\". .. /usr/local/include $CRAILS_CMS_INCLUDE_DIRS\"\n\n# Step 1, create headers to redirect towards the real model headers\ncd app/models\nmodel_filenames=`find . -name \"*.hpp\"`\ncd -\ncd $ODB_AUTOGEN_DIR\nfor filename in $model_filenames ; do\n  touch \"$filename\" && echo \"#include \\\"../../models/$filename\\\"\" > \"$filename\"\ndone\ncd -\n\n# Step 2, remove broken include paths, add include to the global odb header\nfor target in \"$ODB_AUTOGEN_DIR\"/*-odb.hxx ; do\n  [ -e \"$target\" ] || continue\n\n  awk -v owndir=\"$ODB_AUTOGEN_DIR\" \\\n      -v searchdirs=\"$search_dirs\" \\\n      -v bridge='#include \"app/autogen/odb/application-odb.hpp\"' \\\n      -f prebuild-fix-odb.awk \\\n      \"$target\" > \"$target.tmp\"\n  mv \"$target.tmp\" \"$target\"\ndone\n\n##\n## Generate plugin-odb.hxx                                                                                                          \n##\nplugin_odb_path=\"`pwd`/$ODB_AUTOGEN_DIR\"\nplugin_odb_hpp=\"$plugin_odb_path/plugin-odb.hxx\"                                                                                    \ncd app/models\nif [ -f \"$plugin_odb_hpp\" ] ; then                                                                                                  \n  rm \"$plugin_odb_hpp\"                                                                                                              \nfi\necho \"#pragma once\" >> \"$plugin_odb_hpp\"\necho \"#include \\\"app/autogen/odb/application-odb.hpp\\\"\" >> \"$plugin_odb_hpp\"                                                        \nfor filepath in `find . -name \"*.h*\"` ; do                                                                                          \n  filename=$(basename -- \"$filepath\")                                                                                               \n  extension=\"${filename##*.}\"                                                                                                       \n  filename=\"${filename%.*}\"                                                                                                         \n  if [ -f \"$plugin_odb_path/$filename-odb.hxx\" ] ; then                                                                             \n    echo \"#include \\\"$filename-odb.hxx\\\"\" >> \"$plugin_odb_hpp\"                                                                      \n  fi                                                                                                                                \ndone                                                                                                                                \ncd -\n\n##\n## Generate database migration\n##\nset -e\noutput=\"app/database.cpp\"\n\nstrip_comments() { sed '/\\/\\*/,/\\*\\//d' \"$1\"; }\n\nemit() {\n  for file in lib/*.sql; do\n    strip_comments \"$file\" | awk -v mode=\"$1\" -f \"prebuild-schema.awk\"\n  done\n}\n\n{\n  echo \"// This file was generated automatically by prebuild.sh\"\n  echo '#include <crails/odb/connection.hpp>'\n  echo\n  echo 'void install_plugin_database()'\n  echo '{'\n  echo '  Crails::Odb::Connection database;'\n  echo\n  echo '  database.transaction.require(\"odb\");'\n  emit install\n  echo '  database.commit();'\n  echo '}'\n  echo\n  echo 'void uninstall_plugin_database()'\n  echo '{'\n  echo '  Crails::Odb::Connection database;'\n  echo\n  echo '  database.transaction.require(\"odb\");'\n  emit uninstall\n  echo '  database.commit();'\n  echo '}'\n} > \"$output\"\n\necho \"Generated $output\"\n";
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