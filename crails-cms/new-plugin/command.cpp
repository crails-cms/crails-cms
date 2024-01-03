#include "command.hpp"
#include <crails/cli/with_path.hpp>
#include <crails/cli/conventions.hpp>
#include <filesystem>

using namespace std;

void NewPlugin::options_description(boost::program_options::options_description& desc) const
{
  desc.add_options()
    ("name,n", boost::program_options::value<string>(), "plugin name")
    ("target,o", boost::program_options::value<string>(), "folder in which the plugin will be generated (equal to `plugins/[name]` by default)");
}

int NewPlugin::run()
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
      generate_file("app/main.cpp");
      generate_file("app/routes.cpp");
      generate_file("app/renderers.cpp");
      generate_file("app/database.cpp");
      filesystem::create_directories("app/controllers/admin");
      filesystem::create_directories("app/models");
      filesystem::create_directories("app/views");
      filesystem::permissions("prebuild.sh", filesystem::perms::owner_all | filesystem::perms::group_all);
      return 0;
    }
    return -2;
  }
  return -1;
}

void NewPlugin::load_options()
{
  project_name = options["name"].as<string>();
  if (options.count("target"))
    folder_target = options["target"].as<string>();
  else
    folder_target = "plugins/" + project_name;
  renderer.vars["project_name"] = project_name;
  renderer.vars["html_renderer_classname"] = Crails::naming_convention.classnames(project_name + "PluginHtmlRenderer");
  renderer.vars["json_renderer_classname"] = Crails::naming_convention.classnames(project_name + "PluginJsonRenderer");
}
