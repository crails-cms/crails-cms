#include "command.hpp"
#include <crails/cli/with_path.hpp>
#include <crails/cli/conventions.hpp>
#include <filesystem>

using namespace std;

void NewLayout::options_description(boost::program_options::options_description& desc) const
{
  desc.add_options()
    ("name,n", boost::program_options::value<string>(), "layout name")
    ("target,o", boost::program_options::value<string>(), "folder in which the plugin will be generated (equal to `name` by default)");
}

int NewLayout::run()
{
  if (options.count("name"))
  {
    load_options();
    if (filesystem::create_directories(folder_target))
    {
      Crails::WithPath with_path(folder_target);

      generate_file(".crails");
      generate_file("CMakeLists.txt");
      generate_file("prebuild.sh");
      generate_file("package.json");
      generate_file("webpack.config.js");
      generate_file("src/main.cpp");
      generate_file("src/style.hpp");
      generate_file("src/layout.hpp");
      generate_file("src/layout.cpp");
      renderer.generate_file("layouts/views/layouts/themes/layout.html", "views/layouts/themes/" + Crails::naming_convention.filenames(project_name) + ".html");
      generate_file("views/layouts/themes/layout.html");
      generate_file("javascripts/editor.js");
      generate_file("javascripts/index.js");
      generate_file("stylesheets/admin.scss");
      generate_file("stylesheets/layout.scss");
      generate_file("stylesheets/_fonts.scss");
      generate_file("stylesheets/_theme.scss");
      filesystem::permissions("prebuild.sh", filesystem::perms::owner_all | filesystem::perms::group_all);
      return 0;
    }
    return -2;
  }
  return -1;
}

void NewLayout::load_options()
{
  project_name = options["name"].as<string>();
  if (options.count("target"))
    folder_target = options["target"].as<string>();
  else
    folder_target = project_name;
  renderer.vars["project_name"] = project_name;
  renderer.vars["layout_editor_name"] = Crails::naming_convention.classnames(project_name + "LayoutEditor");
  renderer.vars["renderer_classname"] = Crails::naming_convention.classnames(project_name + "HtmlRenderer");
  renderer.vars["assets_classname"] = Crails::naming_convention.classnames(project_name + "Assets");
  renderer.vars["style_classname"] = Crails::naming_convention.classnames(project_name + "Style");
}
