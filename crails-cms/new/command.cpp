#include "command.hpp"
#include <crails/cli/conventions.hpp>
#include <crails/cli/with_path.hpp>
#include <crails/cli/process.hpp>
#include <crails/utils/semantics.hpp>

using namespace std;

void New::options_description(boost::program_options::options_description& desc) const
{
  desc.add_options()
    ("name,n",     boost::program_options::value<string>(), "project name")
    ("target,o",   boost::program_options::value<string>(), "folder in which the project will be generated (equal to `name` by default)")
    ("database,d", boost::program_options::value<string>(), "options: sqlite, pgsql, mysql, oracle");
}

int New::run()
{
  if (options.count("name"))
  {
    load_options();
    if (create_crails_application() && add_crails_plugins())
    {
      Crails::WithPath with_path(folder_target);

      generate_controllers();
      generate_admin_controllers();
      generate_models();
      generate_file("app/main.cpp");
      generate_file("app/routes.cpp");
      generate_file("config/renderers.cpp");
      generate_file("config/request_pipe.cpp");
      generate_file("config/cms/layouts.hpp");
      generate_file("config/cms/layouts.cpp");
      generate_file("config/cms/menus.hpp");
      generate_file("config/cms/plugins.hpp");
      generate_file("config/cms/plugins.cpp");
    }
  }
  return -1;
}

void New::load_options()
{
  project_name = options["name"].as<string>();
  if (options.count("database"))
    database_type = options["database"].as<string>();
  else
    database_type = "sqlite";
  if (options.count("target"))
    folder_target = options["target"].as<string>();
  else
    folder_target = project_name;
  renderer.vars["project_name"] = project_name;
}

bool New::create_crails_application()
{
  std::stringstream command;
  std::string crails_bin = Crails::which("crails");

  if (crails_bin.length())
  {
    command << crails_bin << " new "
      << " -n \"" << project_name << '"'
      << " -o \"" << folder_target << '"'
      << " -d \"" << database_type << '"'
      << " -p \"html.json\""
      << " --session-store CookieStore";
    cout << "+ " << command.str() << endl;
    Crails::run_command(command.str());
    return true;
  }
  else
    std::cerr << "crails command not found. Maybe it's not installed ?" << std::endl;
  return false;
}

bool New::add_crails_plugins()
{
  std::string crails_bin = Crails::which("crails");
  Crails::WithPath current_folder(folder_target);
  int results = 0;

  cout << "+ " << crails_bin << " templates formats -a html" << endl;
  results += Crails::run_command(crails_bin + " templates formats -a html");
  cout << "+ " << crails_bin << " templates formats -a json" << endl;
  results += Crails::run_command(crails_bin + " templates formats -a json");
  cout << "+ " << crails_bin << " plugins i18n install" << endl;
  results += Crails::run_command(crails_bin + " plugins i18n install");
  cout << "+ " << crails_bin << " plugins signin install" << endl;
  results += Crails::run_command(crails_bin + " plugins signin install");
  cout << "+ " << crails_bin << " plugins extra -a libcrails-attachment" << endl;
  results += Crails::run_command(crails_bin + " plugins extra -a libcrails-attachment");
  cout << "+ " << crails_bin << " plugins extra -a libcrails-image" << endl;
  results += Crails::run_command(crails_bin + " plugins extra -a libcrails-image");
  cout << "+ " << crails_bin << " plugins extra -a libcrails-cms" << endl;
  results += Crails::run_command(crails_bin + " plugins extra -a libcrails-paginator");
  cout << "+ " << crails_bin << " plugins extra -a libcrails-cms" << endl;
  results += Crails::run_command(crails_bin + " plugins extra -a libcrails-cms");
  return true;
  //return results != 0;
}

void New::generate_controllers()
{
  std::set<std::string> controllers{
    "page"
  };

  generate_file("app/controllers/application.hpp");
  generate_file("app/controllers/application.cpp");
  generate_file("app/controllers/home.hpp");
  generate_file("app/controllers/home.cpp");
  generate_file("app/controllers/signin.hpp");
  generate_file("app/controllers/signin.cpp");
  for (std::string resource_name : controllers)
  {
    renderer.vars["resource_name"] = resource_name;
    renderer.generate_file("app/controllers/resource.hpp", "app/controllers/" + resource_name + ".hpp");
  }
}

void New::generate_admin_controllers()
{
  std::set<std::string> controllers{
    "attachment",
    "menu",
    "page",
    "user",
    "user_group",
    "wizard"
  };

  generate_file("app/controllers/admin/application.hpp");
  generate_file("app/controllers/admin/opengraph.hpp");
  generate_file("app/controllers/admin/settings.hpp");
  generate_file("app/controllers/admin/opengraph.hpp");
  for (std::string resource_name : controllers)
  {
    renderer.vars["local_route"] = Crails::pluralize(resource_name);
    renderer.vars["resource_name"] = resource_name;
    renderer.vars["resource_traits"] = resource_name + "_traits";
    if (resource_name == "wizard")
      renderer.vars["resource_traits"] = std::string("settings_traits");
    renderer.generate_file("app/controllers/admin/resource.hpp", "app/controllers/admin/" + resource_name + ".hpp");
  }
}

void New::generate_models()
{
  std::set<std::string> models{
    "settings",
    "user",
    "permission_rule",
    "menu",
    "page",
    "attachment"
  };

  generate_file("app/models/homepage.hpp");
  generate_file("app/models/traits.hpp");
  for (std::string resource_name : models)
    generate_model(resource_name);
  generate_user_group_model();
  generate_permission_rule_model();
}

void New::generate_model(const std::string& resource_name)
{
  const std::set<std::string> with_tags{"attachment"};
  std::string header_template = "app/models/model.hpp";
  std::string source_template = "app/models/model.cpp";
  std::string traits_template = "app/models/resource_traits.hpp";
  std::string filename = Crails::naming_convention.filenames(resource_name);
  std::string tag_filename = Crails::naming_convention.filenames(resource_name + "_tag_query");

  renderer.vars["resource_name"] = resource_name;
  if (with_tags.find(resource_name) != with_tags.end())
  {
    renderer.vars["tag_query"] = tag_filename;
    renderer.generate_file("app/models/tag_query.hpp", "app/models/" + tag_filename + ".hpp");
  }
  else
    renderer.vars["tag_query"] = std::string();
  if (filename == "user")
    header_template = "app/models/user.hpp";
  renderer.generate_file(header_template, "app/models/" + filename + ".hpp");
  renderer.generate_file(source_template, "app/models/" + filename + ".cpp");
  renderer.generate_file(traits_template, "app/models/" + filename + "_traits.hpp");
}

void New::generate_user_group_model()
{
  renderer.vars["tag_query"] = std::string();
  renderer.vars["resource_name"] = std::string("user_group");
  renderer.generate_file("app/models/user_group.hpp", "app/models/user_group.hpp");
  renderer.generate_file("app/models/user_group.cpp", "app/models/user_group.cpp");
  renderer.generate_file("app/models/resource_traits.hpp", "app/models/user_group_traits.hpp");
}

void New::generate_permission_rule_model()
{
  renderer.vars["resource_name"] = std::string("permission_rule");
  renderer.generate_file("app/models/permission_rule.hpp", "app/models/permission_rule.hpp");
  renderer.generate_file("app/models/permission_rule.cpp", "app/models/permission_rule.cpp");
}
